#ifndef SVDEVICELIST_H
#define SVDEVICELIST_H

#include <QObject>
#include <QtWidgets/QTableView>

#include "sv_device.h"
#include "ui_devicelist.h"
#include "ui_device.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
using namespace sql_select_defs;
using namespace sql_insert_defs;

//int setDeviceListTable(QSqlQueryModel* queryModel, QTableView* table);

namespace Ui {
  class SvDeviceListDialog;
}

class SvDevicesList : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvDevicesList(QWidget *parent,
                           bool showEditDelete = false,
                           bool showSelect = true);
    
    ~SvDevicesList();
    
//    QSqlQueryModel *m_device_list;
    
    int     t_id;
    QString t_deviceName;
    QString t_ip;
    int     t_port;
    QString t_modelName;
    QString t_className;
    QString t_brandName;
    QString t_libPath;
    int     t_X;
    int     t_Y;
    QString t_zoneName;
    QString t_description;
    
  public slots:
    virtual void accept() Q_DECL_OVERRIDE;
    
    void slotNewDevice();
    void slotEditDevice();
    void slotDeleteDevice();
    
  private:
    Ui::SvDeviceListDialog *Dialog;
    
   // QTableView*     p_tbl_devices;
     QSqlQueryModel *p_devices_model;
    int setDeviceListTable();
    
  private slots:
    void on_DEV_UI_closed();

};

#endif // SVDEVICELIST_H
