#ifndef SVFFMPEG_H
#define SVFFMPEG_H

#include <QThread>
#include <QImage>
#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QOpenGLWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QIcon>
#include <QTextOption>
#include <QDir>
#include <QMutex>
#include <QApplication>

class Svffmpeg;
    
class SvFFMpegWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit SvFFMpegWidget(int index,
                            QString media_path,
                            int width,
                            int height,
                            int posX,
                            int posY,
                            QString caption,
                            int delay = 0,
                            QString path_to_save_frames = "c:/frames/");
    
    ~SvFFMpegWidget();
    
    int index;
    QString media_path;
    QImage img;
    void* _img;
    int img_size;
    Svffmpeg *ffmpg;
    QString caption;
    int delay;
    
        
    void setDrawRect(bool draw) { drawRect = draw; }

  private:
    bool drawRect = false;
    
  protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *) Q_DECL_OVERRIDE; 
    
    
  signals:
    void sigStop();
    void sigSettings();
    void sigSaveFrame();
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void clicked(int index);
    
    
  public slots:
    virtual void slotStop();
    virtual void slotSettings();
    virtual void slotSaveFrame();
    
  private slots:
    void slotClicked(QMouseEvent * event);
    
};

class Svffmpeg : public QThread
{
    Q_OBJECT
    
  public:
    explicit Svffmpeg(QString media_path,
                      void* _img,
//                      QImage *img,
                      int width,
                      int height,
                      int delay,
                      QString path_to_save_frames);
    ~Svffmpeg();
    
    QString media_path;
//    QImage *img;
    int img_width;
    int img_height;
    void* _img;
    bool isConnecting = true;
    int delay;
     
    bool isPlaying() { return _playing; }
    void stop() { _playing = false; }
    
    QString path_to_save_frames;
    
    bool saveframe = false;
    
    virtual void run() Q_DECL_OVERRIDE;
    
  signals:
    void sigImgLoaded();
    
  private:
    bool _playing = true;
    
//  public slots:
    
};

class SvFFMpegObject: public QObject
{
  Q_OBJECT
    
  public:
    explicit SvFFMpegObject();
    
};


#endif // SVFFMPEG_H
