#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../demo_1/COMMON/log.h"
#include "../demo_1/COMMON/sql_select_defs.h"
#include "../demo_1/COMMON/sv_secondmeter.h"
#include "../demo_1/COMMON/sv_pgdb.h"
#include "../demo_1/COMMON/sv_settings.h"
#include "../demo_1/COMMON/sql_select_defs.h"
#include "../demo_1/sv_rls2bittofile.h"
#include "../demo_1/COMMON/sv_rls2bit2filesettings.h"
#include "../demo_1/COMMON/sv_tcpserverclient.h"

using namespace log_ns;

//SvTcpServer* tcp_server = 0;
extern SvPGDB* PGDB;
extern SvRls2bit2FileSettings* RLS2BIT_2F_SETTINGS_UI;

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
  PGDB->execSQL("select id, device_name from devices where device_class = 'РЛС'", q);
  
  while(q->next())
  {
    devIdList.append(q->value("id").toInt()); // обязательно, сначала добавляем индекс
    ui->comboBox->addItem(q->value("device_name").toString());
  }
  q->finish();
  free(q);
      
  connect(ui->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(ui->bnStop, SIGNAL(pressed()), this,  SLOT(slotStop()));
  
  tcp_server = new SvTcpServer(35000, false, this, debug, true, debug, true, debug);
  tcp_server->startServer(35000);
  connect(tcp_server, SIGNAL(sigGotMessage()), this, SLOT(slotGotMessage()));
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
  RlsArchSettings as  = parseRlsConfig(cfg);
  
  if(as.port == 0)  {
    QMessageBox::critical(this, "Ошибка", "Не указан порт для прослушивания", QMessageBox::Ok);
    return;  }
  
  QDir d(as.path_to_save_file); 
  if(!d.exists())  {
    QMessageBox::critical(this, "Ошибка", "Не верный путь для сохранения файлов", QMessageBox::Ok);
    return;  }  
  
  if(as.file_duaration < QTime(0, 0, 10))  {
    QMessageBox::critical(this, "Ошибка", "Время записи файла меньше допустимого предела", QMessageBox::Ok);
    return;  }

  if((as.rotation_speed < 1) | (as.rotation_speed > 8))  {
    QMessageBox::critical(this, "Ошибка", "Скорость вращения вне допустимых пределов", QMessageBox::Ok);
    return;  }  
  

  rls2file = new SvRlsDataToFile(as.port,
                                 as.rotation_speed,
                                 as.path_to_save_file,
                                 current_device_name,
                                 as.user_name,
                                 as.file_duaration,
                                 as.total_duration,
                                 as.datetime_format,
                                 as.file_name_format);
                              

  rls2file->start();

  connect(rls2file, SIGNAL(NewFile()), this, SLOT(slotNewFile()));
  connect(rls2file, SIGNAL(TimeElapsed()), this, SLOT(slotFileFinished()));
  connect(rls2file, SIGNAL(finished()), this, SLOT(slotFinished()));
  
  ui->comboBox->setEnabled(false);
  ui->bnStart->setEnabled(false);
  ui->bnStop->setEnabled(true);  
  
//  tcp_server->startServer(35000);

}

void MainWindow::slotFinished()
{
  rls2file->~SvRlsDataToFile();
  
  log_ns::log(m_Info, QString("Recording finished\n"));
  ui->comboBox->setEnabled(true);
  ui->bnStart->setEnabled(true);
  ui->bnStop->setEnabled(false);
}

void MainWindow::slotStop()
{
  rls2file->stop();
  slotFileFinished();
}

void MainWindow::slotNewFile()
{
  begin_time = rls2file->cur_file_date_time;
  file_name = rls2file->file_name;
  
  PGDB->execSQL(QString("insert into arch_rls (record_begin, device_id, file_name, rotation_speed) "
                        "values('%1', %2, '%3', %4)")
                .arg(begin_time.toString("dd/MM/yy hh:mm:ss"))
                .arg(current_device_id)
                .arg(file_name)
                .arg(rotation_speed), debug);
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString("select max(id) from arch_rls where device_id = %1").arg(current_device_id), q, debug);
  q->first();
  last_id = q->value("max").toInt();
//  log_ns::log(m_Attention, QString("max id = %1").arg(last_id));
  q->finish();
  
  log_ns::log(m_Attention, QString("Begin recording <%1_%2>").arg(begin_time.toString("ddMMyy_hhmmss")).arg(current_device_name));
  
}

void MainWindow::slotFileFinished()
{
  log_ns::log(m_Success, QString("  End recording <%1_%2>").arg(begin_time.toString("ddMMyy_hhmmss")).arg(current_device_name));
  
  PGDB->execSQL(QString("update arch_rls set record_end = '%1' where id = %2")
                .arg(QDateTime::currentDateTime().toString("dd/MM/yy hh:mm:ss"))
                .arg(last_id), debug);  
}

void MainWindow::on_bnSettings_clicked()
{
  RLS2BIT_2F_SETTINGS_UI = new SvRls2bit2FileSettings(current_device_id);
  connect(RLS2BIT_2F_SETTINGS_UI, SIGNAL(accepted()), this, SLOT(on_RLS2BIT_2F_SETTINGS_UI_closed()));
  connect(RLS2BIT_2F_SETTINGS_UI, SIGNAL(rejected()), this, SLOT(on_RLS2BIT_2F_SETTINGS_UI_closed()));
}

void MainWindow::on_RLS2BIT_2F_SETTINGS_UI_closed()
{
  if(RLS2BIT_2F_SETTINGS_UI->result() == QDialog::Accepted)
  {
    
  }
  RLS2BIT_2F_SETTINGS_UI->~SvRls2bit2FileSettings();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  current_device_id = devIdList.at(ui->comboBox->currentIndex());
  current_device_name = ui->comboBox->currentText();
}

void MainWindow::slotGotMessage()
{
  QString c_ip = tcp_server->lastClientIp;

  log_ns::log(m_Attention,  tcp_server->lastClientIp);

  if(tcp_server->last_message.left(9) == "TRANSLATE")
  {
  
    QDate d = QDate(2015, 8, 24);
    QTime t = QTime(8, 5, 30);
    
    GotCmdStruct cmd;
    memcpy(&cmd, tcp_server->last_message.data() + 9, sizeof(GotCmdStruct));
    
    
//    log_ns::log(m_Attention, QString("port=%1  device_id=%2  begin=%3  end=%4")
////                .arg(cmd.cmd)
//                .arg(cmd.port)
//                .arg(cmd.device_id)
//                .arg(cmd.begin_date_dime)
//                .arg(cmd.end_date_dime));
    
    archDataPort = cmd.port;
    
    rls2udp = new SvRls2bitFile2Udp(c_ip,
                                    cmd.port,
                                    QDateTime::fromTime_t(cmd.begin_date_dime), //QDateTime(d, t),
                                    QDateTime::fromTime_t(cmd.end_date_dime),
                                    cmd.device_id);
    
    connect(rls2udp, SIGNAL(NoRecords()), this, SLOT(slotNoRecords()));
    connect(rls2udp, SIGNAL(NewFile()), this, SLOT(slotNewFileTraslation()));
    connect(rls2udp, SIGNAL(WrongFile()), this, SLOT(slotWrongFileTraslation()));
    connect(rls2udp, SIGNAL(finished()), this, SLOT(slotTranslationFinished()));
    
    rls2udp->start();
    
  }
  else if(tcp_server->last_message.left(14) == "STOP:TRANSLATE")
  {
    rls2udp->stop();
  }
  
}

void MainWindow::slotNoRecords()
{
  log_ns::log(m_Fail, "Нет подходящих записей для трансляции");
}

void MainWindow::slotNewFileTraslation()
{
  log_ns::log(m_Attention, QString("Транслируется файл: %1 на порт %2").arg(QFileInfo(rls2udp->CurrentFileName()).fileName())
                                                                       .arg(archDataPort));
}

void MainWindow::slotWrongFileTraslation()
{
  log_ns::log(m_Fail, QString("Файл недоступен для чтения: %1").arg(QFileInfo(rls2udp->CurrentFileName()).fileName()));
}


void MainWindow::slotTranslationFinished()
{
  rls2udp->~SvRls2bitFile2Udp();
  
  log_ns::log(m_Success, "Трансляция завершена\n");
}


