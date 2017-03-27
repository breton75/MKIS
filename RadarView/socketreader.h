#ifndef SOCKETREADER_H
#define SOCKETREADER_H

#include <QThread>

struct Azimuth
{
    int num;
    QByteArray levels;
};

class QUdpSocket;

class SocketReader : public QThread
{
    Q_OBJECT
public:
    explicit SocketReader(const QString &ip_addr,
                          const quint16 port,
                          const quint32 azimuths_count,
                          const quint16 points_count,
                          QObject *parent = 0);
    ~SocketReader();
    static QString getLocalIp();

public:
    void run();

signals:
    void stopLoop();
    void azimuthUpdated(Azimuth);

public slots:
    void stopWork();

private slots:

private:
    QUdpSocket *socket;
    QByteArray buff;
    bool allowCapture;
    const QString ip_address;
    const quint16 port_num;
    const quint32 max_azimuths;
    const quint16 max_points;
};

#endif // SOCKETREADER_H
