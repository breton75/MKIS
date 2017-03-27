#include "sv_scud.h"
#include "ui_sv_scud.h"
#include "./COMMON/log.h"
#include "./COMMON/sv_device_list.h"
#include "sv_zone.h"
#include "./COMMON/sv_zone_list.h"
#include "sv_employee.h"
#include "./COMMON/sv_employees_list.h"

using namespace log_ns;

SvSCUD* SCUD_UI;
extern SvPGDB* PGDB;
extern SvDevicesList* DEVICELIST_UI;
extern SvZone* ZONE_UI;
extern SvNewZone* NEW_ZONE_UI;
extern SvZonesList* ZONELIST_UI;
extern SvEmployee* EMPLOYEE_UI;
extern SvEmployeesList* EMPLOYEESLIST_UI;

SvSCUD::SvSCUD(QWidget *parent,
               int showMode,
               int id) :
  QDialog(parent),
  ui(new Ui::SvSCUD)
{
  ui->setupUi(this);
  
  this->showMode = showMode;
  
  if(showMode == smEdit)
  {
    QSqlQuery* q = new QSqlQuery(PGDB->db);
    QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_SCUDS_WHERE).arg("scuds.id").arg(id), q);
    
    if(err.type() != QSqlError::NoError) return;
    
    if(q->size() == 0) return;
    q->first();
    t_id = q->value("id").toInt();
    t_key = q->value("key_value").toInt();
    t_employee_id = q->value("employee_id").toInt();
    t_employee_name = q->value("employee_name").toString();
    t_employee_patronymic = q->value("employee_patronymic").toString();
    t_employee_surename = q->value("employee_surename").toString();
    t_employee_position = q->value("employee_position").toString();
    t_device_name = q->value("device_name").toString();
    t_zone_name = q->value("zone_name").toString();
  }
    
  ui->editID->setText(showMode == smNew ? "<Новый>" : QString("%1").arg(t_id));
  ui->editKey->setText(QString("%1").arg(t_key));
  ui->editDevice->setText(t_device_name);
  
  ui->editEmployee->setText(showMode == smNew ? "" : QString("%1 %2 %3 %4")
                                                              .arg(t_employee_surename)
                                                              .arg(t_employee_name == "" ? '\0' : t_employee_name.at(0))
                                                              .arg(t_employee_patronymic == "" ? '\0' : t_employee_patronymic.at(0))
                                                              .arg(t_employee_position == "" ? "" : "(" + t_employee_position + ")"));
  ui->editZoneName->setText(t_zone_name);
  
  ui->editKey->setReadOnly(showMode != smNew);
  
  connect(ui->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(ui->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  connect(ui->bnGetKey, SIGNAL(pressed()), this, SLOT(slotGetKey()));
  connect(ui->bnSelectEmployee, SIGNAL(pressed()), this, SLOT(on_bnSelectEmployee_clicked()));
  connect(ui->bnNewEmployee, SIGNAL(pressed()), this, SLOT(on_bnNewEmployee_clicked())); 
  connect(ui->bnSelectDevice, SIGNAL(pressed()), this, SLOT(slotSelectDevice()));
  
  this->setModal(true);
  this->setResult(-1);
  this->show();
  
}

SvSCUD::~SvSCUD()
{
  delete ui;
}

void SvSCUD::accept()
{
  QSqlError err;
  QSqlQuery* q;
  
  if(ui->editKey->text() == "")
  {
    QMessageBox::critical(0, "Ошибка", "Необходимо указать ключ", QMessageBox::Ok);
    ui->editKey->setFocus();
    return;
  }
  
  if(this->showMode  == smNew)
  {
    q = new QSqlQuery(PGDB->db);
    err = PGDB->execSQL(QString(D_SELECT_FROM_SCUDS_WHERE).arg("scuds.key_value").arg(ui->editKey->text()), q);
    
    if(err.type() != QSqlError::NoError) return;
    
    if(q->size())
    {
      QMessageBox::critical(0, "Ошибка", "Такой ключ уже есть в системе", QMessageBox::Ok);
      ui->editKey->setFocus();
      return;
    }
    q->finish();
    free(q);
  }

  t_key = ui->editKey->text().toInt();
//  t_employee_name = ui->editEmployer->text();
  t_device_name = ui->editDevice->text();
  t_zone_name = ui->editZoneName->text();
  
  QString s;
  switch(this->showMode)
  {
    case smNew:
    {
      s = QString(D_INSERT_INTO_SCUDS).arg(t_key)
                                      .arg(t_employee_id)
                                      .arg(t_device_name)
                                      .arg(t_zone_name);

      break;
    }

    case smEdit:
    {
      s = QString(D_UPDATE_SCUDS).arg(t_key)
                                 .arg(t_employee_id)
                                 .arg(t_device_name)
                                 .arg(t_zone_name)
                                 .arg(t_key);

      break;
    }
  }  

  err = PGDB->execSQL(s);
  if(err.type() != QSqlError::NoError) QDialog::reject();  
  else  QDialog::accept();
  
}

void SvSCUD::slotGetKey()
{
  awaitingKey = new AwaitingKey(this);
  connect(awaitingKey, SIGNAL(accepted()), this, SLOT(on_AWAITING_closed()));
  connect(awaitingKey, SIGNAL(rejected()), this, SLOT(on_AWAITING_closed()));
}

void SvSCUD::on_bnSelectEmployee_clicked()
{
  EMPLOYEESLIST_UI = new SvEmployeesList(this);
  connect(EMPLOYEESLIST_UI, SIGNAL(accepted()), this, SLOT(on_EMPLOYEESLIST_UI_closed()));
  connect(EMPLOYEESLIST_UI, SIGNAL(rejected()), this, SLOT(on_EMPLOYEESLIST_UI_closed()));
}

void SvSCUD::on_EMPLOYEESLIST_UI_closed()
{
  if(EMPLOYEESLIST_UI->result() == QDialog::Accepted)
  {
    this->t_employee_id = EMPLOYEESLIST_UI->t_id;
    ui->editEmployee->setText(QString("%1 %2. %3. (%4)")
                              .arg(EMPLOYEESLIST_UI->t_employee_surename)
                              .arg(EMPLOYEESLIST_UI->t_employee_name.at(0))
                              .arg(EMPLOYEESLIST_UI->t_employee_patronymic.at(0))
                              .arg(EMPLOYEESLIST_UI->t_employee_position));
  }
     
  EMPLOYEESLIST_UI->~SvEmployeesList();
}

void SvSCUD::on_bnNewEmployee_clicked()
{
  EMPLOYEE_UI = new SvEmployee(this);
  connect(EMPLOYEE_UI, SIGNAL(accepted()), this, SLOT(on_EMPLOYEE_UI_closed()));
  connect(EMPLOYEE_UI, SIGNAL(rejected()), this, SLOT(on_EMPLOYEE_UI_closed()));
}

void SvSCUD::on_EMPLOYEE_UI_closed()
{
  if(EMPLOYEE_UI->result() == QDialog::Accepted)
  {
    
  }
  EMPLOYEE_UI->~SvEmployee();
}

void SvSCUD::slotSelectDevice()
{
  DEVICELIST_UI = new SvDevicesList(this);
  connect(DEVICELIST_UI, SIGNAL(accepted()), this, SLOT(on_DEVICELIST_UI_closed()));
  connect(DEVICELIST_UI, SIGNAL(rejected()), this, SLOT(on_DEVICELIST_UI_closed()));
}

void SvSCUD::on_DEVICELIST_UI_closed()
{
  if(DEVICELIST_UI->result() == QDialog::Accepted)
  {
    ui->editDevice->setText(DEVICELIST_UI->t_deviceName);
  }
  DEVICELIST_UI->~SvDevicesList();
}

void SvSCUD::on_AWAITING_closed()
{
  if(awaitingKey->result() == QDialog::Accepted)
  {
    ui->editKey->setText(QString("%1").arg(awaitingKey->t_key));
    log_ns::log(m_Attention, awaitingKey->t_date_time.toString("dd.MM.yy hh:mm:ss"));
  }
  awaitingKey->~AwaitingKey();
}

void SvSCUD::on_bnSelectZone_clicked()
{
  ZONELIST_UI = new SvZonesList(this, false, false);
  connect(ZONELIST_UI, SIGNAL(accepted()), this, SLOT(on_ZONELIST_UI_closed()));
  connect(ZONELIST_UI, SIGNAL(rejected()), this, SLOT(on_ZONELIST_UI_closed()));
}

void SvSCUD::on_ZONELIST_UI_closed()
{
  if(ZONELIST_UI->result() == QDialog::Accepted)
  {
    ui->editZoneName->setText(ZONELIST_UI->t_zoneName);
//    on_bnSelectPosition_clicked();
  }
  ZONELIST_UI->~SvZonesList();
}

void SvSCUD::on_bnNewZone_clicked()
{
  NEW_ZONE_UI = new SvNewZone(this);
  connect(NEW_ZONE_UI, SIGNAL(accepted()), this, SLOT(on_NEW_ZONE_UI_closed()));
  connect(NEW_ZONE_UI, SIGNAL(rejected()), this, SLOT(on_NEW_ZONE_UI_closed()));
}

void SvSCUD::on_NEW_ZONE_UI_closed()
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

/** ********* AwaitingKey ************** **/
AwaitingKey::AwaitingKey(QWidget *parent, QString ip) :
  QDialog(parent)
{
  if (this->objectName().isEmpty())
      this->setObjectName(QStringLiteral("AwaitingKeyDialog"));
  this->setWindowModality(Qt::WindowModal);
  this->resize(330, 65);
  QVBoxLayout* verticalLayout = new QVBoxLayout(this);
  verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
  QGroupBox* groupBox = new QGroupBox(this);
  groupBox->setObjectName(QStringLiteral("groupBox"));
  QVBoxLayout* verticalLayout_2 = new QVBoxLayout(groupBox);
  verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
  QHBoxLayout* horizontalLayout = new QHBoxLayout();
  horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
  QLabel* label = new QLabel(groupBox);
  label->setObjectName(QStringLiteral("label"));
  label->setText(ip == "" ? QStringLiteral("Ожидание ключа") : QStringLiteral("Ожидание ключа от ") + ip);

  horizontalLayout->addWidget(label);

  QPushButton* bnCancel = new QPushButton(groupBox);
  bnCancel->setObjectName(QStringLiteral("bnCancel"));
  bnCancel->setText(QStringLiteral("Отмена"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(bnCancel->sizePolicy().hasHeightForWidth());
  bnCancel->setSizePolicy(sizePolicy);

  horizontalLayout->addWidget(bnCancel);

  verticalLayout_2->addLayout(horizontalLayout);

  verticalLayout->addWidget(groupBox);
  
  connect(bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  tcp_server = new SvTcpServer(35580, true, this);
  connect(tcp_server, SIGNAL(sigGotMessage()), this, SLOT(accept()));
  
  this->setResult(-1);
  this->show();
  
}

AwaitingKey::~AwaitingKey()
{
  this->close();
  this->deleteLater();
}

void AwaitingKey::accept()
{
  GotKeyStruct* gotKey = reinterpret_cast<GotKeyStruct*>(malloc(sizeof(GotKeyStruct)));
  memset(gotKey, char(0), sizeof(GotKeyStruct));
  memcpy(gotKey, tcp_server->last_message, sizeof(GotKeyStruct));
  
  /* номер считывателя */
  t_scud_number = int(gotKey->scud_number);
  
  /* сам ключ */
  t_key = 0;
  memcpy(&t_key, &gotKey->key_byte1, 3);
//  t_key = QString("%1").arg(k);
  
  /* дата и время */
  QDate d = QDate((gotKey->year  >> 4) * 10 + (gotKey->year  & 0x0F),
                  (gotKey->month >> 4) * 10 + (gotKey->month & 0x0F),
                  (gotKey->day   >> 4) * 10 + (gotKey->day   & 0x0F));
  
  QTime t = QTime((gotKey->hour >> 4) * 10 + (gotKey->hour & 0x0F),
                  (gotKey->min  >> 4) * 10 + (gotKey->min  & 0x0F),
                  (gotKey->sec  >> 4) * 10 + (gotKey->sec  & 0x0F));

  t_date_time.setDate(d);
  t_date_time.setTime(t);
  
  /* день недели */
  t_weekday = gotKey->weekday;
  
  tcp_server->stopServer();
  tcp_server->deleteLater();
  
  QDialog::accept();
  
}

void AwaitingKey::reject()
{
  tcp_server->stopServer();
  tcp_server->deleteLater();
  
  QDialog::reject();
}

