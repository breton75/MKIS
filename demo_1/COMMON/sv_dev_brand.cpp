#include "sv_dev_brand.h"
#include "ui_device.h"
#include "sql_select_defs.h"
#include "sv_dev_models_list.h"
#include "./COMMON/sv_settings.h"
#include "sv_pgdb.h"
#include <QMessageBox>

using namespace sql_insert_defs;

SvBrand *DEVBRAND_UI;
extern SvPGDB *PGDB;
SvBrand::SvBrand(QWidget *parent,
                 QString brandName,
                 QString description,
                 int id,
                 int showMode) :
  
  QDialog(parent),
  Dialog(new Ui::SvBrandDialog)
{
  
  Dialog->setupUi(this,
                  brandName,
                  description,
                  id,
                  showMode);  
  
  this->showMode = showMode;
  
  Dialog->editBrandName->setReadOnly(showMode != smNew);
  
  connect(Dialog->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();

}

SvBrand::~SvBrand()
{
  this->close();
  delete Dialog;
}

void SvBrand::accept()
{
  t_id = Dialog->editID->text().toInt();
  t_brandName  = Dialog->editBrandName->text();
  t_description = Dialog->textDescription->toPlainText();
  
//  char groupName;
//  QString s = qApp->applicationDirPath() + "/ini/brands.ini";
//  SvSettings* sett = new SvSettings(s);
//  QStringList lst = sett->appSettings->childGroups();
  
  QString s;
  switch(this->showMode)
  {
    case smNew:
    {
      s = QString(D_INSERT_INTO_DEV_BRANDS)
          .arg(t_brandName)
          .arg(t_description);
      
//      if(lst.count())
//      {
//        groupName = lst.last().at(0).toLatin1();
//        if(groupName == 'z') return;
//        groupName = groupName + 1;
//      }
//      else groupName = 'a';
      break;
    }
      
    case smEdit:
    {
      s = QString(D_UPDATE_DEV_BRANDS)
          .arg(t_brandName)
          .arg(t_description)
              .arg(t_id);
      
//      for(int i = 0; i < lst.count(); i++)
//      {
//        s = sett->readValue(lst.at(i), "brand", "").toString();
//        if(s.section('%', 1, 1) == t_brandName)
//        {
//          groupName = lst.at(i).at(0).toLatin1();
//          break;
//        }
//      }
      break;
    }
  }
  
  QSqlError err = PGDB->execSQL(s);
  
  if (err.type() != QSqlError::NoError) QDialog::reject(); // this->setResult(QDialog::Rejected);
  else QDialog::accept();
  
//  sett->writeValue(QString("%1").arg(groupName), "brand", QString("\%%1\%")
//                                                      .arg(t_brandName));
  
//  QDialog::accept();
}

