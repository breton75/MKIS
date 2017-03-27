#ifndef SV_RLS2BIT2FILESETTINGS_H
#define SV_RLS2BIT2FILESETTINGS_H

#include <QDialog>
#include <QByteArray>
#include <QBuffer>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QFileDialog>

#include "ui_rls2bit2filesettings.h"

struct RlsArchSettings
{
  QString device_name;
  QString device_tag;
  quint16 port;
  QString ip;
  QString path_to_save_file;
  QString datetime_format;
  QString file_name_format;
  QString user_name;
  QString password;
    QTime file_duaration;
    QTime total_duration;
     bool doTotalTime;
      int rotation_speed;
      int archServerId;
};

RlsArchSettings parseRlsConfig(QString config);



namespace Ui {
  class SvRls2bit2FileSettingsDialog;
}

class SvRls2bit2FileSettings : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvRls2bit2FileSettings(int device_id);
    
    ~SvRls2bit2FileSettings();

    int device_id;
    QString t_deviceName = "";
    quint32 t_port = 8000;
        int t_rotation_speed = 6;
    QString t_saveDirectory = "";
    QTime   t_FileDuration = QTime(1, 0, 0);
    QTime   t_totalDurationTime = QTime(0, 0, 0);
    bool    t_totalDurationChecked = false;
    QString t_fileNameFormat = "<DATETIME>_<DEVICE_NAME>_<USER_NAME>";
    QString t_dateTimeFormat = "ddMMyy_hhmmss";
    QString t_userName = "";
    QString t_password = "";
    QString t_deviceTag = ""; 
    int t_archServer = -1;
  
  protected:
      void accept();
        
  private:
    Ui::SvRls2bit2FileSettingsDialog *ui;
    QString packConfig();
    
    QList<int>archServerIdList; 
    
  private slots:
    void slotSelectDir();
    
    
};

#endif // SV_RLS2BIT2FILESETTINGS_H
