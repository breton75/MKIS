#include "sv_employees_list.h"

#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_employee.h"
#include "./COMMON/sv_settings.h"
#include "sv_pgdb.h"
#include <QMessageBox>

using namespace sql_select_defs;
using namespace sql_insert_defs;

SvEmployeesList *EMPLOYEESLIST_UI;
extern SvEmployee *EMPLOYEE_UI;

extern SvPGDB *PGDB;

SvEmployeesList::SvEmployeesList(QWidget *parent, bool showEditDelete, bool showSelect) :
  QDialog(parent),
  ui(new Ui::SvEmployeesListDialog),
  p_employees_model(new QSqlQueryModel(this))
{
  
  ui->setupUi(this);
  
  setEmployeesListTable();
    
  ui->bnEditEmployee->setVisible(showEditDelete);
  ui->bnDeleteEmployee->setVisible(showEditDelete);
  ui->bnSelect->setVisible(showSelect);
  
  connect(ui->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(ui->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(ui->bnNewEmployee, SIGNAL(pressed()), this, SLOT(on_bnNewEmployee_clicked()));
  connect(ui->bnEditEmployee, SIGNAL(pressed()), this, SLOT(on_bnEditEmployee_clicked()));
  connect(ui->bnDeleteEmployee, SIGNAL(pressed()), this, SLOT(on_bnDeleteEmployee_clicked()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  
}

SvEmployeesList::~SvEmployeesList()
{
  this->close();
  delete ui;
}

void SvEmployeesList::accept()
{
//  t_className = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 0)).toString();
//  t_libPath = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 1)).toString();
    QSqlRecord r = p_employees_model->record(ui->tblEmployeesList->currentIndex().row());
    t_id= r.value("id").toInt();
    t_employee_name = r.value("employee_name").toString();
    t_employee_patronymic = r.value("employee_patronymic").toString();
    t_employee_surename = r.value("employee_surename").toString();
    t_employee_position = r.value("employee_position").toString();
    t_birth_date = r.value("birth_date").toDate();
    t_key_value = r.value("key_value").toInt();
    t_key_id = r.value("key_id").toInt();
    t_description = r.value("description").toString();
  QDialog::accept();
  
}

void SvEmployeesList::on_bnNewEmployee_clicked()
{
  EMPLOYEE_UI = new SvEmployee(this);
  connect(EMPLOYEE_UI, SIGNAL(accepted()), this, SLOT(on_EMPLOYEE_UI_closed()));
  connect(EMPLOYEE_UI, SIGNAL(rejected()), this, SLOT(on_EMPLOYEE_UI_closed()));
}

void SvEmployeesList::on_EMPLOYEE_UI_closed()
{
  if(EMPLOYEE_UI->result() == QDialog::Accepted)
  {
    setEmployeesListTable();
  }
  
  EMPLOYEE_UI->~SvEmployee();
  
}

void SvEmployeesList::on_bnEditEmployee_clicked()
{
//  t_className = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 0)).toString();
//  t_libPath = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 1)).toString();
  
//  DEVCLASS_UI = new SvDeviceClass(this, t_className, t_libPath, "", 0, SvDeviceClass::smEdit);
//  connect(DEVCLASS_UI, SIGNAL(accepted()), this, SLOT(on_DEVCLASS_UI_closed()));
//  connect(DEVCLASS_UI, SIGNAL(rejected()), this, SLOT(on_DEVCLASS_UI_closed()));
}

void SvEmployeesList::on_bnDeleteEmployee_clicked()
{

}

int SvEmployeesList::setEmployeesListTable()
{
  /* ----------- classes_list -------------*/
//  model->clear();
  
//  model->setColumnCount(2);
  
//  model->setHeaderData(0, Qt::Horizontal, QString("Класс"));
//  model->setHeaderData(1, Qt::Horizontal, QString("Библиотека"));
//  model->setHeaderData(2, Qt::Horizontal, QString("Описание"));


//  Dialog->tblClassesList->setModel(model);
//  Dialog->tblClassesList->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
//  QString s = QApplication::applicationDirPath() + "/ini/classes.ini";
//  SvSettings* bl_sett = new SvSettings(s);

//  QStringList lst = bl_sett->appSettings->childGroups();
//  QList<QStandardItem *> rowItems;
//  for(int i = 0; i < lst.count(); i++)
//  {
//    rowItems.clear();
//    s = bl_sett->readValue(lst.at(i), "class", "").toString();
//    for(int j = 1; j < 3; j++)
//      rowItems << new QStandardItem(s.section('%', j, j));

//    model->appendRow(rowItems);
//    Dialog->tblClassesList->setRowHeight(i, 22);
//  }
  
//  for(int i = 0; i < 2; i++)
//    Dialog->tblClassesList->setColumnWidth(i, 250);
  
    QSqlError err = PGDB->execSQL(D_SELECT_EMPLOYEES_LIST, p_employees_model);
    if(err.type() != QSqlError::NoError) return -1;

    ui->tblEmployeesList->setModel(p_employees_model);

    QStringList headers = QString(D_EMPLOYEES_COLUMN_LIST).split(';');

    for(int i = 0; i < headers.count(); i++)
    {
      p_employees_model->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
      ui->tblEmployeesList->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
      ui->tblEmployeesList->setColumnWidth(i, 150);
    }
    
  return 0;
}
