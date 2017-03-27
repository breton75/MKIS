#include "sv_alarmsTreeView.h"
#include "./COMMON/sv_settings.h"
#include "sv_zonedraw.h"
#include "sv_zone.h"
#include "sv_alarmdialog.h"
#include "./COMMON/sv_pgdb.h"
#include "./COMMON/sql_select_defs.h"

extern SvPGDB* PGDB;
extern SvAlarmDialog* ALARM_DIALOG_UI;
QList<SvAlarmDialog*> adlgList;

void makeAlarmString(QString device_ip, qreal value, AlarmDump *ad);

SvAlarmTreeView::SvAlarmTreeView(QWidget *parent)
//  QWidget(parent)
{
  this->setParent(parent);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->setHeaderHidden(true);
//  this->setDragEnabled(true);
  this->setDragDropMode(QAbstractItemView::DragOnly);
  
  QFont font;
  font.setBold(true);
  font.setWeight(75);
  this->setFont(font);
  
  icoWarning = QIcon(":/tree32/icons/Warning.ico");
  icoError = QIcon(":/tree32/icons/Error.ico");
  icoItem = QIcon(":/alarms/icons/bullet_red.png");
    
  this->setModel(a_treeModel);
//  this->expandAll();
  this->setVisible(true);
  
//  connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemDoubleClicked(QModelIndex)));
}

SvAlarmTreeView::~SvAlarmTreeView()
{
  this->deleteLater();
}

void makeAlarmString(QString device_ip, qreal value, AlarmDump* ad)
{
//  ad->varName = var_name;
  ad->ip = device_ip;
  ad->value = value;
  
//  QString s = QApplication::applicationDirPath() + "/ini/vars.ini";
//  SvSettings* vsett = new SvSettings(s);

//  QStringList lst = vsett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
//  {
//    s = vsett->readValue(lst.at(i), "var", "").toString();
//    if(s.section('%', 1, 1) == ad->varName)
//    {
//      ad->deviceName = s.section('%', 2, 2);
//      ad->alarmName  = s.section('%', 5, 5); 
//      ad->alarmType = s.section('%', 6, 6).toInt();
//    }
//  }
  
//  s = QApplication::applicationDirPath() + "/ini/devices.ini";
//  SvSettings* devsett = new SvSettings(s);

//  lst = devsett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
//  {
//    s = devsett->readValue(lst.at(i), "device", "").toString();
//    if(s.section('%', 1, 1) == ad->deviceName)
//    {
//      ad->className = s.section('%', 2, 2);
//      ad->zoneName = s.section('%', 7, 7); 
//      ad->ip = s.section('%', 5, 5);
//    }
//  }
    
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL(QString(D_SELECT_FROM_DEVICES_WHERE_2).arg("ip").arg("'" + ad->ip + "'"), q);
  
  if(q->size())
  {
    q->first();
    ad->deviceName = q->value("device_name").toString();
    ad->className = q->value("device_class").toString();
    ad->zoneName = q->value("zone_name").toString(); 
    ad->alarmType == value;
    ad->varName = "";
    
    q->finish();
    free(q);
    
    ad->alarmRoot = QString("%1: %2: %3: %4(%5)   Зона: %6   Переменная %7=%8")
                        .arg(ad->alarmType == 1 ? "Тревога" : "Предупреждение")
                        .arg(ad->alarmName)
                        .arg(ad->className)
                        .arg(ad->deviceName)
                        .arg(ad->ip)
                        .arg(ad->zoneName)
                        .arg(ad->varName)
                        .arg(ad->value);
    
    ad->alarmItem = QString("Устройство: %1 %2(%3)\nЗона: %4\nПеременная %5 = %6")
                        .arg(ad->className)
                        .arg(ad->deviceName)
                        .arg(ad->ip)
                        .arg(ad->zoneName)
                        .arg(ad->varName)
                        .arg(ad->value);
    
    if(ad->className == "Видеокамера") ad->itemType = aitVideo;
    else if(ad->className == "РЛС") ad->itemType = aitRls;
    else if(ad->className == "Контроллер") ad->itemType = aitRls;
    else if(ad->className == "СКУД") ad->itemType = aitScud;
  }
}

void SvAlarmTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  
}

void SvAlarmTreeView::mouseDoubleClickEvent(QMouseEvent * event)
{
  QModelIndex current_index = this->currentIndex();

   
  switch (a_treeModel->itemFromIndex(current_index)->type())
  {
    case aitVideo:
    case aitRls:  
    case aitController:
    {
      ALARM_DIALOG_UI = new SvAlarmDialog(alarm_items.value(current_index).zoneName,
                                          alarm_items.value(current_index).deviceName,
                                          alarm_items.value(current_index).alarmType,
                                          this);
      
      connect(ALARM_DIALOG_UI, SIGNAL(accepted()), this, SLOT(on_ALARM_DIALOG_UI_closed()));
      connect(ALARM_DIALOG_UI, SIGNAL(rejected()), this, SLOT(on_ALARM_DIALOG_UI_closed()));

      break;
    }
      
//    case aitRls:
//      qDebug() << "rls";
//      break;
      
//    case aitController:
//      qDebug() << "controller";
//      break;      
  }
  
  QTreeView::mouseDoubleClickEvent(event);
}

void SvAlarmTreeView::on_ALARM_DIALOG_UI_closed(QObject* obj)
{
  if(ALARM_DIALOG_UI->result() == QDialog::Accepted)
  {
    
  }
  else if(ALARM_DIALOG_UI->result() == QDialog::Rejected)
    qDebug() << "rejected";
  
  ALARM_DIALOG_UI->~SvAlarmDialog();
  ALARM_DIALOG_UI = 0;
}

int SvAlarmTreeView::newAlarm(QString device_ip, qreal value)
{
  for(int i = 0; i < this->a_treeModel->rowCount(); i++)
  {
    AlarmDump ad;
    makeAlarmString(device_ip, value, &ad);
    if((this->a_treeModel->item(i)->type() == aitAlarm) &
       (this->a_treeModel->item(i)->text() == ad.alarmRoot))
    {
//      this->setCurrentIndex(this->a_treeModel->item(i)->index());
      return 1;
    }
  }
  
  AlarmDump ad;
  QBrush br;
  br.setStyle(Qt::SolidPattern);
  
  /* заполняем данные о тревоге */
  makeAlarmString(device_ip, value, &ad);
  
  /* создаем корневую запись о тревоге */
  SvAlarmItem* a_item = new SvAlarmItem(ad.alarmRoot);
  
  switch (ad.alarmType) {
    case 2:  // тревога
      a_item->setIcon(icoError);
      br.setColor(QColor(255, 0, 0, 60));
      a_item->setBackground(br);
      break;
      
    default:  // предупреждение
      a_item->setIcon(icoWarning);
      br.setColor(QColor(255, 240, 10, 60));
      a_item->setBackground(br);
      break;
  }

  rootNode->appendRow(a_item);
  
  /* добавляем подробное описание для тревоги */
  
  /* для каждого класса устройств создаем свой тип записи, чтобы потом 
   * определить действия для этой запись */
  QModelIndex indx;
  QStandardItem* d_item;
  switch (ad.itemType)
  {
    case aitVideo:
    {
      d_item = new SvAlarmVideoItem(ad.alarmItem);
      break;
    }
      
    case aitRls:
    {
      d_item = new SvAlarmRlsItem(ad.alarmItem);
      break;
    }
      
    case aitController:
    {
      d_item = new SvAlarmControllerItem(ad.alarmItem);
      break;
    }
      
    case aitScud:
    {
      d_item = new SvAlarmSCUDItem(ad.alarmItem);
      break;
    }      
      
  }
  
  a_item->appendRow(d_item);
  
  indx = d_item->index();
  
  alarm_items.insert(indx, ad);
  
  this->setCurrentIndex(indx);
  
  adlgList.append(new SvAlarmDialog(alarm_items.value(indx).zoneName,
                                    alarm_items.value(indx).deviceName,
                                    alarm_items.value(indx).alarmType,
                                    this));
  
//  connect(adlgList.last(), SIGNAL(destroyed()), SLOT(~SvAlarmDialog));
  
//  connect(ALARM_DIALOG_UI, SIGNAL(destroyed(QObject*)), this, SLOT(on_ALARM_DIALOG_UI_closed(QObject*)));
  
  
//  connect(ALARM_DIALOG_UI, SIGNAL(accepted()), this, SLOT(on_ALARM_DIALOG_UI_closed()));
//  connect(ALARM_DIALOG_UI, SIGNAL(rejected()), this, SLOT(on_ALARM_DIALOG_UI_closed()));
  
}


    
    
    
    
    
    
    
    
    
