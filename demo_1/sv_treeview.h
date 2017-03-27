#ifndef SVTREEVIEW_H
#define SVTREEVIEW_H

#include <QTreeView>
#include <QWidget>
#include <QStandardItemModel>
#include <QList>
#include <QStandardItem>
#include <QApplication>
#include <QDebug>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include <QMdiArea>
#include <QSqlQuery>
#include <QSqlError>
#include <QProgressDialog>
#include <QtEndian>
#include <QVBoxLayout>

struct DragInfo
{
  bool isActive;
  QString sourceClassName;
  QString srcItemText;
  int srcItemType;
};

enum ItemTypes
{
  itDevices = 65537,
  itDevice,
  itVideo,
  itRls,
  itControllers,
  itSensors,
  itScud,
  itVideoAnalitics,
  itArchServer,
               
  itVariables,
  itVariable,
  itZones,
  itZone,
  itEmployees,
  itEmployee,
  itKeys,
  itKey,
  itView,
  itVideoView,
  itAlarms,
  itRlsView, 
  itReports,
  itArchiving,
  itArchVideo,
  itArchRls,
  itArchSCUD,
  
  itDevicesByZone
};

/** определяем типы элементов дерева **/
class SvDevicesItem: public QStandardItem
{
  public:
    explicit SvDevicesItem(const QString &text) { setText(text); }
    int type() const { return itDevices; }
};

class SvDeviceItem: public QStandardItem
{
  public:
    explicit SvDeviceItem(const QString &text) { setText(text); }
    int type() const { return itDevice; }
};

class SvVideoItem: public QStandardItem
{
  public:
    explicit SvVideoItem(const QString &text) { setText(text); }
    int type() const { return itVideo; }
};

class SvRlsItem: public QStandardItem
{
  public:
    explicit SvRlsItem(const QString &text) { setText(text); }
    int type() const { return itRls; }
};

class SvVariableItem: public QStandardItem
{
  public:
    explicit SvVariableItem(const QString &text) { setText(text); }
    int type() const { return itVariable; }
};

class SvAlarmsItem: public QStandardItem
{
  public:
    explicit SvAlarmsItem(const QString &text) { setText(text); }
    int type() const { return itAlarms; }
};

class SvZonesItem: public QStandardItem
{
  public:
    explicit SvZonesItem(const QString &text) { setText(text); }
    int type() const { return itZones; }
};

class SvZoneItem: public QStandardItem
{
  public:
    explicit SvZoneItem(const QString &text) { setText(text); }
    int type() const { return itZone; }
};

class SvKeysItem: public QStandardItem
{
  public:
    explicit SvKeysItem(const QString &text) { setText(text); }
    int type() const { return itKeys; }
};

class SvKeyItem: public QStandardItem
{
  public:
    explicit SvKeyItem(const QString &text) { setText(text); }
    int type() const { return itKey; }
};

class SvEmployeesItem: public QStandardItem
{
  public:
    explicit SvEmployeesItem(const QString &text) { setText(text); }
    int type() const { return itEmployees; }
};

class SvEmployeeItem: public QStandardItem
{
  public:
    explicit SvEmployeeItem(const QString &text) { setText(text); }
    int type() const { return itEmployee; }
};

class SvVideoViewItem: public QStandardItem
{
  public:
    explicit SvVideoViewItem(const QString &text) { setText(text); }
    int type() const { return itVideoView; }
};

class SvArchVideoItem: public QStandardItem
{
  public:
    explicit SvArchVideoItem(const QString &text) { setText(text); }
    int type() const { return itArchVideo; }
};

class SvArchRlsItem: public QStandardItem
{
  public:
    explicit SvArchRlsItem(const QString &text) { setText(text); }
    int type() const { return itArchRls; }
};

class SvArchSCUDItem: public QStandardItem
{
  public:
    explicit SvArchSCUDItem(const QString &text) { setText(text); }
    int type() const { return itArchSCUD; }
};

/** **************************************** **/

class SvTreeView : public QTreeView
{
  Q_OBJECT
  
  public:
    explicit SvTreeView(QWidget* parent, QMdiArea* mdiWindow = 0);
//    explicit SvTreeView(QWidget* parent, QString zoneName, QString planName);
//    explicit SvTreeView(QWidget* parent, int itemTypes, QString value);
    
    ~SvTreeView();
    
    QStandardItemModel* treeModel = new QStandardItemModel;
    
    //defining items
    QStandardItem *rootNode = treeModel->invisibleRootItem();
//    QStandardItem *itemConfig = new QStandardItem("Конфигурация");
    SvDevicesItem *itemDevices; // =  new QStandardItem("Устройства");
    SvVideoItem   *itemVideo; // =  new QStandardItem("Видеокамера");
    SvRlsItem     *itemRls; // =  new QStandardItem("РЛС");
    QStandardItem *itemControllers; // =  new QStandardItem("Контроллер");
    QStandardItem *itemSensors; // =  new QStandardItem("Датчик");
    QStandardItem *itemScud; // =  new QStandardItem("СКУД");
    QStandardItem *itemVAnalitics; //=  new QStandardItem("Сервер видеоаналитики");
    QStandardItem *itemArchServer; // =  new QStandardItem("Сервер архивации");     
    
    QStandardItem *itemVariables; // =  new QStandardItem("Переменные");  
    SvKeysItem    *itemKeys; // =     new QStandardItem("Планы");
    SvZonesItem   *itemZones; // =  new QStandardItem("Зоны безопасности");
  SvEmployeesItem *itemEmployees; // =  new QStandardItem("Сотрудники");
    QStandardItem *itemView; // =   new QStandardItem("Просмотр");
    QStandardItem *itemVideoView; // =   new QStandardItem("Видеокамеры");
    QStandardItem *itemRlsView; // =    new QStandardItem("РЛС");
    QStandardItem *itemAlarmView; // =    new SvAlarmsItem("Тревоги и события");
    QStandardItem *itemReports; // =  new QStandardItem("Отчеты");
    QStandardItem *itemArchiving; // =  new QStandardItem("Архивация"); 
  SvArchVideoItem *itemArchVideo;
    SvArchRlsItem *itemArchRls;
   SvArchSCUDItem *itemArchSCUD;
    
    QAction *actionDevices;
    QAction *actionNewDevice;
    QAction *actionEditDevice;
    QAction *actionDeleteDevice;    
    QAction *actionVariables;
    QAction *actionZones;
    QAction *actionNewZone;
    QAction *actionEditZone;
    QAction *actionDeleteZone;
    QAction *actionReloadZones;
    QAction *actionNewSCUD;
    QAction *actionEditSCUD;
    QAction *actionDeleteSCUD;
    QAction *actionReloadSCUDs;
    QAction *actionConfigSCUDs;
    QAction *actionEmployees;
    QAction *actionNewEmployee;
    QAction *actionEditEmployee;
    QAction *actionDeleteEmployee;
    QAction *actionReloadEmployees;
    QAction *actionVideoView;
    QAction *actionAlarms;
    QAction *actionPlaySingleVideo;
    QAction *actionPlaySingleRls;
    QAction *actionArchVideo;
    QAction *actionArchRls;
    QAction *actionArchSCUD;
    QAction *actionConfigArchVideo;
    QAction *actionConfigArchRls;
    QAction *actionConfigArchSCUD;
    
    QModelIndex selected() { return selectedIndexes().at(0); }
    
    void loadDevices(QString zoneName = "", bool reload = false);
//    void loadPlans();
    void loadZones(bool reload = false);
    void loadVars();
    void loadKeys(bool reload = false);
    void loadEmployees(bool reload = false);
    void loadView();
    void loadArchiving();
    
  private:
    QMdiArea* mdiWindow;
    
    void contextMenuEvent(QContextMenuEvent * event) Q_DECL_OVERRIDE ;
    void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
//    void dragLeaveEvent(QDragLeaveEvent * event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    QList<QAction*>* actionList = new QList<QAction*>;

  private slots:
    void on_actionDevices_triggered();
    void on_actionNewDevice_triggered();
    void on_actionEditDevice_triggered();
    void on_DEV_UI_closed();
    void on_actionDeleteDevice_triggered();    
    void on_actionVariables_triggered();
    void on_actionZones_triggered(QString zoneName = "");
    void on_actionNewZone_triggered();
    void on_NEW_ZONE_UI_closed();
    void on_actionEditZone_triggered();
    void on_ZONE_UI_closed();
    void on_actionDeleteZone_triggered();
    void on_actionReloadZones_triggered();
    void on_actionEmployeers_triggered();
    void on_actionVideoView_triggered();
    void on_actionNewSCUD_triggered();
    void on_actionEditSCUD_triggered();
    void on_SCUD_UI_closed();
    void on_actionReloadSCUDs_triggered(); 
    void on_actionConfigSCUDs_triggered();
    void on_actionNewEmployee_triggered();
    void on_actionEditEmployee_triggered();
    void on_EMPLOYEE_UI_closed();
    void on_actionReloadEmployees_triggered();
    
    void on_actionPlaySingleVideo_triggered();
    void on_actionPlaySingleRls_triggered();
    void on_SINGLERLS_UI_closed();
    
    void on_actionArchVideo_triggered();
    void on_actionArchRls_triggered();
    void on_SELECT_RSL_ARCH_UI_closed();
    void on_actionArchSCUD_triggered();
    
    void on_actionConfigArchVideo_triggered();
    void on_actionConfigArchRls_triggered();  
    void on_actionConfigArchSCUD_triggered(); 
    
    
    
//    void on_actionAlarms_triggered();
//    void on__triggered();    
    
  public slots:
//    void doubleClick();

    
};


#endif // SVTREEVIEW_H
