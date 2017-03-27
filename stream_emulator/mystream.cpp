#include "mystream.h"
#include "log.h"

#include <QByteArray>
#include <QHostAddress>
#include <time.h>

using namespace log_ns;

myStream::myStream(QString ip, quint16 port, QObject *parent) : QThread(parent)
{
  this->ip = ip;
  this->port = port;
}

myStream::~myStream()
{
  this->deleteLater();
}

void myStream::run()
{
  udp = new QUdpSocket();
  
  QByteArray data;
  data.clear();
  
  int azimuth = 0;
  long int cps = CLOCKS_PER_SEC;
  int point_num = 0;
  
  Line2bit* l2 = new Line2bit;
  l2->dollarChar = '$';
  l2->latitude = 0;
  l2->longitude = 0;
  l2->reserved = 0;
  l2->lineLen = 4096;
  l2->lineNum = 0;
  l2->discret = 3570;
  
  int ln = 0;
  this->enable = true;
  while(this->enable)
  {
    clock_t t = clock();
    
//    // признак нового азмута
//    data.append(char(0xEE));
//    data.append(char(0xEE));
//    data.append(char(0xEE));
//    data.append(char(0xEE));
  
//    // номер азимута
//    data.append(char(azimuth));
//    data.append(char(azimuth >> 0x08));
//    data.append(char(azimuth >> 0x10));
//    data.append(char(azimuth >> 0x18)); 
    
//    if(azimuth == 4095) azimuth = 0;
//    else azimuth++;
    
    l2->lineNum = ln;
    l2->lineDT = QDateTime::currentMSecsSinceEpoch();
    
    data.append((char*)(l2), sizeof(Line2bit));
    
    // точки
    for(point_num = 0; point_num < 4096; point_num++)
    {
//      data.append(char(point_num));
//      data.append(char(point_num >> 8));
      int val = rand();
      data.append((char*)(&val));
      
//      data.append(char(0x07 & rand()));
//      data.append(char(0));
    }
    
    udp->writeDatagram(data, QHostAddress(this->ip), this->port);
    data.clear();
    
//    msleep((1 - (clock() - t)/cps) * 1000)/* > 2000*/;
    msleep(1000);
  }
}

