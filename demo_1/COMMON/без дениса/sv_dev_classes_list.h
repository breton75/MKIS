#ifndef SV_CLASSESLIST_H
#define SV_CLASSESLIST_H

#include <QDialog>
#include <QString>
#include <QStandardItemModel>
#include <QDebug>

#include "ui_classeslist.h"

namespace Ui {
  class SvDevClassesListDialog;
}

class SvDevClassesListDialog : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode { smNew = 0, smEdit = 1 };
                    
    explicit SvDevClassesListDialog(QWidget *parent,
                                    bool showEditDelete = false,
                                    bool showSelect = true);
    
    ~SvDevClassesListDialog();
    
    int     t_id;
    QString t_className;
    QString t_libPath;
    QString t_description;
    
  private slots:
    void on_DEVCLASS_UI_closed();
    
  public slots:
    virtual void accept() Q_DECL_OVERRIDE;
    
    void slotNewClass();
    void slotEditClass();
    void slotDeleteClass();
    
  private:
    Ui::SvDevClassesListDialog *Dialog;
    QStandardItemModel* model = new QStandardItemModel();
    
    int setClassListTable();
    
};

#endif // SV_CLASSESLIST_H
