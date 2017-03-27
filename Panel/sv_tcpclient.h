#ifndef SV_TCPCLIENT_H
#define SV_TCPCLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTimer>
#include <QDataStream>

const int dontWait = -1;
const int infinite = 0;

enum SocketErrors
{
  SOCKET_ERROR = -1,
  SOCKET_OK = 0,
  SOCKET_BAD_CONNECTION,
  SOCKET_WRONG_IP,
  SOCKET_WRONG_PORT,
  SOCKET_CONNECTION_FAULT,
  SOCKET_ALREADY_CONNECTED,
  SOCKET_NOT_CONNECTED,
  SOCKET_TIMEOUT,
  SOCKET_AWAITING_CANCELED,
  SOCKET_CONNECTION_CLOSED
};

class SvTcpClient : public QObject
{
    Q_OBJECT

  private:
    quint16     nextBlockSize = 0;

  public:
    quint16 port;
    QString ip;    
    
    SvTcpClient(QString ip = "",
                quint16 port = 35580,
                QObject *parent = 0);      
    
    QTcpSocket* socket;
    bool connected = false;
    
    QByteArray responseData = 0;
    quint64 responseSize = 0;
    int responseStatus = -1;
    
    virtual int connectToHost();
    virtual void disconnectFromHost();
    
    bool advancedStream = false;
    int streamVersion = QDataStream::Qt_5_2;
    bool showSymbols = true;
    
    bool log_requests = true;
    bool log_responses = true;
    
    
    virtual void sendData(QByteArray* data, int msecWaitForAnswer = dontWait, bool showSymbols = false, QObject *parent = 0);
    virtual void sendData(QString text, int msecWaitForAnswer = dontWait, QObject* parent = 0);
    
    /* для отладки таймера */
    virtual void sendData(int msecWaitForAnswer = 30000);
    
  signals:
    virtual void sigGotNewData();
  
  private slots:
      virtual void slotReadyRead();
      virtual void slotSocketError(QAbstractSocket::SocketError);
      virtual void slotStateChanged(QAbstractSocket::SocketState state);

  public slots:
//    virtual void slotNewConnection();
//    virtual void slotReadClient   ();
//    virtual void slotClientDisconnected();
    

    //void slotSetShowSymbols(bool showSymbols) { this->showSymbols = showSymbols; }
    
};

#endif // SV_TCPCLIENT_H








