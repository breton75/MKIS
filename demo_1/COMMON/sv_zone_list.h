#ifndef SVZONELIST_H
#define SVZONELIST_H

#include <QObject>
#include <QtWidgets/QTableView>
#include <QSplitter>
#include <QSqlRecord>
#include <QSqlQueryModel>

#include "sv_device.h"
#include "ui_zonelist.h"
#include "./sv_zone.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_zonedraw.h"

using namespace sql_select_defs;
using namespace sql_insert_defs;

//int setDeviceListTable(QSqlQueryModel* queryModel, QTableView* table);

namespace Ui {
  class SvZonesListDialog;
}

class SvZonesList : public QDialog
{
    Q_OBJECT
    
  public:
    explicit SvZonesList(QWidget *parent,
                           bool showEditDelete = false,
                           bool showNew  = true,
                           bool showSelect = true);
    
    ~SvZonesList();
    
//    QSqlQueryModel *m_device_list;
    
    int t_id;
    QString t_zoneName;
    QString t_parentZoneName;
    QString t_description;   
    
    QTableView* tblZonesList;
    
    SvZoneDrawWidget* zdw;
    
  public slots:
    virtual void accept() Q_DECL_OVERRIDE;
    
    void slotNewZone();
    void slotEditZone();
    void slotDeleteZone();
    
    void tableClicked(QModelIndex mi);
    
  private:
    Ui::SvZonesListDialog *dlg;
//    QStandardItemModel* model = new QStandardItemModel();
    QSqlQueryModel *m_zones_model;
    
    int setZonesListTable();
    
  private slots:
    void on_ZONE_UI_closed();

};

#endif // SVZONELIST_H
