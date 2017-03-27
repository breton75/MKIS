#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../demo_1/COMMON/log.h"
#include "../demo_1/COMMON/sql_select_defs.h"
#include "../demo_1/COMMON/sv_secondmeter.h"
#include "../demo_1/COMMON/sv_pgdb.h"
#include "../demo_1/COMMON/sv_settings.h"
#include "../demo_1/COMMON/sql_select_defs.h"
#include "../demo_1/COMMON/sv_ffmpeg2file.h"
#include "../demo_1/COMMON/sv_ffmpeg2filesettings.h"

using namespace log_ns;

//SvTcpServer* tcp_server = 0;
extern SvPGDB* PGDB;
extern SvFFmpeg2FileSettings* FF2F_SETTINGS_UI;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  SvSettings *sett = new SvSettings(s, this);
  this->resize(sett->readValue("MAIN_WINDOW", "Size", QSize(400, 200)).toSize());
  this->move(sett->readValue("MAIN_WINDOW", "Position", QPoint(100, 100)).toPoint());
  debug = sett->readValue("MAIN_WINDOW", "debug", false).toBool();
  ui->dockWidget_2->resize(sett->readValue("DOCK_WIDGET", "Size", QSize(400, 400)).toSize());
  ui->dockWidget_2->move(sett->readValue("DOCK_WIDGET", "Position", QPoint(300, 300)).toPoint());
 
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL("select id, device_name from devices where device_class = 'Видеокамера'", q);
  
  while(q->next())
  {
    devIdList.append(q->value("id").toInt()); // обязательно, сначала добавляем индекс
    ui->comboBox->addItem(q->value("device_name").toString());
  }
  q->finish();
  free(q);
      
  connect(ui->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(ui->bnStop, SIGNAL(pressed()), this,  SLOT(slotStop()));
//  connect(tcp_server, SIGNAL(sigClientDisconnected()), this, SLOT(slotGotMessage()));
//  connect(this, SIGNAL(sigDBUpdated()), this, SLOT(slotMakeLog()));
//  connect(ui->bnTest, SIGNAL(pressed()), this, SLOT(slotMakeLog()));
}

MainWindow::~MainWindow()
{
  PGDB->~SvPGDB();
  
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";

  SvSettings *sett = new SvSettings(s, this);
  sett->writeValue("MAIN_WINDOW", "Size", this->size());
  sett->writeValue("MAIN_WINDOW", "Position", this->pos());
  sett->writeValue("MAIN_WINDOW", "debug", debug);
  sett->writeValue("DOCK_WIDGET", "Size", ui->dockWidget_2->size());
  sett->writeValue("DOCK_WIDGET", "Position", ui->dockWidget_2->pos());
  delete ui;
}

void MainWindow::slotClose()
{

}

QTextEdit* MainWindow::get_log()
{
  return ui->textLog;
}

void MainWindow::AfterShow()
{

}

void MainWindow::slotStart()
{
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString(D_SELECT_FROM_DEVICES_WHERE_2).arg("id").arg(current_device_id), q, debug);
  q->first();
  
  QString ip = q->value("ip").toString();
  quint32 port = q->value("port").toInt();
  QString cfg = q->value("arch_config").toString();
  
  q->finish();
  free(q);
  
  
  if(cfg == "")  {
    QMessageBox::critical(this, "Ошибка", "Настройки архивации не заданы", QMessageBox::Ok);
    return;  }
  
  // достаем настройки архивации
  FFmpegArchSettings as  = parseConfig(cfg);
  
  if(as.media_link == "")  {
    QMessageBox::critical(this, "Ошибка", "Не указана ссылка на источник медиа", QMessageBox::Ok);
    return;  }
  
  QDir d(as.path_to_save_file); 
  if(!d.exists())  {
    QMessageBox::critical(this, "Ошибка", "Не верный путь для сохранения файлов", QMessageBox::Ok);
    return;  }  
  
  if(as.file_duaration < QTime(0, 0, 10))  {
    QMessageBox::critical(this, "Ошибка", "Время записи файла меньше допустимого предела", QMessageBox::Ok);
    return;  }
  
  
  
  ff2file = new SvFFmpeg2File(ip,
                              port,
                              as.media_link,
                              as.path_to_save_file,
                              current_device_name,
                              as.user_name,
                              as.file_duaration,
                              as.total_duration,
                              1,
                              1,
                              0,
                              as.datetime_format,
                              as.file_name_format);
                              

  ff2file->start();

  connect(ff2file, SIGNAL(NewFile()), this, SLOT(slotNewFile()));
  connect(ff2file, SIGNAL(TimeElapsed()), this, SLOT(slotFileFinished()));
  connect(ff2file, SIGNAL(finished()), this, SLOT(slotFinished()));
  
  ui->comboBox->setEnabled(false);
  ui->bnStart->setEnabled(false);
  ui->bnStop->setEnabled(true);  

}

void MainWindow::slotFinished()
{
  ff2file->~SvFFmpeg2File();
  
  log_ns::log(m_Info, QString("Recording finished\n").arg(begin_time.toString("ddMMyy_hhmmss")).arg(current_device_name));
  ui->comboBox->setEnabled(true);
  ui->bnStart->setEnabled(true);
  ui->bnStop->setEnabled(false);
}

void MainWindow::slotStop()
{
  ff2file->stopPlaying();
  slotFileFinished();
}

void MainWindow::slotNewFile(/*QDateTime dt, QString filename*/)
{
  begin_time = *ff2file->begin_time;
  file_name = *ff2file->file_name;
  
  PGDB->execSQL(QString("insert into arch_video (record_begin, device_id, file_name) values('%1', %2, '%3')")
                .arg(begin_time.toString("dd/MM/yy hh:mm:ss"))
                .arg(current_device_id)
                .arg(file_name), debug);
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString("select max(id) from arch_video where device_id = %1").arg(current_device_id), q, debug);
  q->first();
  last_id = q->value("max").toInt();
//  log_ns::log(m_Attention, QString("max id = %1").arg(last_id));
  q->finish();
  
  log_ns::log(m_Attention, QString("Begin recording <%1_%2>").arg(begin_time.toString("ddMMyy_hhmmss")).arg(current_device_name));
  
}

void MainWindow::slotFileFinished()
{
  log_ns::log(m_Success, QString("  End recording <%1_%2>").arg(begin_time.toString("ddMMyy_hhmmss")).arg(current_device_name));
  
  PGDB->execSQL(QString("update arch_video set record_end = '%1' where id = %2")
                .arg(QDateTime::currentDateTime().toString("dd/MM/yy hh:mm:ss"))
                .arg(last_id), debug);  
}

void MainWindow::on_bnSettings_clicked()
{
  FF2F_SETTINGS_UI = new SvFFmpeg2FileSettings(current_device_id);
  connect(FF2F_SETTINGS_UI, SIGNAL(accepted()), this, SLOT(on_FF2F_SETTINGS_UI_closed()));
  connect(FF2F_SETTINGS_UI, SIGNAL(rejected()), this, SLOT(on_FF2F_SETTINGS_UI_closed()));
}

void MainWindow::on_FF2F_SETTINGS_UI_closed()
{
  if(FF2F_SETTINGS_UI->result() == QDialog::Accepted)
  {
    
  }
  FF2F_SETTINGS_UI->~SvFFmpeg2FileSettings();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  current_device_id = devIdList.at(ui->comboBox->currentIndex());
  current_device_name = ui->comboBox->currentText();
}
