#ifndef SV_PLAN_H
#define SV_PLAN_H

#include <QDialog>
#include <QString>
#include "ui_plan.h"

namespace Ui {
  class SvPlanDialog;
}

class SvPlan : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvPlan(QWidget *parent,
                           QString planName = "",
                           QString planImgPath = "",
                           QString description = "",
                           int id = -1,
                           int showMode = smNew);
    
    ~SvPlan();
    
    int     t_id;
    QString t_planName;
    QString t_imgPath;
    QString t_description;
    
    int show_mode;
     
    
  public slots:
    virtual void accept();
    
  signals:
    sigDeviceAdded(int id);
    sigDeviceDeleted(int id);
    
  private:
    Ui::SvPlanDialog *Dialog;
};

#endif // SV_PLAN_H
