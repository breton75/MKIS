#include "sv_alarmdialog.h"
#include "ui_sv_alarmdialog.h"
#include "./COMMON/sv_settings.h"

SvAlarmDialog* ALARM_DIALOG_UI;

SvAlarmDialog::SvAlarmDialog(QString zoneName,
                             QString deviceName,
                             int alarmType,
                             QWidget *parent) :
  QDialog(parent),
  adlg(new Ui::SvAlarmDialog)
{
  adlg->setupUi(this);
  
  this->setParent(parent);
  
  /** ****** находим и отображаем зону ******* **/
  
  /* находим план, который соответствует зоне */
//  QString plan_name;
  
//  QString s = QApplication::applicationDirPath() + "/ini/zones.ini";
//  SvSettings* zsett = new SvSettings(s);  
//  QStringList zlst = zsett->appSettings->childGroups();
//  for(int i = 0; i < zlst.count(); i++)
//  {
//    s = zsett->readValue(zlst.at(i), "zone", "").toString();
////    qDebug() << "zone" << s;
//    if(s.section('%', 1, 1) == zoneName)
//    {   
////      qDebug() << "plan_name" << s.section('%', 2, 2);
//      plan_name = s.section('%', 2, 2);
//      break;
//    }
//  }
  
  zdw = new SvZoneDrawWidget(adlg->pageZone);
//  zdw->updateDraw(QSize(adlg->toolBox->width(), adlg->toolBox->height()), zoneName, plan_name, false, alarmType);
  zdw->updateDraw(QSize(1008, 756), zoneName, /*plan_name, false,*/ alarmType);
  adlg->vlayZone->addWidget(zdw);
  
  
  /** определяем детальную информацию для отображения **/
  
  /* определяем класс устройства */
//  QString class_name;
//  QString link_path;
  
//  s = QApplication::applicationDirPath() + "/ini/devices.ini";
//  SvSettings* dsett = new SvSettings(s);  
//  QStringList dlst = dsett->appSettings->childGroups();
//  for(int i = 0; i < dlst.count(); i++)
//  {
//    s = dsett->readValue(dlst.at(i), "device", "").toString();
//    if(s.section('%', 1, 1) == deviceName)
//    {   
//      class_name = s.section('%', 2, 2);
//      if(class_name == "Видеокамера") link_path = s.section('%', 8, 8);
//      break;
//    }
//  }
  
//  if(class_name == "Видеокамера")
//  {
//    ffw = new SvFFMpegWidget(0, link_path,
//                             740/*adlg->pageDetails->width() - 8*/,
//                             560 /*adlg->pageDetails->width() - 68*/,
//                             0, 0, deviceName);
    
//    ffw->setParent(adlg->pageDetails);
//    adlg->vlayDetails->addWidget(ffw);
//    ffw->show();
    
//  }
  
  connect(adlg->bnIgnore, SIGNAL(clicked()), this, SLOT(reject()));
  connect(this, SIGNAL(rejected()), SLOT(onClose()));
  
  this->setModal(true);
  this->setResult(-1);
  this->show();
}

SvAlarmDialog::~SvAlarmDialog()
{
  if(this->zdw != NULL) this->zdw->~SvZoneDrawWidget();
  if(this->ffw != NULL) this->ffw->~SvFFMpegWidget();

  delete adlg;
  this->deleteLater();
}

void SvAlarmDialog::onClose()
{
  if(this->result() == QDialog::Accepted)
  {
    
  }
  
  this->~SvAlarmDialog();
}
