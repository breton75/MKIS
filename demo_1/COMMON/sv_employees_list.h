#ifndef SV_EMPLOYEESLIST_H
#define SV_EMPLOYEESLIST_H

#include "ui_employeeslist.h"

#include <QDialog>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Ui {
  class SvEmployeesListDialog;
}

class SvEmployeesList : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvEmployeesList(QWidget *parent,
                                    bool showEditDelete = false,
                                    bool showSelect = true);
    
    ~SvEmployeesList();
    
        int t_id; 
    QString t_employee_name = "";
    QString t_employee_patronymic = "";
    QString t_employee_surename = "";
    QString t_employee_position = "";
        int t_key_id;
    quint32 t_key_value = 0;
    QDate   t_birth_date;
    QString t_description = "";
    
  private slots:
    void on_EMPLOYEE_UI_closed();
    
  public slots:
    virtual void accept() Q_DECL_OVERRIDE;
    
    void on_bnNewEmployee_clicked();
    void on_bnEditEmployee_clicked();
    void on_bnDeleteEmployee_clicked();
    
  private:
    Ui::SvEmployeesListDialog *ui;
   // QStandardItemModel* model = new QStandardItemModel();
    QSqlQueryModel *p_employees_model;
    int setEmployeesListTable();
    
};

#endif // SV_EMPLOYEESLIST_H
