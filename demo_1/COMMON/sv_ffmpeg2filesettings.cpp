#include "sv_ffmpeg2filesettings.h"
#include "sv_pgdb.h"

extern SvPGDB* PGDB;

SvFFmpeg2FileSettings* FF2F_SETTINGS_UI;

SvFFmpeg2FileSettings::SvFFmpeg2FileSettings(int device_id) :
  ff2f(new Ui::SvFFmpeg2FileSettingsDialog)
{
  
  ff2f->setupUi(this);
  ff2f->editDeviceName->setEnabled(false);
  
  this->device_id = device_id;
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL("select id, device_name from devices where device_class='Сервер архивации'", q);

  while(q->next())
  {
    archServerIdList.append(q->value("id").toInt()); // обязательно, сначала добавляем индекс
    ff2f->cbArchServer->addItem(q->value("device_name").toString());
  }
  q->finish();

  
  
  err = PGDB->execSQL(QString("select device_name, arch_config from devices where id=%1").arg(device_id), q);
  q->first();
  
  t_deviceName = q->value("device_name").toString();
  
  if(q->value("arch_config").toString() != "")
  {
    FFmpegArchSettings as = parseConfig(q->value("arch_config").toString());
    
    t_mediaLink  = as.media_link;
    t_saveDirectory  = as.path_to_save_file  ;  
    t_FileDuration  = as.file_duaration;    
    t_totalDurationTime  = as.total_duration;    
    t_totalDurationChecked  = as.doTotalTime;    
    t_fileNameFormat  = as.file_name_format;    
    t_dateTimeFormat  = as.datetime_format;
    t_password  = as.password;    
    t_userName  = as.user_name;    
    t_deviceTag  = as.device_tag;
    t_scale  = as.scale;    
    t_fps  = as.fps;    
    t_codec  = as.codec;
    t_archServer = as.archServerId;
  }
  q->finish();
  free(q);
  
  ff2f->editDeviceName->setText(t_deviceName);
  ff2f->editMediaLink->setText(t_mediaLink);
  ff2f->editSaveDirectory->setText(t_saveDirectory);
  ff2f->teFileDuration->setTime(t_FileDuration);
  ff2f->teTotalDuration->setTime(t_totalDurationTime);
  ff2f->checkBoxTotalDuration->setChecked(t_totalDurationChecked);
  ff2f->editFileNameFormat->setText(t_fileNameFormat);
  ff2f->editDateTimeFormat->setText(t_dateTimeFormat);
  ff2f->editPassword->setText(t_password);
  ff2f->editUserName->setText(t_userName);
  ff2f->editDeviceTag->setText(t_deviceTag); 
  ff2f->sbScale->setValue(t_scale);
  ff2f->sbFps->setValue(t_fps);
  ff2f->cbCodec->setCurrentIndex(t_codec);
  ff2f->cbArchServer->setCurrentIndex(t_archServer);
  
  connect(ff2f->bnOk, SIGNAL(pressed()), this, SLOT(accept()));
  connect(ff2f->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  
}

SvFFmpeg2FileSettings::~SvFFmpeg2FileSettings()
{
  this->close();
  this->deleteLater();
}

void SvFFmpeg2FileSettings::accept()
{
  
  t_mediaLink = ff2f->editMediaLink->text();
  t_saveDirectory = ff2f->editSaveDirectory->text();
  t_FileDuration = ff2f->teFileDuration->time();
  t_totalDurationTime = ff2f->teTotalDuration->time();
  t_totalDurationChecked = ff2f->checkBoxTotalDuration->isChecked();
  t_fileNameFormat = ff2f->editFileNameFormat->text();
  t_dateTimeFormat = ff2f->editDateTimeFormat->text();
  t_userName = ff2f->editUserName->text();
  t_password = ff2f->editPassword->text();
  t_deviceTag = ff2f->editDeviceTag->text(); 
  t_scale = ff2f->sbScale->value();
  t_fps = ff2f->sbFps->value();
  t_codec = ff2f->cbCodec->currentIndex();
  t_archServer = ff2f->cbArchServer->currentIndex();
  
  QString s = packConfig();
  PGDB->execSQL(QString("update devices set arch_config = '%1', video_path='%2' where id = %3")
                .arg(s)
                .arg(t_mediaLink)
                .arg(device_id));
  
  QDialog::accept();
}

QString SvFFmpeg2FileSettings::packConfig()
{
  QString s = QString("%1;%2;%3;%4;%5;%6;%7;%8;%9;%10;%11;%12;%13;%14")
      .arg(ff2f->editMediaLink->text())
      .arg(ff2f->editSaveDirectory->text())
      .arg(ff2f->teFileDuration->time().toString("hh:mm:ss"))
      .arg(ff2f->teTotalDuration->time().toString("hh:mm:ss"))
      .arg(ff2f->checkBoxTotalDuration->isChecked() ? "true" : "false")
      .arg(ff2f->editFileNameFormat->text())
      .arg(ff2f->editDateTimeFormat->text())
      .arg(ff2f->editUserName->text())
      .arg(ff2f->editPassword->text())
      .arg(ff2f->editDeviceTag->text())
      .arg(ff2f->cbCodec->currentIndex())
      .arg(ff2f->sbScale->value())
      .arg(ff2f->sbFps->value())
      .arg(ff2f->cbArchServer->currentIndex());
  
  
  return s;
}

FFmpegArchSettings parseConfig(QString config)
{
  FFmpegArchSettings ff;
  
  QStringList lst = QStringList();
  lst = config.split(';');

  if(lst.count() == 14)
  {
    ff.media_link = lst.at(0);
    ff.path_to_save_file = lst.at(1);
    ff.file_duaration = QTime::fromString(lst.at(2), "hh:mm:ss");
    ff.total_duration = QTime::fromString(lst.at(3), "hh:mm:ss");
    ff.doTotalTime = lst.at(4) == "true";
    ff.file_name_format = lst.at(5);
    ff.datetime_format = lst.at(6);
    ff.user_name = lst.at(7);
    ff.password = lst.at(8);
    ff.device_tag = lst.at(9);
    ff.codec = lst.at(10).toInt();
    ff.scale = lst.at(11).toInt();
    ff.fps = lst.at(12).toInt();
    ff.archServerId = lst.at(13).toInt();
  }
  
  return ff;
}
