#include "sv_dev_class.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "./COMMON/sv_settings.h"

#include <QMessageBox>

using namespace sql_insert_defs;

SvDeviceClass *DEVCLASS_UI;


SvDeviceClass::SvDeviceClass(QWidget *parent,
                             QString className,
                             QString classLibPath,
                             QString description,
                             int id,
                             int showMode) :
  
  QDialog(parent),
  Dialog(new Ui::SvClassDialog)
{
  
  this->show_mode = showMode;
  
  Dialog->setupUi(this,
                  className,
                  classLibPath,
                  description,
                  id,
                  this->show_mode);  
  
  Dialog->editClassName->setReadOnly(showMode != smNew);
  
  connect(Dialog->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();

}

SvDeviceClass::~SvDeviceClass()
{
  this->close();
  delete Dialog;
}

void SvDeviceClass::accept()
{
  
  if(Dialog->editClassName->text() == "")
  {
    Dialog->editClassName->setFocus();
    return;
  }
  
  t_id =  Dialog->editID->text().toInt();
  t_className  = Dialog->editClassName->text();
  t_libPath = Dialog->editLibPath->text();
  t_description = Dialog->textDescription->toPlainText();
  
  char groupName;
  QString s = qApp->applicationDirPath() + "/ini/classes.ini";
  SvSettings* sett = new SvSettings(s);
  QStringList lst = sett->appSettings->childGroups();
  
  switch(this->show_mode)
  {
    case smNew:
      if(lst.count())
      {
        groupName = lst.last().at(0).toLatin1();
        if(groupName == 'z') return;
        groupName = groupName + 1;
      }
      else groupName = 'a';
      break;

    case smEdit:
      for(int i = 0; i < lst.count(); i++)
      {
        s = sett->readValue(lst.at(i), "class", "").toString();
        if(s.section('%', 1, 1) == t_className)
        {
          groupName = lst.at(i).at(0).toLatin1();
          break;
        }
      }
      break;
  }
  
  sett->writeValue(QString("%1").arg(groupName), "class", QString("\%%1\%%2\%")
                                                      .arg(t_className)
                                                      .arg(t_libPath));
  QDialog::accept();
  
}

