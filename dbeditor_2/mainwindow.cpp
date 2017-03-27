#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../Common/sv_device_list.h";
#include "../../Common/sv_device.h"
//#include "../../Common/sql_create_defs.h"
#include "../../Common/sv_arch_configurator.h"

#include <QSqlQueryModel>
#include <QSqlQuery>

using namespace sql_create_defs;

QSqlQueryModel* devModel;
QSqlQuery* devQuery;

SvDevice* device;

extern SvPGDB *PGDB;
extern SvDevice *DEV_UI;
extern SvArchConfigurator* ARCH_UI;

ArchConfiguration* arch_config;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  devModel = new QSqlQueryModel();
  
//   ::setupUi()
  
}

MainWindow::~MainWindow()
{
  delete ui;
}

QTextEdit* MainWindow::get_log()
{
  return ui->textLog;
}

void MainWindow::AfterShow()
{
  setDeviceListTable(devModel, ui->tblDeviceList);
}

void MainWindow::on_bnNewDevice_clicked()
{
  DEV_UI = new SvDevice(this);
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void MainWindow::on_DEV_UI_closed()
{
  if(DEV_UI->result() == QDialog::Accepted)
  {
    setDeviceListTable(devModel, ui->tblDeviceList);
  }
  
  DEV_UI->~SvDevice();
}

int setDeviceListTable(QSqlQueryModel* queryModel, QTableView* table)
{
  /* ----------- dev_list -------------*/
  
  QSqlError err = PGDB->execSQL(SELECT_DEVICE_LIST, queryModel);
  if(err.type() != QSqlError::NoError) return -1;
  
  table->setModel(queryModel);
  
  QStringList headers = QString(DEVICES_COLUMN_LIST).split(';');
  
  for(int i = 0; i < headers.count(); i++)
  {
    queryModel->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
    table->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
  }

  return 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    PGDB->execSQL(QString(CREATE_TABLE_DEVICES).arg("devices"));
}

void MainWindow::on_bnEditDevice_clicked()
{
 
  DEV_UI = new SvDevice(this, devModel->query().value("id").toInt());
  
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void MainWindow::on_bnConfigure_clicked()
{
//  QSqlRecord r = devModel->record(Dialog->tblClassesList->currentIndex().row());
//  QByteArray cfg = devModel->query().value(F_DEVICE_ID).toByteArray();
  
  ARCH_UI = new SvArchConfigurator(PGDB,/* &cfg,*/ devModel->query().value(F_DEVICE_ID).toInt());
  connect(ARCH_UI, SIGNAL(accepted()), this, SLOT(on_ARCH_UI_closed()));
  connect(ARCH_UI, SIGNAL(rejected()), this, SLOT(on_ARCH_UI_closed()));
}

void MainWindow::on_ARCH_UI_closed()
{
  if(ARCH_UI->result() == QDialog::Accepted)
  {
    
  }
  
  ARCH_UI->~SvArchConfigurator();
}
