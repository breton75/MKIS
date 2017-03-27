#ifndef SV_ALARMDIALOG_H
#define SV_ALARMDIALOG_H

#include <QDialog>
#include <QApplication>
#include <QDialog>

#include "sv_zonedraw.h"
#include "./COMMON/sv_ffmpeg.h"

namespace Ui {
  class SvAlarmDialog;
}

class SvAlarmDialog : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvAlarmDialog(QString zoneName,
                           QString deviceName,
                           int alarmType,
                           QWidget *parent = 0);
    
    ~SvAlarmDialog();
    
  private:
    Ui::SvAlarmDialog *adlg;
    
    SvZoneDrawWidget* zdw = NULL;
    SvFFMpegWidget* ffw = NULL;
    
  private slots:
    void onClose();
    
};

#endif // SV_ALARMDIALOG_H
