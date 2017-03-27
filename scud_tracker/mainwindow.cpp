#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../demo_1/COMMON/log.h"
#include "../demo_1/COMMON/sql_select_defs.h"
#include "../demo_1/COMMON/sv_secondmeter.h"
#include "../demo_1/COMMON/sv_pgdb.h"
#include "../demo_1/COMMON/sv_settings.h"
#include "../demo_1/COMMON/sql_select_defs.h"

using namespace log_ns;

//SvTcpServer* tcp_server = 0;
QThread* thr;
extern SvPGDB* PGDB;

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
  
  tcp_server = new SvTcpServer(35580, false, this, false, false, false, false, debug);

  connect(ui->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(ui->bnStop, SIGNAL(pressed()), this,  SLOT(slotStop()));
  connect(tcp_server, SIGNAL(sigClientDisconnected()), this, SLOT(slotGotMessage()));
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
  tcp_server->startServer(35580);
  
  ui->bnStart->setEnabled(false);
  ui->bnStop->setEnabled(true);
}

void MainWindow::slotStop()
{
  tcp_server->stopServer();
  
  ui->bnStart->setEnabled(true);
  ui->bnStop->setEnabled(false);
}

void MainWindow::slotGotMessage()
{
  GotKeyStruct* gotKey = reinterpret_cast<GotKeyStruct*>(malloc(sizeof(GotKeyStruct)));
  memset(gotKey, char(0), sizeof(GotKeyStruct));
  memcpy(gotKey, tcp_server->last_message, sizeof(GotKeyStruct));
  
  /* номер считывателя */
  t_scud_number = int(gotKey->scud_number);
  t_code = t_scud_number >> 4;
  t_scud_number = t_scud_number & 0x0f;
  
  /* сам ключ */
  t_key = 0;
  memcpy(&t_key, &gotKey->key_byte1, 3);
  
  /* дата и время */
  QDate d = QDate((gotKey->year  >> 4) * 10 + (gotKey->year  & 0x0F),
                  (gotKey->month >> 4) * 10 + (gotKey->month & 0x0F),
                  (gotKey->day   >> 4) * 10 + (gotKey->day   & 0x0F));
  
  QTime t = QTime((gotKey->hour >> 4) * 10 + (gotKey->hour & 0x0F),
                  (gotKey->min  >> 4) * 10 + (gotKey->min  & 0x0F),
                  (gotKey->sec  >> 4) * 10 + (gotKey->sec  & 0x0F));

//  QDateTime t_date_time;
  t_date_time.setDate(d);
  t_date_time.setTime(t);
  
  /** временно ! */
  t_date_time.setDate(QDateTime::currentDateTime().date());
  t_date_time.setTime(QDateTime::currentDateTime().time());
  /** ********* **/
  
  /* день недели */
//  int t_weekday = gotKey->weekday;
  
  QSqlError err = PGDB->execSQL(QString("insert into scud_history "
                                        "(key_value, sensor_number, date_time, ip) "
                                        "values(%1, %2, '%3', '%4')")
                                        .arg(t_key)
                                        .arg(t_scud_number)
                                        .arg(t_date_time.toString("dd/MM/yy hh:mm:ss"))
                                        .arg(tcp_server->lastClientIp), debug);

  if(err.type() != QSqlError::NoError)
  {
    log_ns::log(m_Err, err.databaseText());
    return;
  }
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString(D_SELECT_FROM_SCUDS_WHERE).arg("key_value").arg(t_key), q, debug);
  q->first();
  
  QSqlQuery* q1 = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString("select device_name from devices where ip = '%1'").arg(tcp_server->lastClientIp), q1, debug);
  q1->first();

  log_ns::log(m_Data, QString("Ключ: %1  Сотрудник: <%2 %3. %4.>   Время прохода: %5  Дверь: %6  Считыватель: %7  Код: %8")
                .arg(t_key)
                .arg(q->value("employee_surename").toString())
                .arg(q->value("employee_name").toString() == "" ? '\0' : q->value("employee_name").toString().at(0))
                .arg(q->value("employee_patronymic").toString() == "" ? '\0' : q->value("employee_patronymic").toString().at(0))     
                .arg(t_date_time.toString("dd.MM.yy hh:mm:ss"))
                .arg(QString("%1 (%2)").arg(q1->value("device_name").toString()).arg(tcp_server->lastClientIp))
                .arg(t_scud_number)
                .arg(t_code));
    
  q->~QSqlQuery();
  q1->~QSqlQuery();
  free(q);
  free(q1);
//  pg->~SvPGDB();
  
}


void MainWindow::on_bnTest_clicked()
{
//  PGDB->execSQL("EXEC PROCEDURE")
}
