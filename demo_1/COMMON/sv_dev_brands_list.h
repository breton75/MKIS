#ifndef SV_BRANDSLIST_H
#define SV_BRANDSLIST_H

#include <QDialog>
#include <QString>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include "ui_brandslist.h"
//#include "./COMMON/sv_pgdb.h"

#include <QSqlError>

namespace Ui {
  class SvDevBrandsListDialog;
}

class SvDevBrandsListDialog : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvDevBrandsListDialog(QWidget *parent,
                                   bool showEditDelete = false,
                                   bool showSelect = false);
    
    ~SvDevBrandsListDialog();
    
    int     t_id;
    QString t_brandName;
    QString t_address;
    QString t_email;
    QString t_site;
    QString t_description;


    
  private slots:
    void on_DEVBRAND_UI_closed();
    
  public slots:
    virtual void accept() Q_DECL_OVERRIDE;
    
    void slotNewBrand();
    void slotEditBrand();
    void slotDeleteBrand();

    
  private:
    Ui::SvDevBrandsListDialog *Dialog;
    //QStandardItemModel* model = new QStandardItemModel();
    QSqlQueryModel *p_brands_model;
    int setBrandListTable();
    
};

#endif // SV_BRANDSLIST_H
