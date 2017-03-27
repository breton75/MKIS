#include "sv_dev_brands_list.h"
#include "sv_dev_brand.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "./COMMON/sv_settings.h"

#include <QMessageBox>

using namespace sql_insert_defs;
using namespace sql_select_defs;

SvDevBrandsListDialog *DEVBRANDSLIST_UI;

extern SvBrand *DEVBRAND_UI;

SvDevBrandsListDialog::SvDevBrandsListDialog(QWidget *parent,
                                             bool showEditDelete,
                                             bool showSelect) :
  QDialog(parent),
  Dialog(new Ui::SvDevBrandsListDialog)
{
  
  Dialog->setupUi(this);
  
  setBrandListTable();
    
  Dialog->bnEditBrand->setVisible(showEditDelete);
  Dialog->bnDeleteBrand->setVisible(showEditDelete);
  Dialog->bnSelect->setVisible(showSelect);
  
  connect(Dialog->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(Dialog->bnNewBrand, SIGNAL(pressed()), this, SLOT(slotNewBrand()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(slotEditBrand()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(slotDeleteBrand()));  
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  

}

SvDevBrandsListDialog::~SvDevBrandsListDialog()
{
  this->close();
  delete Dialog;
}

void SvDevBrandsListDialog::accept()
{
//  t_brandName = model->data(model->index(Dialog->tblBrandsList->selectionModel()->currentIndex().row(), 0)).toString();
//  QDialog::accept();
  
  QSqlRecord r = m_dev_brands_list->record(Dialog->tblBrandsList->currentIndex().row());
  
  t_id = r.value("id").toInt();
  t_brandName = r.value("brand_name").toString();
  t_description = r.value("description").toString();
  
  QDialog::accept();
}

void SvDevBrandsListDialog::slotNewBrand()
{
  DEVBRAND_UI = new SvBrand(this);
  connect(DEVBRAND_UI, SIGNAL(accepted()), this, SLOT(on_DEVBRAND_UI_closed()));
  connect(DEVBRAND_UI, SIGNAL(rejected()), this, SLOT(on_DEVBRAND_UI_closed()));
}

void SvDevBrandsListDialog::on_DEVBRAND_UI_closed()
{
  if(DEVBRAND_UI->result() == QDialog::Accepted)
  {
    setBrandListTable();

  }
  DEVBRAND_UI->~SvBrand();

}

void SvDevBrandsListDialog::slotEditBrand()
{
  
}

void SvDevBrandsListDialog::slotDeleteBrand()
{
  
}

int SvDevBrandsListDialog::setBrandListTable()
{
  /* ----------- brand_list -------------*/
//  model->clear();
  
//  model->setColumnCount(1);
  
//  model->setHeaderData(0, Qt::Horizontal, QString("Производитель"));
//  model->setHeaderData(1, Qt::Horizontal, QString("Входит в зону"));
//  model->setHeaderData(2, Qt::Horizontal, QString("Описание"));


//  Dialog->tblBrandsList->setModel(model);
//  Dialog->tblBrandsList->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
//  QString s = QApplication::applicationDirPath() + "/ini/brands.ini";
//  SvSettings* bl_sett = new SvSettings(s);

//  QStringList lst = bl_sett->appSettings->childGroups();
//  QList<QStandardItem *> rowItems;
//  for(int i = 0; i < lst.count(); i++)
//  {
//    rowItems.clear();
//    s = bl_sett->readValue(lst.at(i), "brand", "").toString();
//    for(int j = 1; j < 2; j++)
//      rowItems << new QStandardItem(s.section('%', j, j));

//    model->appendRow(rowItems);
//    Dialog->tblBrandsList->setRowHeight(i, 22);
//  }
  
//  for(int i = 0; i < 1; i++)
//    Dialog->tblBrandsList->setColumnWidth(i, 250);
  
//  return 0;
  
  QSqlError err = PGDB->execSQL(SELECT_DEV_BRANDS_LIST, m_dev_brands_list);
  if(err.type() != QSqlError::NoError) return -1;
  
  Dialog->tblBrandsList->setModel(m_dev_brands_list);
  
  QStringList headers = QString(DEV_BRANDS_COLUMN_LIST).split(';');
  
  for(int i = 0; i < headers.count(); i++)
    m_dev_brands_list->setHeaderData(i,  Qt::Horizontal, headers.at(i));

  return 0;
  
}
