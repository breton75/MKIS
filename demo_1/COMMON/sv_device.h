#ifndef SV_DEVICETYPE_H
#define SV_DEVICETYPE_H

#include <QDialog>
#include <QString>
#include "ui_device.h"
#include "sv_zone_list.h"
#include <QSqlError>

namespace Ui {
  class SvDeviceDialog;
}

class SvDevice : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvDevice(QWidget *parent,
                      QString deviceName = "",
                      int showMode = smNew);
 
    
    ~SvDevice();
    
    int showMode;
    
    int     t_id;
    QString t_deviceName = "";
    QString t_ip = "";
    int t_port = 0;
    int t_model_id = -1; // модель может быть не выбрана
    QString t_modelName = "";
    QString t_className = "";
    QString t_brandName = "";
    QString t_driverPath = "";
    QString t_videoPath = "";
    QString t_zoneName = "";
    float   t_X = 0;
    float   t_Y = 0;
//    int     t_Z;
    QString t_description = "";
    
     
  private slots:
    void on_DEVMODELSLIST_UI_closed();
    void on_DEVMODEL_UI_closed();
    void on_ZONELIST_UI_closed();
    void on_ZONE_UI_closed();
    
    void on_bnSelectZone_clicked();
    void on_bnNewZone_clicked();
    void on_NEW_ZONE_UI_closed();
    void on_bnSelectPosition_clicked();
    
  public slots:
    void accept() Q_DECL_OVERRIDE;
    void slotNewModel();
    void slotSelectModel();
    
  private:
    Ui::SvDeviceDialog *Dialog;

};

#endif // SV_DEVICETYPE_H
