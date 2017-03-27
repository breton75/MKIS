#ifndef SV_FFMPEG2FILESETTINGS_H
#define SV_FFMPEG2FILESETTINGS_H

#include <QDialog>
#include <QByteArray>
#include <QBuffer>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "ui_ffmpeg2filesettings.h"

struct FFmpegArchSettings
{
  QString device_name;
  QString device_tag;
  QString media_link;
  QString ip;
  quint16 port;
  QString path_to_save_file;
  QString datetime_format;
  QString file_name_format;
  QString user_name;
  QString password;
  QTime file_duaration;
  QTime total_duration;
  bool doTotalTime;
  bool doConvert; 
  int fps;
  int scale;
  int codec;
  int archServerId;
};

  FFmpegArchSettings parseConfig(QString config);



namespace Ui {
  class SvFFmpeg2FileSettingsDialog;
}

class SvFFmpeg2FileSettings : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvFFmpeg2FileSettings(int device_id);
    
    ~SvFFmpeg2FileSettings();

    int device_id;
    QString t_deviceName = "";
    QString t_mediaLink = "";
    QString t_saveDirectory = "";
    QTime   t_FileDuration = QTime(1, 0, 0);
    QTime   t_totalDurationTime = QTime(0, 0, 0);
    bool    t_totalDurationChecked = false;
    QString t_fileNameFormat = "<DATETIME>_<DEVICE_NAME>_<USER_NAME>_<CODEC>";
    QString t_dateTimeFormat = "ddMMyy_hhmmss";
    QString t_userName = "";
    QString t_password = "";
    QString t_deviceTag = ""; 
        int t_scale = 1;
        int t_fps = 30;
        int t_codec = 0;
        int t_archServer = -1;
  
  protected:
      void accept();
        
  private:
    Ui::SvFFmpeg2FileSettingsDialog *ff2f;
    QString packConfig();
    
    QList<int>archServerIdList;    
    
};

#endif // SV_FFMPEG2FILESETTINGS_H
