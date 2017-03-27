#include "socketreader.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QUdpSocket>

const quint16 packetSize(1460);		// размер пакета одного азимута
const quint16 headerSize(4);		// размер заголовка
static const unsigned char header[headerSize] = {		// заголовок/метка начала пакета
    0xEE, 0xEE, 0xEE, 0xEE
};

SocketReader::SocketReader(const QString &ip_addr,
                           const quint16 port,
                           const quint32 azimuths_count,
                           const quint16 points_count,
                           QObject *parent)
    : QThread(parent),
      allowCapture(false),
      ip_address(ip_addr),
      port_num(port),
      max_azimuths(azimuths_count),
      max_points(points_count)
{
    buff.resize(packetSize);
    qRegisterMetaType<Azimuth>("Azimuth");
}

SocketReader::~SocketReader()
{
    delete socket;
}

void SocketReader::run()
{
    allowCapture = true;
    socket = new QUdpSocket;
    socket->bind(/*QHostAddress(ip_address), */port_num);

    while (allowCapture)
    {
        while (socket->waitForReadyRead(500))
        {
            while (socket->hasPendingDatagrams())
            {
                socket->readDatagram(buff.data(), packetSize);

                uint posByte(0);
                while (posByte < headerSize)
                {
                    if (buff[posByte] != (char)header[posByte])
                        continue;
                    ++posByte;
                }

                quint32 num_azimuth(0);
                for (int i = 0; i < 4; ++i)	// 4 байта для номера азимута
                {
                    num_azimuth |= (quint32)(uchar)buff[posByte++] << (i * 8);
                }

                if (num_azimuth >= max_azimuths)
                    break;
                else
                {
                    bool correct(true);

                    Azimuth cur_azimuth;
                    cur_azimuth.num = num_azimuth;
                    cur_azimuth.levels.resize(max_points);

                    while (posByte < packetSize)
                    {
                        quint16 cur_point(0);
                        quint8 cur_level(0);
                        for (int i = 0; i < 2; ++i) // 2 байта для номера точки
                            cur_point |= (quint16)(uchar)buff[posByte++] << (i * 8);
                        if (cur_point >= max_points)
                        {
                            correct = false;
                            break;
                        }

                        cur_level = (quint8)buff[posByte++];
                        if (cur_level > 7) // допустимый уровень сигнала
                        {
                            correct = false;
                            break;
                        }

                        if (buff[posByte++] != char(0))
                        {
                            correct = false;
                            break;
                        }
                        cur_azimuth.levels[cur_point] = cur_level;
                    }
                    if (correct)
                    {
                        azimuthUpdated(cur_azimuth);
                    }
                }
            }
        }
    }

    socket->close();
}

void SocketReader::stopWork()
{
    allowCapture = false;
    emit stopLoop();
}

QString SocketReader::getLocalIp()
{
    QString localIp;
    foreach (const QHostAddress &addr, QNetworkInterface::allAddresses())
    {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol &&
            addr != QHostAddress(QHostAddress::LocalHost))
            localIp = addr.toString();
    }
    return localIp;
}
