#include "sv_dev_models_list.h"

#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_dev_model.h"
#include "./COMMON/sv_settings.h"

#include <QMessageBox>

using namespace sql_select_defs;
using namespace sql_insert_defs;

SvDevModelsList *DEVMODELSLIST_UI;
extern SvDevModel *DEVMODEL_UI;

SvDevModelsList::SvDevModelsList(QWidget *parent, bool showEditDelete, bool showSelect) :
  QDialog(parent),
  Dialog(new Ui::SvDevModelsListDialog)
{
  
  Dialog->setupUi(this);
    
  Dialog->bnEditModel->setVisible(showEditDelete);
  Dialog->bnDeleteModel->setVisible(showEditDelete);
  Dialog->bnSelect->setVisible(showSelect);
  
  connect(Dialog->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(Dialog->bnNewModel, SIGNAL(pressed()), this, SLOT(slotNewModel()));
  connect(Dialog->bnEditModel, SIGNAL(pressed()), this, SLOT(slotEditModel()));
  connect(Dialog->bnDeleteModel, SIGNAL(pressed()), this, SLOT(slotDeleteModel()));
  
  setModelListTable();
  
  this->setResult(-1);
  this->setModal(true);
  this->show();

}

SvDevModelsList::~SvDevModelsList()
{
  this->close();
  delete Dialog;
}

void SvDevModelsList::accept()
{
  t_modelName = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 0)).toString();
  t_className = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 1)).toString();
  t_brandName = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 2)).toString();
  t_libPath = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 3)).toString();

  QDialog::accept();
  
}

void SvDevModelsList::slotNewModel()
{
  DEVMODEL_UI = new SvDevModel(this);
  connect(DEVMODEL_UI, SIGNAL(accepted()), this, SLOT(on_DEVMODEL_UI_closed()));
  connect(DEVMODEL_UI, SIGNAL(rejected()), this, SLOT(on_DEVMODEL_UI_closed()));
}
  
void SvDevModelsList::on_DEVMODEL_UI_closed()
{
  if(DEVMODEL_UI->result() == QDialog::Accepted)
  {
    setModelListTable();
  }
  
  DEVMODEL_UI->~SvDevModel();
  
}

void SvDevModelsList::slotEditModel()
{
  t_modelName = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 0)).toString();
  t_className = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 1)).toString();
  t_brandName = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 2)).toString();
  t_libPath = model->data(model->index(Dialog->tblModelsList->selectionModel()->currentIndex().row(), 3)).toString();
  
  DEVMODEL_UI = new SvDevModel(this, t_modelName, t_brandName, t_className, t_libPath, "", 0, SvDevModel::smEdit);
  connect(DEVMODEL_UI, SIGNAL(accepted()), this, SLOT(on_DEVMODEL_UI_closed()));
  connect(DEVMODEL_UI, SIGNAL(rejected()), this, SLOT(on_DEVMODEL_UI_closed()));
}

void SvDevModelsList::slotDeleteModel()
{

}

int SvDevModelsList::setModelListTable()
{
  /* ----------- model_list -------------*/
  model->clear();
  
  model->setColumnCount(4);
  
  model->setHeaderData(0, Qt::Horizontal, QString("Модель"));
  model->setHeaderData(1, Qt::Horizontal, QString("Класс устройства"));
  model->setHeaderData(2, Qt::Horizontal, QString("Производитель"));  
  model->setHeaderData(3, Qt::Horizontal, QString("Драйвер"));


  Dialog->tblModelsList->setModel(model);
  Dialog->tblModelsList->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  QString s = QApplication::applicationDirPath() + "/ini/models.ini";
  SvSettings* bl_sett = new SvSettings(s);

  QStringList lst = bl_sett->appSettings->childGroups();
  QList<QStandardItem *> rowItems;
  for(int i = 0; i < lst.count(); i++)
  {
    rowItems.clear();
    s = bl_sett->readValue(lst.at(i), "model", "").toString();
    for(int j = 1; j < 5; j++)
      rowItems << new QStandardItem(s.section('%', j, j));

    model->appendRow(rowItems);
    Dialog->tblModelsList->setRowHeight(i, 22);
  }
  
  for(int i = 0; i < 4; i++)
    Dialog->tblModelsList->setColumnWidth(i, 250);
  
  return 0;
}
