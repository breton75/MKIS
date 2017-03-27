#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sv_treeview.h"
#include "sv_deviceswindow.h"
#include "./COMMON/sv_device.h"
#include "sv_videoviewwindow.h"
#include "sv_zoneswindow.h"
#include "sv_zone.h"
#include "sv_alarmswindow.h"
#include "./COMMON/sv_settings.h"
#include "./COMMON/sv_pgdb.h"
#include "./COMMON/log.h"

using namespace log_ns;

SvTreeView* tree;
extern SvDevice* DEV_UI;
extern SvZone* ZONE_UI;
extern SvDevicesWindow* DEV_WINDOW_UI;
extern SvAlarmsWindow* ALARMS_UI;

extern SvPGDB* PGDB;

QList<QAction*> aLst;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  tree = new SvTreeView(ui->dockWidgetContents, ui->mdiArea);
  ui->verticalLayout->addWidget(tree);
  
//  tree->loadDevices();
//  tree->loadVars();
//  tree->loadZones();
//  tree->loadEmployees();
//  tree->loadView();
//  tree->loadArchiving();
  
  /** *************** контекстные меню ***************** **/
  
  /* устройства */
//  tree->actionsDevices->append(ui->actionDevices);
//  tree->actionsDevices->append(ui->actionNewDevice);
  
//  /* просмотр видео */
//  tree->actionsVideoView->append(ui->actionVideoView);
  
//  tree->actionsPlans->append(ui->actionPlans);
  
  /** ****** дерево тревожных событий ****** **/
//  alarm_tree = new SvAlarmTreeView(ui->alarmDockWidgetContent);
//  ui->verticalLayout_3->addWidget(alarm_tree);
  
  
//  /** ****** запускаем отслеживание переменных ****** **/
//  vtrk = new SvVarsTracker(this, 1000);
//  vtrk->start();
 
}

MainWindow::~MainWindow()
{
  vtrk->~SvVarsTracker();
  delete ui;
}

QTextEdit* MainWindow::get_log()
{
  return ui->textLog;
}

void MainWindow::AfterShow()
{
  tree->loadDevices();
  tree->loadVars();
  tree->loadZones();
  tree->loadKeys();
  tree->loadEmployees();
  tree->loadView();
  tree->loadArchiving();
  
  alarm_tree = new SvAlarmTreeView(ui->alarmDockWidgetContent);
  ui->verticalLayout_3->addWidget(alarm_tree);
  
  
  /** ****** запускаем отслеживание переменных ****** **/
  vtrk = new SvVarsTracker(this, 1000);
  vtrk->start();
  
  connect(vtrk, SIGNAL(alarm(QString,qreal)), this, SLOT(on_alarm(QString,qreal)));
//  connect(tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(treatDoubleClick(QModelIndex)));
  
  tcp_server = new SvTcpServer(35581, true, this, false, false, false, false, true);
  connect(tcp_server, SIGNAL(sigClientDisconnected()), this, SLOT(slotGotMessage()));
  
  ui->mainToolBar->insertAction(ui->actionEmployeers, tree->actionDevices);
  ui->mainToolBar->insertAction(ui->actionEmployeers, tree->actionZones);
  
}

void MainWindow::slotGotMessage()
{
  GotKeyStruct2* gotKey = reinterpret_cast<GotKeyStruct2*>(malloc(sizeof(GotKeyStruct2)));
  memset(gotKey, char(0), sizeof(GotKeyStruct2));
  memcpy(gotKey, tcp_server->last_message, sizeof(GotKeyStruct2));
  
  /* номер считывателя */
  t_scud_number = int(gotKey->scud_number);
  t_code = t_scud_number >> 4;
  t_scud_number = t_scud_number && 0x0f;
  
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
  
  /* день недели */
//  int t_weekday = gotKey->weekday;
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString(D_SELECT_FROM_SCUDS_WHERE).arg("key_value").arg(t_key), q, true);
  q->first();
  
  QSqlQuery* q1 = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString("select device_name from devices where ip = '%1'").arg(tcp_server->lastClientIp), q1, true);
  q1->first();

  t_employee_name = q->value("employee_name").toString();
  t_surename = q->value("employee_surename").toString();
  t_employee_patronymic = q->value("employee_patronymic").toString();
  t_device_name = q1->value("device_name").toString();
  t_device_ip = tcp_server->lastClientIp;
  
  log_ns::log(m_Data, QString("Ключ: %1  Сотрудник: <%2 %3. %4.>   Время прохода: %5  Дверь: %6  Считыватель: %7  Код: %8")
                .arg(t_key)
                .arg(t_surename)
                .arg(t_employee_name == "" ? '\0' : t_employee_name.at(0))
                .arg(t_employee_patronymic == "" ? '\0' : t_employee_patronymic.at(0))     
                .arg(t_date_time.toString("dd.MM.yy hh:mm:ss"))
                .arg(QString("%1 (%2)").arg(t_device_name).arg(t_device_ip))
                .arg(t_scud_number)
                .arg(t_code));
    
  q->~QSqlQuery();
  q1->~QSqlQuery();
  free(q);
  free(q1);

  // поднимаем тревогу
  if(t_surename == "")
  {
    alarm_tree->newAlarm(t_device_ip, qreal(t_scud_number));
  }
  
}

//void MainWindow::treatDoubleClick(QModelIndex idx)
//{
  
//  switch (tree->treeModel->itemFromIndex(idx)->type())
//  {
//    case itDevice:
//    {
//      DEV_UI = new SvDevice(this, idx.data().toString());
//      connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
//      connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
//      break;
//    }
      
//    case itZone:
//    {
//      ui->actioneditZone->trigger();
//      break;
//    }
      
//    case itAlarms:
//    {
//      on_actionAlarms_triggered();        
//      break;
//    }
//  }    
  
//}

void MainWindow::on_alarm(QString var, qreal value)
{
  
  alarm_tree->newAlarm(var, value);
}

//void MainWindow::on_DEV_UI_closed()
//{
  
//}

//void MainWindow::on_actionDevices_triggered()
//{
//  if(!ui->mdiArea->findChild<QWidget*>(DEVICES_SUBWINDOW_NAME))
//  {
//    DEV_WINDOW_UI = new SvDevicesWindow(this,
//                                      ui->mdiArea,
//                                      "Устройства");

//    DEV_WINDOW_UI->bnAddDevice->setDefaultAction(ui->actionNewDevice);
//    DEV_WINDOW_UI->bnEditDevice->setDefaultAction(ui->actionEditDevice);
//    DEV_WINDOW_UI->bnDeleteDevice->setDefaultAction(ui->actionDeleteDevice);  
//    DEV_WINDOW_UI->show();
//  }
  
//  DEV_WINDOW_UI->setFocus();

//}

//void MainWindow::on_actionVariables_triggered()
//{
    
//}

//void MainWindow::on_actionZones_triggered()
//{
    
//}

//void MainWindow::on_actionEmployeers_triggered()
//{
    
//}

//void MainWindow::on_actionPlans_triggered()
//{
//  QList<QPointF>* lst = new QList<QPointF>;
//  SvPlansWindow* zones = new SvPlansWindow(ui->mdiArea,
//                                           "Зоны безопасности",
//                                           lst);
//  zones->show();
//}

//void MainWindow::on_actionAccess_control_triggered()
//{
    
//}

//void MainWindow::on_actionNewDevice_triggered()
//{
//  DEV_UI = new SvDevice(this, "");
//  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
//  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
//}

//void MainWindow::on_actionVideoView_triggered()
//{
//  SvVideoViewWindow* viewVideo = new SvVideoViewWindow(ui->mdiArea,
//                                                       "Просмотр видеокамер");
//  viewVideo->show();
//}

//void MainWindow::on_actioneditZone_triggered()
//{
////  qDebug() << tree->treeModel->itemFromIndex(tree->selected())->text()
////           << tree->treeModel->itemFromIndex(tree->selected())->parent()->text();
  

//}

//void MainWindow::on_ZONE_UI_closed()
//{
//  if(ZONE_UI->result() == QDialog::Accepted)
//  {
    
//  }
  
//  ZONE_UI->~SvZone();
//}



//void MainWindow::on_actionEditDevice_triggered()
//{

//}


//void MainWindow::on_actionAlarms_triggered()
//{
//  if(!ui->mdiArea->findChild<QWidget*>(ALARMS_SUBWINDOW_NAME))
//  {
//    ALARMS_UI = new SvAlarmsWindow(ui->mdiArea,
//                                   "Тревоги и события");

//    ALARMS_UI->bnAddDevice->setDefaultAction(ui->actionNewDevice);
//    ALARMS_UI->bnEditDevice->setDefaultAction(ui->actionEditDevice);
//    ALARMS_UI->bnDeleteDevice->setDefaultAction(ui->actionDeleteDevice);  
//    ALARMS_UI->show();
//  }
  
//  ALARMS_UI->setFocus();
//}


