#include "sv_plan.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"

#include <QMessageBox>

using namespace sql_insert_defs;

SvPlan *PLAN_UI;


SvPlan::SvPlan(QWidget *parent,
                             QString planName,
                             QString planImgPath,
                             QString description,
                             int id,
                             int showMode) :
  
  QDialog(parent),
  Dialog(new Ui::SvPlanDialog)
{
  
  this->show_mode = showMode;
  
  Dialog->setupUi(this,
                  planName,
                  planImgPath,
                  description,
                  id,
                  this->show_mode);  
  
  connect(Dialog->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();

}

SvPlan::~SvPlan()
{
  this->close();
  delete Dialog;
}

void SvPlan::accept()
{
  
  if(Dialog->editPlanName->text() == "")
  {
    Dialog->editPlanName->setFocus();
    return;
  }
  
  t_id =  Dialog->editID->text().toInt();
  t_planName  = Dialog->editPlanName->text();
  t_imgPath = Dialog->editImgPath->text();
  t_description = Dialog->textDescription->toPlainText();
  
  QString s;
  switch(this->show_mode)
  {
    case smNew:


      break;

    case smEdit:
      
      break;
  }
  
  QDialog::accept(); //this->setResult(QDialog::Accepted);
  
}

