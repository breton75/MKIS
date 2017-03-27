#include "panel_tcp.h"
//#include "QTcpSocket"
#include <QDebug>
#include <QString>
Panel_tcp::Panel_tcp(QObject *parent) : QObject(parent)
{
tcpSocket=new QTcpSocket(this);

  //  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
//    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
Red= new QBitArray;
Red->resize(32);
Red->fill(false,0,32);

Green= new QBitArray;
Green->resize(32);
Green->fill(true,0,32);
}

Panel_tcp::~Panel_tcp()
{

}

void Panel_tcp::readFortune()
{

}

void Panel_tcp::displayError(QAbstractSocket::SocketError error)
{
    qDebug()<<"error disa:"<<error;
}

void Panel_tcp::Write_date(int Red_i, int Green_i )
{
//alarmst.nameq=new QString("ALARM");
//int Green=0xFFFFFFFE;
//int RED=0x1;
    char *txt;
    try
      {
 QByteArray arrBlock ;//= new QByteArray();
    arrBlock.append("ALARM");
    arrBlock.append( QByteArray::fromRawData((char*)&Red_i,4));
    arrBlock.append( QByteArray::fromRawData((char*)&Green_i,4));
    txt=arrBlock.data();
  //arrBlock->append(RED);
    tcpSocket->write(txt,13);
    qint64 len;
    qDebug()<<" Write";
    tcpSocket->read(txt,len);
   //   qDebug()<<" tcpSocket->write(txt,13); "<<QString("%1").arg( tcpSocket->write(txt,13));
    //while (tcpSocket->readBufferSize()>0)
    {
       //tcpSocket->read(txt,len);
        QApplication::processEvents();

    }
     qDebug()<<" tcpSocket->bytesAvailable "<<QString("%1").arg(tcpSocket->bytesAvailable());

    tcpSocket->disconnectFromHost();
    }
    catch (const std::bad_alloc &)
    {
    // handle exception
        ;
    }

}

int Panel_tcp::conectTCP(bool Led, int Nember)
{

    int Red_i=0;
    int Green_i=0;
    try
    {

        //QBitArray  a(32);
        //a= (a);
        qDebug()<<"Nember="<<QString("%1").arg(Nember)<<" Led="<<Led;
        if (Led==0)
        {
            Green->setBit(Nember-1,true);
            Red->setBit(Nember-1,false);

        }
        else
        {
            Green->setBit(Nember-1,false);
            Red->setBit(Nember-1,true);

        }
        //char *data = ba.data();


            for(uint i = 0; i < Red->size(); i++)
            {
                Red_i <<= 1;
                Red_i += (int)Red->at(i);
            }
            for(uint i = 0; i < Green->size(); i++)
            {
                Green_i <<= 1;
                Green_i += (int)Green->at(i);
            }

        //mcpy(&Red_i, Red, sizeof(int));
        //memcpy(&Green_i, Green, sizeof(Green));
//        for(int i=0;i<32;i++)
//        {
//        qDebug()<<i<<QString("Green %1").arg(Green->testBit(i));
//        }
//        for(int i=0;i<32;i++)
//        {
//        qDebug()<<i<<QString("Red %1").arg(Red->testBit(i));
//        }
        qDebug()<<" <<:"<<QString("Red_i %1").arg(Red_i);
        qDebug()<<" <<:"<<QString("Green_i %1").arg(Green_i);

        QString IP="169.254.1.253";
        quint16 port = 35550;
        qDebug()<<" disa:"<<IP<<QString("port %1").arg(port);
        tcpSocket->connectToHost(IP,port);
        const int Timeout = 5 * 1000;


                 if (!tcpSocket->waitForConnected(Timeout))
                 {
                    // emit error(tcpSocket->error(), tcpSocket->errorString());
                     //return;
                 }
        qDebug()<<"conect disa:"<<tcpSocket;


        Write_date(Red_i,Green_i);
        qDebug()<<"conect :"<<tcpSocket->errorString();
    }
    catch (const std::bad_alloc &)
    {
    // handle exception
        ;
    }
}
