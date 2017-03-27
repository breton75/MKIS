#include "sv_treeview.h"
#include "./COMMON/sv_settings.h"
#include "sv_zonedraw.h"
#include "sv_zone.h"

void addToTree();
//extern SvZone* ZONE_UI;


SvTreeView::SvTreeView(QWidget *parent)
//  QWidget(parent)
{
  this->setParent(parent);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->setHeaderHidden(true);
//  this->setDragEnabled(true);
  this->setDragDropMode(QAbstractItemView::DragOnly);
  
  this->setModel(treeModel);
//  this->expandAll();
  this->setVisible(true);
}

SvTreeView::~SvTreeView()
{
  
}

void SvTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu* menu = new QMenu(this);
  
  if(this->currentIndex() == itemDevices->index())
  {
    menu->addActions(*this->actionsDevices);
    
    menu->setTitle("Устройства");
  }
  
  else if(this->currentIndex() == this->itemVideoView->index())
  {
    menu->addActions(*this->actionsVideoView);
    menu->setTitle("Видеонаблюдение");
  }
  
  else if(this->currentIndex() == this->itemZones->index())
  {
    menu->addActions(*this->actionsPlans);
    menu->setTitle("Зоны безопасности");
  }  
  
  menu->exec(event->globalPos());
}

//void SvTreeView::mouseDoubleClickEvent(QMouseEvent * event)
//{
////  QTreeView::mouseDoubleClickEvent(event);
//}

void SvTreeView::doubleClick()
{
  
}

void SvTreeView::loadDevices(QString zoneName)
{
  itemDevices =  new QStandardItem("Устройства");
  itemDevices->setIcon(QIcon(":/tree32/icons/cpu_16.ico"));
  
  rootNode->appendRow(itemDevices);
  
  itemVideo =  new QStandardItem("Видеокамера");  
  itemVideo->setIcon(QIcon(":/tree32/icons/videocam.ico"));
  
  itemRls =  new QStandardItem("РЛС"); 
  itemRls->setIcon(QIcon(":/tree32/icons/rls.ico"));
  
  itemControllers =  new QStandardItem("Контроллер"); 
  itemControllers->setIcon(QIcon(":/tree32/icons/wagon.ico"));
  
  itemSensors =  new QStandardItem("Датчик"); 
  itemSensors->setIcon(QIcon(":/tree32/icons/Star2.bmp"));
  
  itemScud =  new QStandardItem("СКУД");  
  itemScud->setIcon(QIcon(":/tree32/icons/Key_16.ico"));
  
  itemVAnalitics =  new QStandardItem("Сервер видеоаналитики");
  itemVAnalitics->setIcon(QIcon(":/tree32/icons/Eye.bmp"));
  
  itemArchServer =  new QStandardItem("Сервер архивации");     
  itemArchServer->setIcon(QIcon(":/tree32/icons/Database.ico"));
  
  itemDevices->appendRow(itemVideo);
  itemDevices->appendRow(itemRls);
  itemDevices->appendRow(itemControllers);
  itemDevices->appendRow(itemSensors);
  itemDevices->appendRow(itemScud);
  itemDevices->appendRow(itemVAnalitics);
  itemDevices->appendRow(itemArchServer);
  
  QFont fnt_normal = QFont(this->font().family(), this->font().pixelSize(), QFont::Normal);
  fnt_normal.setStrikeOut(false);
  
  QFont fnt_inZone = QFont(this->font().family(), this->font().pixelSize(), QFont::Bold);
  fnt_inZone.setStrikeOut(false);
  
  QFont fnt_outZone = QFont(this->font().family(), this->font().pixelSize() - 1, QFont::Cursive);
  fnt_outZone.setStrikeOut(true);
  
  QString s = QApplication::applicationDirPath() + "/ini/devices.ini";
  SvSettings* devsett = new SvSettings(s);
  
  QList<QStandardItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/bullet_blue.png");
  
  QStringList lst = devsett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    s = devsett->readValue(lst.at(i), "device", "").toString();
    QString class_name = s.section('%', 2, 2);
    QString device_name = s.section('%', 1, 1);
  
    itemsList.append(new SvDeviceItem(device_name));
    itemsList.last()->setIcon(ico);
    
    if(zoneName == "") itemsList.last()->setFont(fnt_normal);
    else if(zoneName == s.section('%', 7, 7)) itemsList.last()->setFont(fnt_inZone);     
    else itemsList.last()->setFont(fnt_outZone);
    
    if((zoneName == "") | (zoneName == s.section('%', 7, 7)))
    {
      if(class_name == "Видеокамера")
        itemVideo->appendRow(itemsList.last());
      
      else if(class_name == "РЛС")
        itemRls->appendRow(itemsList.last());
      
      else if(class_name == "Контроллер")
        itemControllers->appendRow(itemsList.last());
        
      else if(class_name == "Датчик")
        itemSensors->appendRow(itemsList.last());
        
      else if(class_name == "СКУД")
        itemScud->appendRow(itemsList.last());
        
      else if(class_name == "Сервер видеоаналитики")
        itemVAnalitics->appendRow(itemsList.last());
        
      else if(class_name == "Сервер архивации")
        itemArchServer->appendRow(itemsList.last());
    }
  }
}

void SvTreeView::loadZones()
{
  itemZones =  new QStandardItem("Зоны безопасности");     
  itemZones->setIcon(QIcon(":/tree32/icons/Shield_16.ico"));
  
  rootNode->appendRow(itemZones);
  
  QString s = QApplication::applicationDirPath() + "/ini/plans.ini";
  SvSettings* psett = new SvSettings(s);
  QStringList plst = psett->appSettings->childGroups();
  
  s = QApplication::applicationDirPath() + "/ini/zones.ini";
  SvSettings* zsett = new SvSettings(s);  
  QStringList zlst = zsett->appSettings->childGroups();
  
  QList<QStandardItem*> itemsList;
  
  QIcon pico = QIcon(":/tree32/icons/ar.ico");
  QIcon zico = QIcon(":/tree32/icons/layers_1.ico");

  itemsList.append(itemZones);
  QString parentName = "";

  while(itemsList.count())
  {
    QStandardItem* parentItem = itemsList.first();
    if(parentItem == itemZones) parentName = "";
    else parentName = parentItem->text();
    
    for(int i = 0; i < plst.count(); i++)
    {
      /* читаем имя родителя */
      s = psett->readValue(plst.at(i), "plan", "").toString();
      QString plan_parent_name = s.section('%', 2, 2);
      
      /* если имя родителя соответствует текущему,
       * то смотрим, есть ли уже такой элемент */
      if(plan_parent_name == parentName)
      {
        /* имя плана */
        QString plan_name = s.section('%', 1, 1);
  
        bool found = false;
        for(int j = 0; j < parentItem->rowCount(); j++)
          found = found | ((parentItem->child(j)->type() == itPlan) & 
                           (plan_name == parentItem->child(j)->text()));
          
        if(!found)
        {
          SvPlanItem* item = new SvPlanItem(plan_name);
          item->setIcon(pico);
          item->setWhatsThis(QString("Plan %1").arg(plan_name));
          parentItem->appendRow(item);
          itemsList.append(item);
        }
        
      }
    }
     /* добавляем список зон после списка планов */
    for(int i = 0; i < zlst.count(); i++)
    {
      /* читаем имя родителя зоны */
      s = zsett->readValue(zlst.at(i), "zone", "").toString();
      QString zone_parent_name = s.section('%', 2, 2);

      /* если имя родителя соответствует текущему элементу,
       * то смотрим, есть ли уже такой элемент */
      if(zone_parent_name == parentName)
      {
        /* имя плана */
        s = zsett->readValue(zlst.at(i), "zone", "").toString();
        QString zone_name = s.section('%', 1, 1);
  
        bool found = false;
        for(int j = 0; j < parentItem->rowCount(); j++)
          found = found | ((parentItem->child(j)->type() == itZone) & 
                           (zone_name == parentItem->child(j)->text()));
          
        if(!found)
        {
          SvZoneItem* item = new SvZoneItem(zone_name);
          item->setIcon(zico);
          item->setWhatsThis(QString("Zone %1").arg(zone_name));
          parentItem->appendRow(item);
        }
      }
    }
      
    itemsList.removeFirst();
  }
}

void SvTreeView::loadVars()
{
  itemVariables =  new QStandardItem("Переменные");        
  itemVariables->setIcon(QIcon(":/tree32/icons/struct.ico"));
  
  rootNode->appendRow(itemVariables);
  
  QString s = QApplication::applicationDirPath() + "/ini/" + "vars.ini";
  SvSettings* vsett = new SvSettings(s);
  
  QList<QStandardItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/bullet_blue.png");
  
  QStringList lst = vsett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    s = vsett->readValue(lst.at(i), "var", "").toString();
    QString var_name = s.section('%', 1, 1);
    QString device_name = s.section('%', 2, 2);
   
    itemsList.append(new SvVariableItem(QString("%1 (%2)").arg(var_name, device_name)));
    itemsList.last()->setIcon(ico);
    
    itemVariables->appendRow(itemsList.last());
    
  }
}    


void SvTreeView::loadEmployees()
{
  itemEmployees =  new QStandardItem("Сотрудники");        
  itemEmployees->setIcon(QIcon(":/tree32/icons/Users.ico"));
  
  rootNode->appendRow(itemEmployees);
}

void SvTreeView::loadView()
{
  itemView =   new QStandardItem("Просмотр");              
  itemView->setIcon(QIcon(":/tree32/icons/Eye.bmp"));
  
  itemVideoView =   new QStandardItem("Видеокамеры");  
  itemVideoView->setIcon(QIcon(":/tree32/icons/videocam.ico"));
  
  itemRlsView =    new QStandardItem("РЛС");  
  itemRlsView->setIcon(QIcon(":/tree32/icons/rls.ico"));
  
  itemAlarmView =    new SvAlarmsItem("Тревоги и события");
  itemAlarmView->setIcon(QIcon(":/tree32/icons/Error.ico"));
  
  itemReports =  new QStandardItem("Отчеты");              
  itemReports->setIcon(QIcon(":/tree32/icons/Chart2.ico"));
  
  
  rootNode->appendRow(itemView);

  itemView->appendRow(itemVideoView);
  itemView->appendRow(itemRlsView);  
  itemView->appendRow(itemReports);
  itemView->appendRow(itemAlarmView);
}

void SvTreeView::loadArchiving()
{
  itemArchiving =  new QStandardItem("Архивация");         
  itemArchiving->setIcon(QIcon(":/tree32/icons/Database.ico"));
    
  rootNode->appendRow(itemArchiving);
}    
    
    
    
    
    
    
    
    
