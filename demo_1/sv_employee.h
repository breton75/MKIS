#ifndef SV_EMPLOYEE_H
#define SV_EMPLOYEE_H

#include "ui_sv_employee.h"

#include <QDialog>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
  class SvEmploeeDialog;
}

class SvEmployee : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
    
    explicit SvEmployee(QWidget *parent,
                        int showMode = smNew,
                        int emploeeID = -1);
    ~SvEmployee();
    
   int showMode; 
       int t_id; 
   QString t_employee_name = "";
   QString t_employee_patronymic = "";
   QString t_employee_surename = "";
   QString t_employee_position = "";
       int t_key_id = -1;
   quint32 t_key_value = 0;
   QDate   t_birth_date;
   QString t_description = "";
    
   void accept() Q_DECL_OVERRIDE;
   
  private:
    Ui::SvEmploeeDialog *ui;
    
  private slots:
    void on_bnSelectScud_clicked();
    void on_bnNewScud_clicked();
    void on_SCUDSLIST_UI_closed();
    void on_SCUD_UI_closed();
    
};

#endif // SV_EMPLOYEE_H
