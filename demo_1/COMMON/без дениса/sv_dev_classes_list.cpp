#include "sv_dev_classes_list.h"

#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_dev_class.h"
#include "./COMMON/sv_settings.h"

#include <QMessageBox>

using namespace sql_select_defs;
using namespace sql_insert_defs;

SvDevClassesListDialog *DEVCLASSESLIST_UI;
extern SvDeviceClass *DEVCLASS_UI;

SvDevClassesListDialog::SvDevClassesListDialog(QWidget *parent, bool showEditDelete, bool showSelect) :
  QDialog(parent),
  Dialog(new Ui::SvDevClassesListDialog)
{
  
  Dialog->setupUi(this);
  
  setClassListTable();
    
  Dialog->bnEditClass->setVisible(showEditDelete);
  Dialog->bnDeleteClass->setVisible(showEditDelete);
  Dialog->bnSelect->setVisible(showSelect);
  
  connect(Dialog->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(Dialog->bnNewClass, SIGNAL(pressed()), this, SLOT(slotNewClass()));
  connect(Dialog->bnEditClass, SIGNAL(pressed()), this, SLOT(slotEditClass()));
  connect(Dialog->bnDeleteClass, SIGNAL(pressed()), this, SLOT(slotDeleteClass()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  
}

SvDevClassesListDialog::~SvDevClassesListDialog()
{
  this->close();
  delete Dialog;
}

void SvDevClassesListDialog::accept()
{
  t_className = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 0)).toString();
  t_libPath = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 1)).toString();
  
  QDialog::accept();
  
}

void SvDevClassesListDialog::slotNewClass()
{
  DEVCLASS_UI = new SvDeviceClass(this);
  connect(DEVCLASS_UI, SIGNAL(accepted()), this, SLOT(on_DEVCLASS_UI_closed()));
  connect(DEVCLASS_UI, SIGNAL(rejected()), this, SLOT(on_DEVCLASS_UI_closed()));
}

void SvDevClassesListDialog::on_DEVCLASS_UI_closed()
{
  if(DEVCLASS_UI->result() == QDialog::Accepted)
  {
    setClassListTable();
  }
  
  DEVCLASS_UI->~SvDeviceClass();
  
}

void SvDevClassesListDialog::slotEditClass()
{
  t_className = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 0)).toString();
  t_libPath = model->data(model->index(Dialog->tblClassesList->selectionModel()->currentIndex().row(), 1)).toString();
  
  DEVCLASS_UI = new SvDeviceClass(this, t_className, t_libPath, "", 0, SvDeviceClass::smEdit);
  connect(DEVCLASS_UI, SIGNAL(accepted()), this, SLOT(on_DEVCLASS_UI_closed()));
  connect(DEVCLASS_UI, SIGNAL(rejected()), this, SLOT(on_DEVCLASS_UI_closed()));
}

void SvDevClassesListDialog::slotDeleteClass()
{

}

int SvDevClassesListDialog::setClassListTable()
{
  /* ----------- classes_list -------------*/
  model->clear();
  
  model->setColumnCount(2);
  
  model->setHeaderData(0, Qt::Horizontal, QString("Класс"));
  model->setHeaderData(1, Qt::Horizontal, QString("Библиотека"));
//  model->setHeaderData(2, Qt::Horizontal, QString("Описание"));


  Dialog->tblClassesList->setModel(model);
  Dialog->tblClassesList->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  QString s = QApplication::applicationDirPath() + "/ini/classes.ini";
  SvSettings* bl_sett = new SvSettings(s);

  QStringList lst = bl_sett->appSettings->childGroups();
  QList<QStandardItem *> rowItems;
  for(int i = 0; i < lst.count(); i++)
  {
    rowItems.clear();
    s = bl_sett->readValue(lst.at(i), "class", "").toString();
    for(int j = 1; j < 3; j++)
      rowItems << new QStandardItem(s.section('%', j, j));

    model->appendRow(rowItems);
    Dialog->tblClassesList->setRowHeight(i, 22);
  }
  
  for(int i = 0; i < 2; i++)
    Dialog->tblClassesList->setColumnWidth(i, 250);
  
  return 0;
}
