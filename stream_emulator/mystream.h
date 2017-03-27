#ifndef MYSTREAM_H
#define MYSTREAM_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QDateTime>

#pragma pack(push,1)
struct Line2bit {
   quint8 dollarChar;  // символ '$' (0x24 = 36)
      int latitude;    // широта места установки радара
      int longitude;   // долгота места установки радара
  quint32 reserved; 
  
  quint32 lineLen;  
  quint32 lineNum;
  quint16 discret;
  quint64 lineDT;
};
#pragma pack(pop)

class myStream : public QThread
{
    Q_OBJECT
  protected:
    void run();
    
  private:
    
    
  public:
    myStream(QString ip, quint16 port, QObject *parent = 0);
    ~myStream();
    
    QUdpSocket *udp;
    bool enable = false;

    QString ip;
    quint16 port;
    
  signals:
    void uu();
    
  public slots:
};

#endif // MYSTREAM_H
