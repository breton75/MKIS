#ifndef SVVIDEOWINDOW_H
#define SVVIDEOWINDOW_H

#include "./COMMON/sv_ffmpeg.h"

#include <QObject>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QList>
#include <QTableView>
#include <QApplication>
#include <QStringList>
#include <QList>
#include <QStandardItem>
#include <QTextCodec>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QMap>
#include <QMutex>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>

#include <QDebug>

class SvVideoViewWindow : public QWidget // QMdiSubWindow
{
    Q_OBJECT
      
  public:
    explicit SvVideoViewWindow(QMdiArea* parent,
                               QString title,
                               int width = 600,
                               int height = 400);
    ~SvVideoViewWindow();
    
    QComboBox* cbCameraList;
    QWidget* widgetVideo;
    QPushButton* bnPlay;
    
    QStringList* paths;
    
  public slots:
    void slotPlay();
    
  private slots:
    void slotVideoClick(int index);
    
    
};

class SvSingleVideoWindow: public QDialog
{
    Q_OBJECT
      
  public:
    explicit SvSingleVideoWindow(QString link,
                                 QString device_name,
                                 QString title,
                                 int width = 600,
                                 int height = 400);
    ~SvSingleVideoWindow();
    
  private:
    QVBoxLayout* vlay;
    SvFFMpegWidget* ffm;
    
  private slots:
//    void on_reject();
};

#endif // SVVIDEOWINDOW_H
