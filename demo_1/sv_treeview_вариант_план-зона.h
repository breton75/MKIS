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
  itPlanZones,
  itPlan,
  itZone,
  itEmployees,
  itEmployee,
  itView,
  itVideoView,
  itAlarms,
  itRlsView, 
  itReports,
  itArchiving,
  
  itDevicesByZone
};

/** определяем типы элементов дерева **/
class SvDeviceItem: public QStandardItem
{
  public:
    explicit SvDeviceItem(const QString &text) { setText(text); }
    int type() const { return itDevice; }
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

class SvPlanItem: public QStandardItem
{
  public:
    explicit SvPlanItem(const QString &text) { setText(text); }
    int type() const { return itPlan; }
};

class SvZoneItem: public QStandardItem
{
  public:
    explicit SvZoneItem(const QString &text) { setText(text); }
    int type() const { return itZone; }
};

/** **************************************** **/

class SvTreeView : public QTreeView
{
  public:
    explicit SvTreeView(QWidget* parent);
//    explicit SvTreeView(QWidget* parent, QString zoneName, QString planName);
//    explicit SvTreeView(QWidget* parent, int itemTypes, QString value);
    
    ~SvTreeView();
    
    QStandardItemModel* treeModel = new QStandardItemModel;
    
    //defining items
    QStandardItem *rootNode = treeModel->invisibleRootItem();
//    QStandardItem *itemConfig = new QStandardItem("Конфигурация");
    QStandardItem *itemDevices; // =  new QStandardItem("Устройства");
    QStandardItem *itemVideo; // =  new QStandardItem("Видеокамера");
    QStandardItem *itemRls; // =  new QStandardItem("РЛС");
    QStandardItem *itemControllers; // =  new QStandardItem("Контроллер");
    QStandardItem *itemSensors; // =  new QStandardItem("Датчик");
    QStandardItem *itemScud; // =  new QStandardItem("СКУД");
    QStandardItem *itemVAnalitics; //=  new QStandardItem("Сервер видеоаналитики");
    QStandardItem *itemArchServer; // =  new QStandardItem("Сервер архивации");     
    
    QStandardItem *itemVariables; // =  new QStandardItem("Переменные");  
//    QStandardItem *itemPlans =     new QStandardItem("Планы");
    QStandardItem *itemZones; // =  new QStandardItem("Зоны безопасности");
    QStandardItem *itemEmployees; // =  new QStandardItem("Сотрудники");
    QStandardItem *itemView; // =   new QStandardItem("Просмотр");
    QStandardItem *itemVideoView; // =   new QStandardItem("Видеокамеры");
    QStandardItem *itemRlsView; // =    new QStandardItem("РЛС");
    QStandardItem *itemAlarmView; // =    new SvAlarmsItem("Тревоги и события");
    QStandardItem *itemReports; // =  new QStandardItem("Отчеты");
    QStandardItem *itemArchiving; // =  new QStandardItem("Архивация");         
    
    QList<QAction*>* actionsDevices = new QList<QAction*>;
    QList<QAction*>* actionsVideo = new QList<QAction*>;
    QList<QAction*>* actionsRls = new QList<QAction*>;
    QList<QAction*>* actionsControllers = new QList<QAction*>;
    QList<QAction*>* actionsSensors = new QList<QAction*>;
    QList<QAction*>* actionsScud = new QList<QAction*>;
    QList<QAction*>* actionsVAnalitics = new QList<QAction*>;
    QList<QAction*>* actionsArchServer = new QList<QAction*>;
    
    QList<QAction*>* actionsVariables = new QList<QAction*>;
    QList<QAction*>* actionsPlans = new QList<QAction*>;
    QList<QAction*>* actionsZones = new QList<QAction*>;
    QList<QAction*>* actionsEmployees = new QList<QAction*>;
    QList<QAction*>* actionsView = new QList<QAction*>;
    QList<QAction*>* actionsVideoView = new QList<QAction*>;
    QList<QAction*>* actionsRlsView = new QList<QAction*>;
    QList<QAction*>* actionsReports = new QList<QAction*>;
    QList<QAction*>* actionsArchiving = new QList<QAction*>;
    
    QModelIndex selected() { return selectedIndexes().at(0); }
    
    void loadDevices(QString zoneName = "");
//    void loadPlans();
    void loadZones();
    void loadVars();
    void loadEmployees();
    void loadView();
    void loadArchiving();
    
  private:
    void contextMenuEvent(QContextMenuEvent * event) Q_DECL_OVERRIDE ;
//    void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    
    QList<QAction*>* actionList = new QList<QAction*>;
    
    
    
  public slots:
    void doubleClick();
    
};


#endif // SVTREEVIEW_H
