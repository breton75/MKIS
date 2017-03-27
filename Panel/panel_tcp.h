#ifndef PANEL_TCP_H
#define PANEL_TCP_H

#include <QObject>
#include "QTcpSocket"
#include <Exception>
#include <QBitArray>
#include<QApplication>
//#pragma pack(push, 1)

class Panel_tcp : public QObject
{
    Q_OBJECT
public:
    explicit Panel_tcp(QObject *parent = 0);
    ~Panel_tcp();
  QTcpSocket *tcpSocket;
QBitArray *Red;//=0x0;
QBitArray *Green;//=0xFFFFFFFF;

signals:

public slots:
   virtual void readFortune();
   virtual void displayError(QAbstractSocket::SocketError error);
   virtual void Write_date(int Red_i, int Green_i);
   int conectTCP(bool Led, int Nember );
};

#endif // PANEL_TCP_H
