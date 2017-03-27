#include "sv_rls2bit2filesettings.h"
#include "sv_pgdb.h"

extern SvPGDB* PGDB;

SvRls2bit2FileSettings* RLS2BIT_2F_SETTINGS_UI;

SvRls2bit2FileSettings::SvRls2bit2FileSettings(int device_id) :
  ui(new Ui::SvRls2bit2FileSettingsDialog)
{
  
  ui->setupUi(this);
  ui->editDeviceName->setEnabled(false);
  
  this->device_id = device_id;
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL("select id, device_name from devices where device_class='Сервер архивации'", q);

  while(q->next())
  {
    archServerIdList.append(q->value("id").toInt()); // обязательно, сначала добавляем индекс
    ui->cbArchServer->addItem(q->value("device_name").toString());
  }
  q->finish();
  
  
  err = PGDB->execSQL(QString("select device_name, arch_config from devices where id=%1").arg(device_id), q);
  q->first();
  
  t_deviceName = q->value("device_name").toString();
  
  if(q->value("arch_config").toString() != "")
  {
    RlsArchSettings as = parseRlsConfig(q->value("arch_config").toString());
    
    t_port  = as.port;
    t_rotation_speed = as.rotation_speed;
    t_saveDirectory  = as.path_to_save_file  ;  
    t_FileDuration  = as.file_duaration;    
    t_totalDurationTime  = as.total_duration;    
    t_totalDurationChecked  = as.doTotalTime;    
    t_fileNameFormat  = as.file_name_format;    
    t_dateTimeFormat  = as.datetime_format;
    t_password  = as.password;    
    t_userName  = as.user_name;    
    t_deviceTag  = as.device_tag;
    t_archServer = as.archServerId;
  }
  q->finish();
  free(q);
  
  ui->editDeviceName->setText(t_deviceName);
  ui->sbPort->setValue(t_port);
  ui->sbRotationSpeed->setValue(t_rotation_speed);
  ui->editSaveDirectory->setText(t_saveDirectory);
  ui->teFileDuration->setTime(t_FileDuration);
  ui->teTotalDuration->setTime(t_totalDurationTime);
  ui->checkBoxTotalDuration->setChecked(t_totalDurationChecked);
  ui->editFileNameFormat->setText(t_fileNameFormat);
  ui->editDateTimeFormat->setText(t_dateTimeFormat);
  ui->editPassword->setText(t_password);
  ui->editUserName->setText(t_userName);
  ui->editDeviceTag->setText(t_deviceTag); 
  ui->cbArchServer->setCurrentIndex(t_archServer);
  
  connect(ui->bnOk, SIGNAL(pressed()), this, SLOT(accept()));
  connect(ui->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  connect(ui->bnSelectSaveDirectory, SIGNAL(pressed()), this, SLOT(slotSelectDir()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  
}

SvRls2bit2FileSettings::~SvRls2bit2FileSettings()
{
  this->close();
  this->deleteLater();
}

void SvRls2bit2FileSettings::accept()
{
  t_port = ui->sbPort->value();
  t_rotation_speed = ui->sbRotationSpeed->value();
  t_saveDirectory = ui->editSaveDirectory->text();
  t_FileDuration = ui->teFileDuration->time();
  t_totalDurationTime = ui->teTotalDuration->time();
  t_totalDurationChecked = ui->checkBoxTotalDuration->isChecked();
  t_fileNameFormat = ui->editFileNameFormat->text();
  t_dateTimeFormat = ui->editDateTimeFormat->text();
  t_userName = ui->editUserName->text();
  t_password = ui->editPassword->text();
  t_deviceTag = ui->editDeviceTag->text();
  t_archServer = ui->cbArchServer->currentIndex();
  
  QString s = packConfig();
  PGDB->execSQL(QString("update devices set arch_config = '%1' where id = %2").arg(s).arg(device_id));
  
  QDialog::accept();
}

QString SvRls2bit2FileSettings::packConfig()
{
  QString s = QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12")
      .arg(ui->sbPort->value())
      .arg(ui->editSaveDirectory->text())
      .arg(ui->teFileDuration->time().toString("hh:mm:ss"))
      .arg(ui->teTotalDuration->time().toString("hh:mm:ss"))
      .arg(ui->checkBoxTotalDuration->isChecked() ? "true" : "false")
      .arg(ui->editFileNameFormat->text())
      .arg(ui->editDateTimeFormat->text())
      .arg(ui->editUserName->text())
      .arg(ui->editPassword->text())
      .arg(ui->editDeviceTag->text())
      .arg(ui->sbRotationSpeed->value())
      .arg(ui->cbArchServer->currentIndex());
  
  return s;
}

RlsArchSettings parseRlsConfig(QString config)
{
  RlsArchSettings ff;
  
  QStringList lst = QStringList();
  lst = config.split(';');

  if(lst.count() == 12)
  {
    ff.port = lst.at(0).toInt();
    ff.path_to_save_file = lst.at(1);
    ff.file_duaration = QTime::fromString(lst.at(2), "hh:mm:ss");
    ff.total_duration = QTime::fromString(lst.at(3), "hh:mm:ss");
    ff.doTotalTime = lst.at(4) == "true";
    ff.file_name_format = lst.at(5);
    ff.datetime_format = lst.at(6);
    ff.user_name = lst.at(7);
    ff.password = lst.at(8);
    ff.device_tag = lst.at(9);
    ff.rotation_speed = lst.at(10).toInt();
    ff.archServerId = lst.at(11).toInt();
  }
  
  return ff;
}

void SvRls2bit2FileSettings::slotSelectDir()
{
  QString dirName = QFileDialog::getExistingDirectory(this,
                                                  tr("Выберите каталог"),
                                                  qApp->applicationDirPath());

  if(dirName.isEmpty()) return;
  
  ui->editSaveDirectory->setText(dirName);
}
