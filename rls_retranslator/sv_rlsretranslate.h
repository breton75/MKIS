#ifndef SVRL2BITRETRANSLATE_H
#define SVRL2BITRETRANSLATE_H

#include <QWidget>
#include <QObject>
#include <QUdpSocket>
#include <QIODevice>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QThread>
#include <QDateTime>
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QTime>
//#include <QSlider>
#include <QVBoxLayout>
#include <QDialog>
#include <qmath.h>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>

#define Header2bitSize 13
#pragma pack(push,1)
struct Header2bit {
   quint8 dollarChar;  // символ '$' (0x24 = 36)
      int latitude;    // широта места установки радара
      int longitude;   // долгота места установки радара
  quint16 linesCount;    
  quint16 reserved; 
};
#pragma pack(pop)

#define Line2bitHeaderSize 18
#pragma pack(push,1)
struct Line2bit
{
  quint32 lineLen;  
  quint32 lineNum;
  quint16 discret;
  quint64 lineDT;
};
#pragma pack(pop)

class SvRlsRetranslate : public QThread
{
    Q_OBJECT
  public:
    explicit SvRlsRetranslate(QString ip,
                              quint16 port,
                              QObject *parent = 0);
    
    ~SvRlsRetranslate();

    bool isPlaying() { return _playing; }

  private:
    quint16 port;
        int rotation_speed;
    int linesCount;
    bool _playing = false;
    
    QString user_name;
//    QString password;
    QString path_to_save_file;
    QString device_name;
    QString datetime_format;
    QString file_name_format;
    
    QTime   file_duaration;
    QTime   total_duaration;
    qint32 file_duration_sec;
    qint32 total_duration_sec;
    
    QFile* file = NULL;
    QDataStream* out = NULL;
    bool new_file;
    bool new_header;
    
  protected:
    void run() Q_DECL_OVERRIDE;
    
  signals:
//    void lineUpdated(int lineNum);
    void NewFile();
    void NewHeader();
    void TotalTimeElapsed();
    void TimeElapsed();
    void finished();
    
  public slots:
    void stop() { _playing = false; }
    
  private slots:
//    void readPendingDatagrams();

    
};

class SvRls2bitFile2Udp : public QThread
{
  Q_OBJECT
    
  public:
    SvRls2bitFile2Udp(QString ip,
                      quint16 port,
                      QDateTime begin_date_time,
                      QDateTime end_date_time,
                      int device_id);
    
    ~SvRls2bitFile2Udp();

    bool isPlaying() { return _playing; }
    QString CurrentFileName() { return current_file_name; }
    
  private:
    void run() Q_DECL_OVERRIDE;
    
    QSqlQuery* query;
    
    QString ip;
    quint16 port;
    QDateTime begin_date_time;
    QDateTime end_date_time;
    int device_id;
    
    QString current_file_name;
    bool _playing = false;
    
  signals:
    void NoRecords();
    void NewFile();
    void WrongFile();
    
  public slots:
    void stop() { _playing = false; }
};

#endif // SVRL2BITRETRANSLATE_H
