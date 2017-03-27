#include "sv_device.h"
#include "ui_device.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_dev_model.h"
#include "sv_dev_models_list.h"
#include "./COMMON/sv_settings.h"
#include "./sv_zone.h"

#include <QMessageBox>
#include <QDebug>

using namespace sql_insert_defs;
using namespace sql_select_defs;

SvDevice *DEV_UI;
extern SvDevModelsList *DEVMODELSLIST_UI;
extern SvDevModel* DEVMODEL_UI;
extern SvZone* ZONE_UI;
extern SvNewZone* NEW_ZONE_UI;
extern SvZonesList *ZONELIST_UI;

SvDevice::SvDevice(QWidget *parent,
                   QString deviceName,
                   int showMode) :
  QDialog(parent),
  Dialog(new Ui::SvDeviceDialog)
{
 
  this->showMode = showMode;
  
  if(showMode == smEdit)
  {
    QString s = QApplication::applicationDirPath() + "/ini/devices.ini";
    SvSettings* sett = new SvSettings(s);
    
    QStringList lst = sett->appSettings->childGroups();
    for(int i = 0; i < lst.count(); i++)
    {
      s = sett->readValue(lst.at(i), "device", "").toString();
      if(s.section('%', 1, 1) == deviceName)
      {
        this->t_deviceName = deviceName;
        this->t_className = s.section('%', 2, 2);
        this->t_brandName = s.section('%', 3, 3); 
        this->t_modelName = s.section('%', 4, 4);
        this->t_ip = s.section('%', 5, 5);
        this->t_port = s.section('%', 6, 6).toInt();
        this->t_zoneName = s.section('%', 7, 7);
        this->t_X = s.section('%', 9, 9).toFloat();
        this->t_X = s.section('%', 10, 10).toFloat();
      }
    }
  }
  
  Dialog->setupUi(this,
                  t_deviceName,
                  t_ip,
                  t_port,
                  t_modelName,
                  t_className,
                  t_brandName,
                  t_libPath,
                  t_description,
                  t_zoneName,
                  t_X,
                  t_Y,
                  0,
                  showMode);  
  
  Dialog->editDevName->setReadOnly(showMode != smNew);
  
  connect(Dialog->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  connect(Dialog->bnNewModel, SIGNAL(pressed()), this, SLOT(slotNewModel()));
  connect(Dialog->bnSelectModel, SIGNAL(pressed()), this, SLOT(slotSelectModel()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
}

SvDevice::~SvDevice()
{
  this->close();
  delete Dialog;
}

void SvDevice::accept()
{
  
  /* делаем всякие проверки вводимых данных */
  if(Dialog->editDevName->text() == "")
  {
    Dialog->editDevName->setFocus();
    return;
  }
  
  if(Dialog->editIP->text() == "")
  {
    Dialog->editIP->setFocus();
    return;
  }  
  
  if((Dialog->editPort->text() == "") || (Dialog->editPort->text().toInt() == 0))
  {
    Dialog->editPort->setFocus();
    return;
  }   
  
  if((Dialog->editClass->text() == "") || (Dialog->editDriver->text() == ""))
  {
    Dialog->bnSelectModel->setFocus();
    return;
  }
  /* конец проверок */
  
  t_id = Dialog->editID->text().toInt();
  t_deviceName = Dialog->editDevName->text();
  t_ip = Dialog->editIP->text();
  t_port = Dialog->editPort->text().toInt();
  t_modelName  = Dialog->editModelName->text();
  t_className  = Dialog->editClass->text();
  t_brandName  = Dialog->editBrand->text();
  t_libPath    = Dialog->editDriver->text();
  t_zoneName   = Dialog->editZoneName->text();
  t_X = Dialog->editPositionX->text().toFloat();
  t_Y = Dialog->editPositionY->text().toFloat();
//  t_Z = Dialog->sbZ->value();
  t_description = Dialog->textDescription->toPlainText();
  
  char groupName;
  QString s = qApp->applicationDirPath() + "/ini/devices.ini";
  SvSettings* sett = new SvSettings(s);
  QStringList lst = sett->appSettings->childGroups();

  switch (this->showMode)
  {
    case smNew:
    {
      if(lst.count())
      {
        groupName = lst.last().at(0).toLatin1();
        if(groupName == 'z') return;
        groupName = groupName++;
      }
      else groupName = 'a';
      break;
    }
      
    case smEdit:
    {
      for(int i = 0; i < lst.count(); i++)
      {
        s = sett->readValue(lst.at(i), "device", "").toString();
        if(s.section('%', 1, 1) == t_deviceName)
        {
          groupName = lst.at(i).at(0).toLatin1();
          break;
        }
      }
      break;
    }
  }
  
  sett->writeValue(QString("%1").arg(groupName), "device", QString("\%%1\%%2\%%3\%%4\%%5\%%6\%%7\%%8\%%9\%%10\%")
                                                      .arg(t_deviceName)
                                                      .arg(t_className)
                                                      .arg(t_brandName)
                                                      .arg(t_modelName)
                                                      .arg(t_ip)
                                                      .arg(t_port)
                                                      .arg(t_zoneName)
                                                      .arg("")
                                                      .arg(t_X)
                                                      .arg(t_Y));
  
  QDialog::accept(); // this->setResult(QDialog::Accepted);
  
}

void SvDevice::slotSelectModel()
{
  DEVMODELSLIST_UI = new SvDevModelsList(this, false, true);
  connect(DEVMODELSLIST_UI, SIGNAL(accepted()), this, SLOT(on_DEVMODELSLIST_UI_closed()));
  connect(DEVMODELSLIST_UI, SIGNAL(rejected()), this, SLOT(on_DEVMODELSLIST_UI_closed()));
 }
  
void SvDevice::on_DEVMODELSLIST_UI_closed()
{
  int i = DEVMODELSLIST_UI->result();
  if(i == QDialog::Accepted)
  {
    this->t_model_id = DEVMODELSLIST_UI->t_id;
    Dialog->editModelName->setText(DEVMODELSLIST_UI->t_modelName);
    Dialog->editBrand->setText(DEVMODELSLIST_UI->t_brandName);
    Dialog->editClass->setText(DEVMODELSLIST_UI->t_className);
    Dialog->editDriver->setText(DEVMODELSLIST_UI->t_libPath); 
  }
     
  DEVMODELSLIST_UI->~SvDevModelsList();
  
}

void SvDevice::slotNewModel()
{
  DEVMODEL_UI = new SvDevModel(this);
  connect(DEVMODEL_UI, SIGNAL(accepted()), this, SLOT(on_DEVMODEL_UI_closed()));
  connect(DEVMODEL_UI, SIGNAL(rejected()), this, SLOT(on_DEVMODEL_UI_closed()));
}

void SvDevice::on_DEVMODEL_UI_closed()
{
  if(DEVMODEL_UI ->result() == QDialog::Accepted)
  {
    Dialog->editModelName->setText(DEVMODEL_UI->t_modelName);
    Dialog->editBrand->setText(DEVMODEL_UI->t_brandName);
    Dialog->editClass->setText(DEVMODEL_UI->t_className);
    Dialog->editDriver->setText(DEVMODEL_UI->t_libPath);
  }
  
  DEVMODEL_UI->~SvDevModel();
}

void SvDevice::on_bnSelectZone_clicked()
{
  ZONELIST_UI = new SvZonesList(this, false, false);
  connect(ZONELIST_UI, SIGNAL(accepted()), this, SLOT(on_ZONELIST_UI_closed()));
  connect(ZONELIST_UI, SIGNAL(rejected()), this, SLOT(on_ZONELIST_UI_closed()));
}

void SvDevice::on_ZONELIST_UI_closed()
{
  if(ZONELIST_UI->result() == QDialog::Accepted)
  {
    Dialog->editZoneName->setText(ZONELIST_UI->t_zoneName);
//    on_bnSelectPosition_clicked();
  }
  ZONELIST_UI->~SvZonesList();
}

void SvDevice::on_bnNewZone_clicked()
{
  NEW_ZONE_UI = new SvNewZone(this);
  connect(NEW_ZONE_UI, SIGNAL(accepted()), this, SLOT(on_NEW_ZONE_UI_closed()));
  connect(NEW_ZONE_UI, SIGNAL(rejected()), this, SLOT(on_NEW_ZONE_UI_closed()));
}

void SvDevice::on_NEW_ZONE_UI_closed()
{
  if(NEW_ZONE_UI->result() == QDialog::Accepted)
  {
    QString s = NEW_ZONE_UI->t_zoneName;
    ZONE_UI = new SvZone(s, true, this);

    connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
    connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
  }
  
  NEW_ZONE_UI->~SvNewZone();
}

void SvDevice::on_bnSelectPosition_clicked()
{
  if(Dialog->editZoneName->text() == "") return;
  
  QString planName = "";
  QString zoneName = Dialog->editZoneName->text();
  
  QString s = QApplication::applicationDirPath() + "/ini/zones.ini";
  SvSettings* zsett = new SvSettings(s);
  
  QStringList lst = zsett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    s = zsett->readValue(lst.at(i), "zone", "").toString();
    if(s.section('%', 1, 1) == zoneName)
    {
      planName = s.section('%', 2, 2);
      break;
    }
  }
  
  if(planName == "") return;
  
  ZONE_UI = new SvZone(zoneName,
                       true,
                       this);
  
  connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
  connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
 
}

void SvDevice::on_ZONE_UI_closed()
{
  if(ZONE_UI->result() == QDialog::Accepted)
  {
    QString s = QApplication::applicationDirPath() + "/ini/devices.ini";
    SvSettings* dsett = new SvSettings(s);
    
    QStringList lst = dsett->appSettings->childGroups();
    for(int i = 0; i < lst.count(); i++)
    {
      s = dsett->readValue(lst.at(i), "device", "").toString();
      if((s.section('%', 1, 1) == Dialog->editDevName->text()) &
         (s.section('%', 7, 7) == Dialog->editZoneName->text()))
      {
        Dialog->editPositionX->setText(s.section('%', 9, 9));
        Dialog->editPositionY->setText(s.section('%', 10, 10));
        break;
      }
    }
  }
  ZONE_UI->~SvZone();
}
