#ifndef SVALARMTREEVIEW_H
#define SVALARMTREEVIEW_H

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
#include <QMap>
#include <QSqlError>
#include <QSqlQuery>

enum AlarmItemTypes
{
  aitAlarm = 65537,
  aitDevice,
  aitDeviceClass,
  aitVar,
  aitValue,
  aitAlarmType,  
  aitZoneName,
  
  aitVideo,
  aitRls,
  aitController,
  aitSensor,
  aitScud,
  aitVideoAnalitics,
  aitArchServer,
};

/** определяем типы элементов дерева **/
class SvAlarmItem: public QStandardItem
{
  public:
    explicit SvAlarmItem(const QString &text) { setText(text); }
    int type() const { return aitAlarm; }
};

class SvAlarmVideoItem: public QStandardItem
{
  public:
    explicit SvAlarmVideoItem(const QString &text) { setText(text); }
    int type() const { return aitVideo; }
};

class SvAlarmRlsItem: public QStandardItem
{
  public:
    explicit SvAlarmRlsItem(const QString &text) { setText(text); }
    int type() const { return aitRls; }
};

class SvAlarmControllerItem: public QStandardItem
{
  public:
    explicit SvAlarmControllerItem(const QString &text) { setText(text); }
    int type() const { return aitController; }
};

class SvAlarmSCUDItem: public QStandardItem
{
  public:
    explicit SvAlarmSCUDItem(const QString &text) { setText(text); }
    int type() const { return aitScud; }
};

//class SvAlarmValueItem: public QStandardItem
//{
//  public:
//    explicit SvAlarmValueItem(const QString &text) { setText(text); }
//    int type() const { return aitValue; }
//};

//class SvAlarmTypeItem: public QStandardItem
//{
//  public:
//    explicit SvAlarmTypeItem(const QString &text) { setText(text); }
//    int type() const { return aitAlarmType; }
//};

//class SvAlarmZoneItem: public QStandardItem
//{
//  public:
//    explicit SvAlarmZoneItem(const QString &text) { setText(text); }
//    int type() const { return aitZoneName; }
//};

/** **************************************** **/

struct AlarmDump
{
  QString alarmRoot;
  QString alarmItem;
  int alarmType;
  int itemType;
  
  QString varName;
  QString deviceName;
  qreal value;
  QString className;
  QString ip;
  QString zoneName;
  QString alarmName;
};

class SvAlarmTreeView : public QTreeView
{
  Q_OBJECT
  
  public:
    explicit SvAlarmTreeView(QWidget* parent);
    
    ~SvAlarmTreeView();
    
    QStandardItemModel* a_treeModel = new QStandardItemModel;
    
    QStandardItem *rootNode = a_treeModel->invisibleRootItem();

//    SvAlarmItem *itemAlarm;
//    SvAlarmDeviceItem *itemDevice;
//    SvAlarmDeviceClassItem *itemDeviceClass;
//    SvAlarmVarItem *itemVar;
//    SvAlarmValueItem *itemValue;
//    SvAlarmTypeItem *itemAlarmtype;
//    SvAlarmZoneItem *itemZone;
    
    QModelIndex selected() { return selectedIndexes().at(0); }
    
    int newAlarm(QString device_ip, qreal value/*, QString device_name*/);
    
  private:
    void contextMenuEvent(QContextMenuEvent * event) Q_DECL_OVERRIDE ;
    void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
        
    QIcon icoError;
    QIcon icoWarning;
    QIcon icoItem;
    
    QMap<QModelIndex, AlarmDump> alarm_items;

  private slots:
    void on_ALARM_DIALOG_UI_closed(QObject*);
    
};


#endif // SVALARMTREEVIEW_H
