#include "sv_tcpclient.h"
#include "log.h"
#include "sv_secondmeter.h"

#include <QApplication>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QFuture>
#include <QProgressDialog>
#include <QMessageBox>

using namespace log_ns;

//QTcpSocket* pClientSocket;
QString char2hex(char c, bool toUpper = true, bool add0x = false);

/**************************************************************/

QString char2hex(char c, bool toUpper, bool add0x)
{
    QString s = "";
    int d = 0;
    memcpy(&d, &c, 1);

    s.setNum(d, 16);
    if(s.length() == 1) s = '0' + s;

    return (add0x ? "0x" : "") + (toUpper ? s.toUpper() : s) + " ";

}

SvTcpClient::SvTcpClient(QString ip,
                         quint16 port,
                         QObject *parent) :
  QObject(parent)
{
  this->ip = ip;
  this->port = port;
  
  this->socket = new QTcpSocket(this);
  connect(this->socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
  connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotSocketError(QAbstractSocket::SocketError)));
  connect(this->socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(slotStateChanged(QAbstractSocket::SocketState)));
  
//  log(m_Info, "Clent runned");
  
}

int SvTcpClient::connectToHost()
{
  try
  {
    if (this->ip == "") {log(m_Err, "Wrong IP adress\n"); return SOCKET_WRONG_IP;}// throw SOCKET_WRONG_IP; //
    if (this->port == 0) {log(m_Err, "Wrong port\n"); return SOCKET_WRONG_PORT;}// throw(SOCKET_WRONG_PORT);
    
    if (!this->connected)
      {    
        this->socket->connectToHost(this->ip, this->port);
        if (this->socket->waitForConnected(2000))
          {
            this->connected = true;
            return SOCKET_OK;
          }
        else {log(m_Err, QString("Can not connect to %1:%2\n").arg(this->ip).arg(this->port)); return SOCKET_BAD_CONNECTION;}//throw(SOCKET_BAD_CONNECTION);
      }
    return 0;
  }
 
  catch (int err)
  {
    switch (err)
    {  
      case SOCKET_BAD_CONNECTION:
        log(m_Err, QString("Can not connect to %1:%2\n").arg(this->ip).arg(this->port));
        break;      
      
      case SOCKET_WRONG_IP:
        log(m_Err, "Wrong IP adress\n");
        break;
        
      case SOCKET_WRONG_PORT:
        log(m_Err, "Wrong port\n");
        break;        
    }
    
    return err;
  }
}

void SvTcpClient::disconnectFromHost()
{
  this->socket->disconnectFromHost();
  this->connected  = false;
}

void SvTcpClient::slotSocketError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     (QString(this->socket->errorString()) != "" ? QString(this->socket->errorString()) :
                      QString(this->socket->errorString()))
                    );
    log(m_Err, strError);
}

void SvTcpClient::slotStateChanged(QAbstractSocket::SocketState state)
{
  switch (state)
    {
    case QAbstractSocket::UnconnectedState:
      log(m_Info, "No connection");
      this->connected = false;
      QApplication::processEvents();
      break;
      
    case QAbstractSocket::HostLookupState:
      log(m_Info, QString("Looking up for %1").arg(this->ip));
      QApplication::processEvents();
      break;   

    case QAbstractSocket::ConnectingState:
      log(m_Info, QString("Connecting to %1").arg(this->ip));
      QApplication::processEvents();
      break;
      
    case QAbstractSocket::ConnectedState:
      this->connected = true;
      log(m_Info, QString("Connected to %1").arg(this->ip));
      QApplication::processEvents();
      break;

    case QAbstractSocket::BoundState:
      log(m_Info, QString("Bounded for %1:%2").arg(this->ip).arg(this->port));
      QApplication::processEvents();
      break; 
      
    case QAbstractSocket::ClosingState:
      log(m_Info, "Closing connection");
      QApplication::processEvents();
      break;       
    }
}

void SvTcpClient::slotReadyRead()
{
  try
  {
    QString str;
    
    if (!this->advancedStream)
    {
      if (this->socket->bytesAvailable() > 0)
      {
        responseData = this->socket->readAll();
      
        if(log_responses)
        {
          for (int i=0; i < responseData.size(); i++)
          {
            if(showSymbols)
            {
              if((responseData.at(i) > 31) || 
                 (responseData.at(i) == 10) || 
                  (responseData.at(i) == 13)) 
                 str = str + responseData.at(i);
              else str = str + char2hex(responseData.at(i)) + " ";
            }
            
            else str = str + char2hex(responseData.at(i));
            
          }
        }
      }
        
      else
      {
        responseSize = 0;
        QDataStream in(this->socket);
        
        in.setVersion(this->streamVersion);/*QDataStream::Qt_5_3*/
        for (;;)
        {
          if (!responseSize)
          {
            if (this->socket->bytesAvailable() < (quint64)sizeof(quint64)) break;
            in >> responseSize;
          }
          if (this->socket->bytesAvailable() < responseSize) break;
    //      QTime   time;
          
          responseData = this->socket->readAll();

          if(log_responses)
          {
            QDataStream in1(responseData);
            in1.setVersion(this->streamVersion);
            in1 >> str;
//            in >> responseData;// /*time >>*/ str;
          }

          responseSize = 0;
        }
      }
    }
    
    if(log_responses) log(m_Data, /*time.toString() + " " +*/ " >> " + str);
    
    emit sigGotNewData();
  }

  catch(...)
  {
    log(m_Err, "slotReadyRead error: ");  
  }
    
}

void SvTcpClient::sendData(QString text, int msecWaitForAnswer, QObject* parent)
{
  QByteArray arrBlock;

  if(!this->advancedStream) arrBlock.append(text);

  else
  {
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(this->streamVersion);/*QDataStream::Qt_5_3*/
    out << quint16(0) /*<< QTime::currentTime()*/ << text;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
  }

  this->socket->write(arrBlock);
  log(m_Data, " << " + text);
  
  if(msecWaitForAnswer == dontWait) return;
  
  /*********************** ждем ответ ***********************/
  this->responseSize = 0;
  this->responseData.clear();
  
  SvSecondMeter *t = new SvSecondMeter(msecWaitForAnswer,
                                       "Waiting for response",
                                       "Cancel",
                                       true,
                                       parent);
  
  connect(this, SIGNAL(sigGotNewData()), t, SLOT(slotDone()));
  
  //while((t->status == SvSecondMeter::smsRunned)&&(this->socket->isOpen())) QApplication::processEvents();
  while((t->status == SvSecondMeter::smsRunned)&&(this->socket->isOpen())&&(socket->state() == QAbstractSocket::ConnectedState)) QApplication::processEvents();
  //if(!this->socket->isOpen()) t->status = SvSecondMeter::smsUnfinished;
  if(!this->socket->isOpen() && (t->status == SvSecondMeter::smsRunned)) t->status = SvSecondMeter::smsUnfinished;

  
  switch (t->status)
  {
    case SvSecondMeter::smsCanceled:
      this->socket->abort();
      QApplication::processEvents(QEventLoop::AllEvents, 3000);
      log(m_Err, QString("Response awaiting was canceled by user at %1").
            arg(t->current_time.toString("hh:mm:ss")));
      this->responseStatus = SOCKET_AWAITING_CANCELED;
      break;
      
    case SvSecondMeter::smsTimeout:
      this->socket->abort();
      QApplication::processEvents(QEventLoop::AllEvents, 3000);
      log(m_Err, QString("Response awaiting timeout %1").
            arg(t->current_time.toString("hh:mm:ss")));
      this->responseStatus = SOCKET_TIMEOUT;
      break;
      
    case SvSecondMeter::smsUnfinished:
      log(m_Err, QString("Qwaiting not finished %1").
            arg(t->current_time.toString("hh:mm:ss")));
      this->responseStatus = SOCKET_CONNECTION_CLOSED;
      break;
      
    case SvSecondMeter::smsDoneOk:
      this->responseStatus = SOCKET_OK;      
  }
  
  t->~SvSecondMeter();
  
}

void SvTcpClient::sendData(QByteArray* data, int msecWaitForAnswer, bool showSymbols, QObject* parent)
{
//    if(!this->clientSocket->connected()) return;
  
    QByteArray *arrBlock = new QByteArray();
    
    arrBlock->append(*data); // (const char*)data, length);
    
    this->socket->write(*data);
    
    if(showSymbols)
    {
      QString s = "";
      for(int i=0; i < arrBlock->length(); i++)
          s = s + char2hex(arrBlock->at(i));
      
      log(m_Data, " << " + s);
    }

    if(msecWaitForAnswer == dontWait) return;
    
    /*********************** ждем ответ ***********************/
    this->responseSize = 0;
    this->responseData.clear();
    
    SvSecondMeter *t = new SvSecondMeter(msecWaitForAnswer,
                                         "Waiting for response",
                                         "Cancel",
                                         true,
                                         parent);
    
    connect(this, SIGNAL(sigGotNewData()), t, SLOT(slotDone()));
    
    //while((t->status == SvSecondMeter::smsRunned)&&(this->socket->isOpen())) QApplication::processEvents();
    while((t->status == SvSecondMeter::smsRunned)&&(this->socket->isOpen())&&(socket->state() == QAbstractSocket::ConnectedState)) QApplication::processEvents();
    //if(!this->socket->isOpen()) t->status = SvSecondMeter::smsUnfinished;
    if(!this->socket->isOpen() && (t->status == SvSecondMeter::smsRunned)) t->status = SvSecondMeter::smsUnfinished;
    
    switch (t->status)
    {
      case SvSecondMeter::smsCanceled:
        this->socket->abort();
        QApplication::processEvents(QEventLoop::AllEvents, 3000);
        log(m_Err, QString("Response awaiting was canceled by user at %1").
              arg(t->current_time.toString("hh:mm:ss")));
        this->responseStatus = SOCKET_AWAITING_CANCELED;
        break;
        
      case SvSecondMeter::smsTimeout:
        this->socket->abort();
        QApplication::processEvents(QEventLoop::AllEvents, 3000);
        log(m_Err, QString("Response awaiting timeout %1").
              arg(t->current_time.toString("hh:mm:ss")));
        this->responseStatus = SOCKET_TIMEOUT;
        break;
        
      case SvSecondMeter::smsUnfinished:
        log(m_Err, QString("Qwaiting not finished %1").
              arg(t->current_time.toString("hh:mm:ss")));
        this->responseStatus = SOCKET_CONNECTION_CLOSED;
        break;
        
      case SvSecondMeter::smsDoneOk:
        this->responseStatus = SOCKET_OK;      
    }
    
    t->~SvSecondMeter();
}

void SvTcpClient::sendData(int msecWaitForAnswer /* = 30000 */)
{
  try
  {
    /************* для отладки таймера ************/
    
    /*********************** ждем ответ ***********************/
    this->responseSize = 0;
    this->responseData.clear();
    
    SvSecondMeter *t = new SvSecondMeter(msecWaitForAnswer,
                                         "Waiting for response",
                                         "Cancel",
                                         true);
    
//    connect(this, SIGNAL(sigGotNewData()), t, SLOT(slotDone()));
    
    while(t->status == SvSecondMeter::smsRunned) QApplication::processEvents();
    
    switch (t->status)
    {
      case SvSecondMeter::smsCanceled:
//        this->socket->abort();
        log(m_Err, QString("Response awaiting was canceled by user at %1").
              arg(t->current_time.toString("hh:mm:ss")));
        this->responseStatus = SOCKET_AWAITING_CANCELED;
        break;
        
      case SvSecondMeter::smsTimeout:
//        this->socket->abort();
        log(m_Err, QString("Response awaiting timeout %1").
              arg(t->current_time.toString("hh:mm:ss")));
        this->responseStatus = SOCKET_TIMEOUT;
        break;
        
      case SvSecondMeter::smsDoneOk:
        this->responseStatus = SOCKET_OK;      
    }
    
    t->~SvSecondMeter();
  }
  
  catch(...)
  {
    log(m_Err, "sayToServer: ");
  }
}
