#ifndef SV_MODELSLIST_H
#define SV_MODELSLIST_H

#include <QDialog>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>

#include "ui_modelslist.h"

namespace Ui {
  class SvDevModelsListDialog;
}

class SvDevModelsList : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvDevModelsList(QWidget *parent,
                             bool showEditDelete = false,
                             bool showSelect = false);
    
    ~SvDevModelsList();
    
    int     t_id;
    QString t_modelName;
    QString t_className;
    QString t_brandName;
    QString t_libPath;
    int t_default_port;
    QString t_description;
    
  private slots:
    void on_DEVMODEL_UI_closed();
    
  public slots:
    void accept() Q_DECL_OVERRIDE;
    
    void slotNewModel();
    void slotEditModel();
    void slotDeleteModel();

    
  private:
    Ui::SvDevModelsListDialog *Dialog;
    QStandardItemModel* model = new QStandardItemModel();
    
    int setModelListTable();
};

#endif // SV_MODELSLIST_H
