#include "sv_employee.h"
#include "./COMMON/sv_pgdb.h"
#include "sv_scud.h"

SvEmployee* EMPLOYEE_UI;
extern SvPGDB* PGDB;
extern SvSCUD* SCUD_UI;

SvEmployee::SvEmployee(QWidget *parent, int showMode, int emploeeID) :
  QDialog(parent),
  ui(new Ui::SvEmploeeDialog)
{
  this->showMode = showMode;
  
  if(showMode == smEdit)
  {
    QSqlQuery* q = new QSqlQuery(PGDB->db); 
    QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_EMPLOYEES_WHERE).arg(emploeeID), q);
    if(err.type() != QSqlError::NoError) return;
    
    if(q->size())
    {
      q->first();
      t_id = q->value("id").toInt();
      t_employee_name = q->value("employee_name").toString();
      t_employee_patronymic = q->value("employee_patronymic").toString();
      t_employee_surename = q->value("employee_surename").toString();
      t_employee_position = q->value("employee_position").toString();
      t_birth_date = q->value("birth_date").toDate();
      t_key_value = q->value("key_value").toInt();
      t_key_id = q->value("key_id").toInt();
      t_description = q->value("description").toString();
    }
  }

  ui->setupUi(this);
  
  ui->editID->setText(showMode == smNew ? "<Новый>" : QString("%1").arg(t_id));
  ui->editName->setText(t_employee_name);
  ui->editPatronymic->setText(t_employee_patronymic);
  ui->editSurename->setText(t_employee_surename);
  ui->dateBirthDate->setDate(t_birth_date);
  ui->editPosition->setText(t_employee_position);
  ui->editScud->setText(QString("%1").arg(t_key_value));
  
  connect(ui->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(ui->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  connect(ui->bnNewScud, SIGNAL(pressed()), this, SLOT(on_bnNewScud_clicked()));
  connect(ui->bnSelectScud, SIGNAL(pressed()), this, SLOT(on_bnSelectScud_clicked()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();  
}

SvEmployee::~SvEmployee()
{
  this->close();
  delete ui;
}

void SvEmployee::on_bnNewScud_clicked()
{
  SCUD_UI = new SvSCUD(this);
  connect(SCUD_UI, SIGNAL(accepted()), this, SLOT(on_SCUD_UI_closed()));
  connect(SCUD_UI, SIGNAL(rejected()), this, SLOT(on_SCUD_UI_closed()));
}

void SvEmployee::on_SCUD_UI_closed()
{
  if(SCUD_UI->result() == QDialog::Accepted)
  {
    t_key_id = SCUD_UI->t_id;
    t_key_value = SCUD_UI->t_key;
  }
  SCUD_UI->~SvSCUD();
}

void SvEmployee::on_bnSelectScud_clicked()
{
  
}

void SvEmployee::on_SCUDSLIST_UI_closed()
{
  
}

void SvEmployee::accept()
{
  QSqlError err;
  QSqlQuery* q;
 
  if(ui->editSurename->text() == "")
  {
    QMessageBox::critical(0, "Ошибка", "Необходимо указать фамилию", QMessageBox::Ok);
    ui->editSurename->setFocus();
    return;
  }  
  
  t_employee_name = ui->editName->text();
  t_employee_patronymic = ui->editPatronymic->text();
  t_employee_surename = ui->editSurename->text();
  t_employee_position = ui->editPosition->text();
  t_birth_date = ui->dateBirthDate->date();
    
  QString s;
  switch(this->showMode)
  {
    case smNew:
    {
      s = QString(D_INSERT_INTO_EMPLOYEES).arg(t_employee_name)
                                          .arg(t_employee_patronymic)
                                          .arg(t_employee_surename)
                                          .arg(t_employee_position)
                                          .arg(t_birth_date.toString("dd/MM/yy"))
                                          .arg(t_key_id)
                                          .arg(t_description);

      break;
    }

    case smEdit:
    {
      s = QString(D_UPDATE_EMPLOYEES).arg(t_employee_name)
                                     .arg(t_employee_patronymic)
                                     .arg(t_employee_surename)
                                     .arg(t_employee_position)
                                     .arg(t_birth_date.toString("dd/MM/yy"))
                                     .arg(t_key_id)
                                     .arg(t_description);

      break;
    }
  }  

  err = PGDB->execSQL(s);
  if(err.type() != QSqlError::NoError) QDialog::reject();  
  else  QDialog::accept();
}

