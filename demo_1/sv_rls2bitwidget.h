#ifndef SVRL2BITSWIDGET_H
#define SVRL2BITSWIDGET_H

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
#include <QSqlQuery>
#include <QSqlError>

#include <QVBoxLayout>
#include <QDialog>
#include <qmath.h>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>

#include "./COMMON/sv_tcpserverclient.h"

#define AZIMUTHS_COUNT 4096

class SvRlsDataBuffering;

class SvRls2BitWidget : public QWidget
{
  Q_OBJECT
  
  public:
    
    SvRls2BitWidget(quint16 port,
                    QString caption,
                    int window_width = 640,
                    int window_height = 640,
                    int img_resolution = 640,
                    int draw_points_per_line = 1024,
                    QImage *background = 0);
    
    ~SvRls2BitWidget();
    
    void* _buffer;
//    void* _img;
    QImage img;
    int img_resolution;
    
    bool isPlaying();
//    QGraphicsScene* scene;
//    QPixmap* currentPix;
    
  private:
    SvRlsDataBuffering* rls;
    QString caption;
    quint32 port;
    QTimer timer;
    float angle;
    int draw_points_per_line;
    QImage* background;
    
//    GraphicsView *graphicsView;
//    QSlider *zoomSlider;
    
//  private slots:
//    void setupMatrix(qreal scaleXY = 0);
    
  protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    
  public slots:
    void drawLine(int lineNum);
    void stop();
    
};

#pragma pack(push,1)
struct StandartRLS {
      uchar dollarChar;  // символ '$' (0x24 = 36)
        int latitude;    // широта места установки радара
        int longitude;   // долгота места установки радара
    quint16 discret;    // цена одного дискрета в мм
    quint16 lineNum;    // номер линейки 0..4095
    quint16 lineLen;    // размер линейки 0..4104
      uchar reserve;     // всегда 0
      uchar checkSum1;   // контрольная сумма 1 (байты 0-15 с переполнением)
      uchar checkSum2;   // контрольная сумма 2 (байты 0-16 с переполнением
    quint64 lineDT;     // время прихода линейки, UTC
    // дальше - собственно линейка данных
};
#pragma pack(pop)

#define Header2bitSize 13
#pragma pack(push,1)
struct Header2bit {
   quint8 dollarChar;  // символ '$' (0x24 = 36)
      int latitude;    // широта места установки радара
      int longitude;   // долгота места установки радара
  quint32 reserved; 
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

class SvRlsDataBuffering : public QThread
{
    Q_OBJECT
  public:
    explicit SvRlsDataBuffering(void* buffer,
                                quint16 port,
                                QObject *parent = 0);
    
    ~SvRlsDataBuffering();
    
    void* buffer;
    int* firstLineNum;
    int* lastLineNum;
    
    bool isPlaying() { return _playing; }

  private:
    QUdpSocket *socket;
    quint16 port;
//    QByteArray *datagram;
    int linesCount;
    int pointPerLine;
    int bitPerPoint;
    bool _playing = true;
    
  protected:
    void run() Q_DECL_OVERRIDE;
    
  signals:
    void lineUpdated(int lineNum);
    
  public slots:
    void stop() { _playing = false; }
    
  private slots:
//    void readPendingDatagrams();

    
};

class SvSingleRlsWindow: public QDialog
{
    Q_OBJECT
      
  public:
    explicit SvSingleRlsWindow(quint16 port,
                               QString device_name,
                               QString title,
                               int width = 640,
                               int height = 640);
    ~SvSingleRlsWindow();
    
  private:
    QVBoxLayout* vlay;
    SvRls2BitWidget* rls;
    
  private slots:
    void reject();
};

class SvSelectRlsArchWindow: public QDialog
{
    Q_OBJECT
      
  public:
    explicit SvSelectRlsArchWindow();
    ~SvSelectRlsArchWindow();
    
    quint16 DataPort() { return data_port; }
    QString DeviceName() { return device_name; }
    QDateTime DateTimeBegin() { return dateTimeBegin; }
    QDateTime DateTimeEnd() { return dateTimeEnd; }
    
  private:
//    SvRls2BitWidget* rls;
    QList<int>devIdList; 

    QGroupBox *groupBox;
    QVBoxLayout *vlay;
    QVBoxLayout *vlay_2;
    QHBoxLayout *hlayDevice;
    QLabel *lblDevice;
    QComboBox *cbDevice;
    QHBoxLayout *hlayBegin;
    QLabel *lblBegin;
    QDateTimeEdit *dtBegin;
    QHBoxLayout *hlayEnd;
    QLabel *lblEnd;
    QDateTimeEdit *dtEnd;
    QHBoxLayout *hlayButtons;
    QSpacerItem *spacer;
    QPushButton *bnStart;
    QPushButton *bnStop;
    QHBoxLayout *hlayServer;
    QLabel *lblIP;
    QLineEdit* editIP;
    QLabel *lblPort;
    QSpinBox* sbPort;
    
    SvRls2BitWidget* rlswdg;
    
    QString server_ip;
    quint16 server_port;
    quint16 data_port;
    
    int device_id;
    QString device_name;
    QDateTime dateTimeBegin;
    QDateTime dateTimeEnd;
    
  private slots:
//    void accept();
    void slotStart();
    void slotStop();
};

#endif // SVRLSWIDGET_H
