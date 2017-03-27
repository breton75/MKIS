#include "sv_treeview.h"
#include "./COMMON/sv_settings.h"
#include "sv_zonedraw.h"
#include "sv_zone.h"
#include "sv_deviceswindow.h"
#include "./COMMON/sv_device.h"
#include "sv_videoviewwindow.h"
#include "sv_zoneswindow.h"
#include "sv_alarmswindow.h"
#include "./COMMON/sv_pgdb.h"
#include "./COMMON/log.h"
#include "sv_scud.h"
#include "sv_employee.h"
#include "./COMMON/sv_employees_list.h"
#include "sv_archvideoview.h"
#include "sv_archscudview.h"
#include "sv_rls2bitwidget.h"
#include "./COMMON/sv_ffmpeg2filesettings.h"
#include "./COMMON/sv_rls2bit2filesettings.h"
#include "./COMMON/sv_tcpserverclient.h"

using namespace log_ns;

void addToTree();
//extern SvZone* ZONE_UI;
extern SvDevice* DEV_UI;
extern SvZone* ZONE_UI;
extern SvNewZone* NEW_ZONE_UI;
extern SvDevicesWindow* DEV_WINDOW_UI;
extern SvAlarmsWindow* ALARMS_UI;
extern SvZonesWindow* ZONES_WINDOW_UI;
extern SvSCUD* SCUD_UI;
extern SvEmployee* EMPLOYEE_UI;
extern SvSingleVideoWindow* SINGLEVIDEO_UI;
extern SvArchVideoView* ARCHVIDEO_WINDOW_UI;
extern SvArchSCUDView* ARCHSCUD_WINDOW_UI;
extern SvSingleRlsWindow* SINGLERLS_UI;
extern SvFFmpeg2FileSettings* FF2F_SETTINGS_UI;
extern SvRls2bit2FileSettings* RLS2BIT_2F_SETTINGS_UI;
extern SvSelectRlsArchWindow* SELECT_RSL_ARCH_UI;

extern SvPGDB* PGDB;

DragInfo DRAG_INFO;

SvTreeView::SvTreeView(QWidget *parent, QMdiArea *mdiWindow)
//  QWidget(parent)
{
  this->setParent(parent);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->setHeaderHidden(true);
  this->mdiWindow = mdiWindow;
  
//  this->setDragEnabled(true);
  this->setDragDropMode(QAbstractItemView::DragOnly);
  
  this->setModel(treeModel);
//  this->expandAll();
  this->setVisible(true);
  
  QIcon icon;
  
  /** *********** actions ************** **/
  actionDevices = new QAction(this);
  actionDevices->setObjectName(QStringLiteral("actionDevices"));
  icon.addFile(QStringLiteral(":/tree32/icons/cpu_16.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionDevices->setIcon(icon);
  actionDevices->setText("Открыть устройства");
  connect(actionDevices, SIGNAL(triggered()), this, SLOT(on_actionDevices_triggered()));
  
  actionNewDevice = new QAction(this);
  actionNewDevice->setObjectName(QStringLiteral("actionNewDevice"));
  icon.addFile(QStringLiteral(":/icons/add_device.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionNewDevice->setIcon(icon);
  actionNewDevice->setText("Новое устройство");
  
  actionEditDevice = new QAction(this);
  actionEditDevice->setObjectName(QStringLiteral("actionEditDevice"));
  icon.addFile(QStringLiteral(":/editors/icons/Pen.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionEditDevice->setIcon(icon);
  actionEditDevice->setText("Редактировать устройство");
  
  actionDeleteDevice = new QAction(this);
  actionDeleteDevice->setObjectName(QStringLiteral("actionDeleteDevice"));
  icon.addFile(QStringLiteral(":/icons/delete_device.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionDeleteDevice->setIcon(icon);
  actionDeleteDevice->setText("Удалить устройство");
  
  actionVariables = new QAction(this);
  actionVariables->setObjectName(QStringLiteral("actionVariables"));
  icon.addFile(QStringLiteral(":/tree32/icons/struct.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionVariables->setIcon(icon);
  actionVariables->setText("Открыть переменные");
  
  actionZones = new QAction(this);
  actionZones->setObjectName(QStringLiteral("actionZones"));
  icon.addFile(QStringLiteral(":/tree32/icons/Shield_16.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionZones->setIcon(icon);
  actionZones->setText("Открыть зоны");
//  connect(actionZones, SIGNAL(triggered()), this, SLOT(on_actionZones_triggered()));
  
  actionNewZone = new QAction(this);
  actionNewZone->setObjectName(QStringLiteral("actionNewZone"));
  icon.addFile(QStringLiteral(":/tree32/icons/add_zone.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionNewZone->setIcon(icon);
  actionNewZone->setText("Новая зона");
  
  actionEditZone = new QAction(this);
  actionEditZone->setObjectName(QStringLiteral("actionEditZone"));
  icon.addFile(QStringLiteral(":/tree32/icons/edit_zone.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionEditZone->setIcon(icon);
  actionEditZone->setText("Редактировать зону");
  
  actionDeleteZone = new QAction(this);
  actionDeleteZone->setObjectName(QStringLiteral("actionDeleteZone"));
  icon.addFile(QStringLiteral(":/tree32/icons/delete_zone.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionDeleteZone->setIcon(icon);
  actionDeleteZone->setText("Удалить зону");
  
  actionReloadZones = new QAction(this);
  actionReloadZones->setObjectName(QStringLiteral("actionReloadZones"));
  icon.addFile(QStringLiteral(":/tree32/icons/Refresh.bmp"), QSize(), QIcon::Normal, QIcon::Off);
  actionReloadZones->setIcon(icon);
  actionReloadZones->setText("Обновить");
  
  actionNewSCUD = new QAction(this);
  actionNewSCUD->setObjectName(QStringLiteral("actionNewSCUD"));
  icon.addFile(QStringLiteral(":/tree32/icons/add_zone.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionNewSCUD->setIcon(icon);
  actionNewSCUD->setText("Новый ключ");
  
  actionEditSCUD = new QAction(this);
  actionEditSCUD->setObjectName(QStringLiteral("actionEditSCUD"));
  icon.addFile(QStringLiteral(":/tree32/icons/edit_zone.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionEditSCUD->setIcon(icon);
  actionEditSCUD->setText("Редактировать ключ");

  actionReloadSCUDs = new QAction(this);
  actionReloadSCUDs->setObjectName(QStringLiteral("actionReloadSCUDs"));
  icon.addFile(QStringLiteral(":/tree32/icons/Refresh.bmp"), QSize(), QIcon::Normal, QIcon::Off);
  actionReloadSCUDs->setIcon(icon);
  actionReloadSCUDs->setText("Обновить");
  
  actionConfigSCUDs = new QAction(this);
  actionConfigSCUDs->setObjectName(QStringLiteral("actionConfigSCUDs"));
  icon.addFile(QStringLiteral(":/tree32/icons/Compile-Run.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionConfigSCUDs->setIcon(icon);
  actionConfigSCUDs->setText("Применить конфигурацию");
  
  actionEmployees = new QAction(this);
  actionEmployees->setObjectName(QStringLiteral("actionEmployees"));
  icon.addFile(QStringLiteral(":/tree32/icons/Users.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionEmployees->setIcon(icon);
  actionEmployees->setText("Открыть сотрудников");
  
  actionNewEmployee = new QAction(this);
  actionNewEmployee->setObjectName(QStringLiteral("actionNewEmployee"));
  icon.addFile(QStringLiteral(":/tree32/icons/Add.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionNewEmployee->setIcon(icon);
  actionNewEmployee->setText("Новый сотрудник");
  
  actionEditEmployee = new QAction(this);
  actionEditEmployee->setObjectName(QStringLiteral("actionEditEmployee"));
  icon.addFile(QStringLiteral(":/tree32/icons/Modify.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionEditEmployee->setIcon(icon);
  actionEditEmployee->setText("Редактировать");
  
  actionDeleteEmployee = new QAction(this);
  actionDeleteEmployee->setObjectName(QStringLiteral("actionDeleteEmployee"));
  icon.addFile(QStringLiteral(":/tree32/icons/Erase.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionDeleteEmployee->setIcon(icon);
  actionDeleteEmployee->setText("Удалить сотрудника"); 
  
  actionReloadEmployees = new QAction(this);
  actionReloadEmployees->setObjectName(QStringLiteral("actionReloadEmployees"));
  icon.addFile(QStringLiteral(":/tree32/icons/Refresh.bmp"), QSize(), QIcon::Normal, QIcon::Off);
  actionReloadEmployees->setIcon(icon);
  actionReloadEmployees->setText("Обновить");   

  actionVideoView = new QAction(this);
  actionVideoView->setObjectName(QStringLiteral("actionVideoView"));
  icon.addFile(QStringLiteral(":/tree32/icons/Eye.bmp"), QSize(), QIcon::Normal, QIcon::Off);
  actionVideoView->setIcon(icon);
  actionVideoView->setText("Просмотр видео");
  
  actionPlaySingleVideo = new QAction(this);
  actionPlaySingleVideo->setObjectName(QStringLiteral("actionPlaySingleVideo"));
  icon.addFile(QStringLiteral(":/tree32/icons/Eye.bmp"), QSize(), QIcon::Normal, QIcon::Off);
  actionPlaySingleVideo->setIcon(icon);
  actionPlaySingleVideo->setText("Просмотр видео");  
  
  actionPlaySingleRls = new QAction(this);
  actionPlaySingleRls->setObjectName(QStringLiteral("actionPlaySingleRls"));
  icon.addFile(QStringLiteral(":/tree32/icons/rls.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionPlaySingleRls->setIcon(icon);
  actionPlaySingleRls->setText("РЛС в реальном времени");  
  
  actionAlarms = new QAction(this);
  actionAlarms->setObjectName(QStringLiteral("actionAlarms"));
  icon.addFile(QStringLiteral(":/tree32/icons/Warning.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionAlarms->setIcon(icon);
  actionAlarms->setText("Тревоги и оповещения");
  
  actionArchVideo = new QAction(this);
  actionArchVideo->setObjectName(QStringLiteral("actionArchVideo"));
  icon.addFile(QStringLiteral(":/tree32/icons/videocam.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionArchVideo->setIcon(icon);
  actionArchVideo->setText("Видео");
  
  actionArchRls = new QAction(this);
  actionArchRls->setObjectName(QStringLiteral("actionArchRls"));
  icon.addFile(QStringLiteral(":/tree32/icons/rls.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionArchRls->setIcon(icon);
  actionArchRls->setText("РЛС");
  
  actionArchSCUD = new QAction(this);
  actionArchSCUD->setObjectName(QStringLiteral("actionArchSCUD"));
  icon.addFile(QStringLiteral(":/tree32/icons/Key_16.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionArchSCUD->setIcon(icon);
  actionArchSCUD->setText("СКУД");
  
  actionConfigArchVideo = new QAction(this);
  actionConfigArchVideo->setObjectName(QStringLiteral("actionConfigArchVideo"));
  icon.addFile(QStringLiteral(":/tree32/icons/Gears.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionConfigArchVideo->setIcon(icon);
  actionConfigArchVideo->setText("Настройки архивации");
  
  actionConfigArchRls = new QAction(this);
  actionConfigArchRls->setObjectName(QStringLiteral("actionConfigArchRls"));
  icon.addFile(QStringLiteral(":/tree32/icons/Gears.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionConfigArchRls->setIcon(icon);
  actionConfigArchRls->setText("Настройки архивации");
  
  actionConfigArchSCUD = new QAction(this);
  actionConfigArchSCUD->setObjectName(QStringLiteral("actionConfigArchSCUD"));
  icon.addFile(QStringLiteral(":/tree32/icons/Gears.ico"), QSize(), QIcon::Normal, QIcon::Off);
  actionConfigArchSCUD->setIcon(icon);
  actionConfigArchSCUD->setText("Настройки архивации");
  
  QMetaObject::connectSlotsByName(this);
  
  DRAG_INFO.isActive = false;
  DRAG_INFO.sourceClassName = "";
  DRAG_INFO.srcItemText = "";
  DRAG_INFO.srcItemType = -1;
  
}

SvTreeView::~SvTreeView()
{
  this->deleteLater();
}

void SvTreeView::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu* menu = new QMenu(this);
  
  switch (this->treeModel->itemFromIndex(this->currentIndex())->type())
  {
    case itDevices:
    {
      menu->insertAction(0, actionDevices);
      menu->addSeparator();
      menu->insertAction(0, actionNewDevice);
      menu->setTitle("Устройства");
      break;
    }
      
    case itDevice:
    {
      menu->insertAction(0, actionNewDevice);
      menu->insertAction(0, actionEditDevice);
      menu->insertAction(0, actionDeleteDevice);
      
      switch (this->treeModel->itemFromIndex(this->currentIndex())->parent()->type())
      {
        case itVideo:
          menu->addSeparator();
          menu->insertAction(0, actionPlaySingleVideo);
          menu->addSeparator();
          menu->insertAction(0, actionConfigArchVideo);
          break;
          
        case itRls:
          menu->addSeparator();
          menu->insertAction(0, actionPlaySingleRls);
          menu->addSeparator();
          menu->insertAction(0, actionConfigArchRls);
          break;
      }
      menu->setTitle("Устройства");
      break;
    }
      
    case itZones:
    {
      menu->insertAction(0, actionZones);
      menu->addSeparator();
      menu->insertAction(0, actionNewZone);
      menu->addSeparator();
      menu->insertAction(0, actionReloadZones);
      menu->setTitle("Зоны безопасности");
      break;
    }  
      
    case itZone:
    {
      menu->insertAction(0, actionNewZone);
      menu->insertAction(0, actionEditZone);
      menu->insertAction(0, actionDeleteZone);
      menu->addSeparator();
      menu->insertAction(0, actionReloadZones);
      menu->setTitle("Зоны безопасности");
      break;
    }       
      
    case itKeys:
    {
      menu->insertAction(0, actionNewSCUD);
      menu->addSeparator();
      menu->insertAction(0, actionReloadSCUDs);
      menu->addSeparator();
      menu->insertAction(0, actionConfigSCUDs);
      menu->setTitle("Ключи");
      break;
    }
      
    case itKey:
    {
      menu->insertAction(0, actionNewSCUD);
      menu->insertAction(0, actionEditSCUD);
      menu->addSeparator();
      menu->insertAction(0, actionReloadSCUDs);
      menu->setTitle("Ключи");
      break;
    } 
      
    case itVideoView:
    {
      menu->insertAction(0, actionVideoView);
      menu->setTitle("Видеонаблюдение");
      break;
    }
      
    case itEmployees:
    {
      menu->insertAction(0, actionNewEmployee);
      menu->addSeparator();
      menu->insertAction(0, actionReloadEmployees);
//      menu->addSeparator();
//      menu->insertAction(0, actionConfigSCUDs);
      menu->setTitle("Ключи");
      break;
    }
      
    case itEmployee:
    {
      menu->insertAction(0, actionNewEmployee);
      menu->insertAction(0, actionEditEmployee);
      menu->addSeparator();
      menu->insertAction(0, actionReloadEmployees);
      menu->setTitle("Ключи");
      break;
    }   
     
  }
  
  menu->exec(event->globalPos());
}

void SvTreeView::mouseDoubleClickEvent(QMouseEvent * event)
{
  switch (treeModel->itemFromIndex(this->selected())->type())
  {
    case itDevice:
    {
      if(event->modifiers().testFlag(Qt::ShiftModifier))
        on_actionEditDevice_triggered();
      break;
    }
      
    case itZone:
    {
      qDebug() << "SvTreeView::mouseDoubleClickEvent 1";
      if(event->modifiers().testFlag(Qt::ShiftModifier))
      {  qDebug() << "SvTreeView::mouseDoubleClickEvent 2";
        on_actionEditZone_triggered(); }
      else
        on_actionZones_triggered(treeModel->itemFromIndex(this->indexAt(event->localPos().toPoint()))->text());  
      break;
    }
      
    case itAlarms:
    {
//      on_actionAlarms_triggered();        
      break;
    }
      
    case itArchVideo:
    {
      on_actionArchVideo_triggered();
      break;
    }
      
    case itArchSCUD:
    {
      on_actionArchSCUD_triggered();
      break;
    }   
      
    case itArchRls:
    {
      on_actionArchRls_triggered();
      break;
    }      
  } 
  
  QTreeView::mouseDoubleClickEvent(event);
}

void SvTreeView::mousePressEvent(QMouseEvent *event)
{
  switch (treeModel->itemFromIndex(this->indexAt(event->localPos().toPoint()))->type())
  {
    case itDevice:
    {
//      on_actionEditDevice_triggered();
      break;
    }
      
    case itZone:
    {
      if(mdiWindow->findChild<QWidget*>(ZONES_SUBWINDOW_NAME))
        on_actionZones_triggered(treeModel->itemFromIndex(this->indexAt(event->localPos().toPoint()))->text());
      break;
    }
      
    case itAlarms:
    {
//      on_actionAlarms_triggered();        
      break;
    }
  } 

  QTreeView::mousePressEvent(event);

}

/** ********** устройства *************** **/
void SvTreeView::on_actionDevices_triggered()
{
  if(!mdiWindow) return;
  
  if(!mdiWindow->findChild<QWidget*>(DEVICES_SUBWINDOW_NAME))
  {
    DEV_WINDOW_UI = new SvDevicesWindow(mdiWindow,
                                        "Устройства");

    DEV_WINDOW_UI->bnAddDevice->setDefaultAction(actionNewDevice);
    DEV_WINDOW_UI->bnEditDevice->setDefaultAction(actionEditDevice);
    DEV_WINDOW_UI->bnDeleteDevice->setDefaultAction(actionDeleteDevice);  
    DEV_WINDOW_UI->show();
  }
  
  DEV_WINDOW_UI->setFocus();

}

void SvTreeView::on_actionNewDevice_triggered()
{
  DEV_UI = new SvDevice(this);
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvTreeView::on_actionEditDevice_triggered()
{
  DEV_UI = new SvDevice(this, this->treeModel->itemFromIndex(this->selected())->text(), SvDevice::smEdit);
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvTreeView::on_DEV_UI_closed()
{
  if(DEV_UI->result() == QDialog::Accepted)
  {
    loadDevices("", true);
  }
  DEV_UI->~SvDevice();
}

void SvTreeView::on_actionDeleteDevice_triggered()
{
  
}

void SvTreeView::on_actionConfigArchVideo_triggered()
{
  FF2F_SETTINGS_UI = new SvFFmpeg2FileSettings(this->treeModel->itemFromIndex(this->currentIndex())->data().toInt());
}


void SvTreeView::on_actionConfigArchRls_triggered()
{
  RLS2BIT_2F_SETTINGS_UI = new SvRls2bit2FileSettings(this->treeModel->itemFromIndex(this->currentIndex())->data().toInt());
}

void SvTreeView::on_actionConfigArchSCUD_triggered()
{
  
}


/** *************** зоны ****************** **/
void SvTreeView::on_actionZones_triggered(QString zoneName)
{
  if(!mdiWindow) return;

  if(!mdiWindow->findChild<QWidget*>(ZONES_SUBWINDOW_NAME))
  {
    ZONES_WINDOW_UI = new SvZonesWindow(mdiWindow,
                                          "Зоны безопасности");

    ZONES_WINDOW_UI->show();
    
  }
  else
    ZONES_WINDOW_UI->setFocus();
  
  if(zoneName != "") ZONES_WINDOW_UI->treeZoneChanged(zoneName);
  
}

void SvTreeView::on_actionNewZone_triggered()
{
  NEW_ZONE_UI = new SvNewZone(this, SvNewZone::smNew,
                              treeModel->itemFromIndex(this->currentIndex())->type() == itZones ? "" : treeModel->itemFromIndex(this->currentIndex())->text());
  connect(NEW_ZONE_UI, SIGNAL(accepted()), this, SLOT(on_NEW_ZONE_UI_closed()));
  connect(NEW_ZONE_UI, SIGNAL(rejected()), this, SLOT(on_NEW_ZONE_UI_closed()));
}


void SvTreeView::on_NEW_ZONE_UI_closed()
{
  if(NEW_ZONE_UI->result() == QDialog::Accepted)
  {
    QString s = NEW_ZONE_UI->t_zoneName;
    ZONE_UI = new SvZone(s, true, this);

    connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
    connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
  }
  
  NEW_ZONE_UI->~SvNewZone();
  NEW_ZONE_UI = NULL;
}

void SvTreeView::on_actionEditZone_triggered()
{
  NEW_ZONE_UI = new SvNewZone(this, SvNewZone::smEdit, treeModel->itemFromIndex(this->currentIndex())->text());
  connect(NEW_ZONE_UI, SIGNAL(accepted()), this, SLOT(on_NEW_ZONE_UI_closed()));
  connect(NEW_ZONE_UI, SIGNAL(rejected()), this, SLOT(on_NEW_ZONE_UI_closed()));
  
//  ZONE_UI = new SvZone(treeModel->itemFromIndex(this->currentIndex())->text(), true, this);
//  connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
//  connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
}

void SvTreeView::on_ZONE_UI_closed()
{
  if(ZONE_UI->result() == QDialog::Accepted)
  {
    loadZones(true);
  }
  
  ZONE_UI->~SvZone();
  ZONE_UI = NULL;
}

void SvTreeView::on_actionDeleteZone_triggered()
{

}

void SvTreeView::on_actionReloadZones_triggered()
{
  loadZones(true);
}

/** ********* просмотр видео ************ **/
void SvTreeView::on_actionVideoView_triggered()
{
  if(!mdiWindow) return;
  
  SvVideoViewWindow* viewVideo = new SvVideoViewWindow(mdiWindow,
                                                       "Просмотр видеокамер");
  viewVideo->show();
}

void SvTreeView::on_actionPlaySingleVideo_triggered()
{
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_DEVICES_WHERE_2)
                                .arg("id")
                                .arg(this->treeModel->itemFromIndex(this->currentIndex())->data().toInt()), q);
  
  //  qDebug() << this->treeModel->itemFromIndex(this->currentIndex())->data().toInt();
  if(!q->size()) return;                    
  q->first();
  
  SINGLEVIDEO_UI = new SvSingleVideoWindow(q->value("video_path").toString(),
                                           q->value("device_name").toString(),
                                           "Видео: " + q->value("video_path").toString(),
                                           800,
                                           600);
  q->finish();
  free(q);
}

void SvTreeView::on_actionPlaySingleRls_triggered()
{
  SINGLERLS_UI = new SvSingleRlsWindow(8000,
                                       this->treeModel->itemFromIndex(this->currentIndex())->text(),
                                       "Данные РЛС реального времени");
  
}
/** *********** тревоги *************** **/


/** *********** SCUD ****************** **/
void SvTreeView::on_actionNewSCUD_triggered()
{
  SCUD_UI = new SvSCUD(this);
  connect(SCUD_UI, SIGNAL(accepted()), this, SLOT(on_SCUD_UI_closed()));
  connect(SCUD_UI, SIGNAL(rejected()), this, SLOT(on_SCUD_UI_closed()));
}

void SvTreeView::on_actionEditSCUD_triggered()
{
//  SvKeyItem* f = new SvKeyItem("dd");
//  f->se
  SCUD_UI = new SvSCUD(this, SvSCUD::smEdit, treeModel->itemFromIndex(this->currentIndex())->data().toInt());
//  SCUD_UI = new SvSCUD(this, SvSCUD::smEdit, reinterpret_cast<SvKeyItem*>(treeModel->itemFromIndex(this->currentIndex()))->db_id);
  connect(SCUD_UI, SIGNAL(accepted()), this, SLOT(on_SCUD_UI_closed()));
  connect(SCUD_UI, SIGNAL(rejected()), this, SLOT(on_SCUD_UI_closed()));
}

void SvTreeView::on_SCUD_UI_closed()
{
  if(SCUD_UI->result() == QDialog::Accepted)
  {
    loadKeys(true);
  }
  SCUD_UI->~SvSCUD();
}

void SvTreeView::on_actionReloadSCUDs_triggered()
{
  loadKeys(true);
}

void SvTreeView::on_actionConfigSCUDs_triggered()
{
  /* определяем количество устройств СКУД */
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL("SELECT device_name, zone_name, ip, port FROM devices WHERE device_class='СКУД'", q);
  if(err.type() != QSqlError::NoError) return;
  
  int numDevices = q->size(); // value("count").toInt();
  if(!numDevices) return;
  
  QProgressDialog progress("Конфигурирование устойств СКУД", "Отмена", 0, numDevices, this);
  progress.setWindowModality(Qt::WindowModal);
  progress.show();
  
//  for (int i = 0; i < numDevices; i++)
  int pval = 0;
  while(q->next())
  {
    progress.setValue(pval);
    if(progress.wasCanceled()) break;
  
    QString device_name = q->value("device_name").toString();
    QString zone_name = q->value("zone_name").toString();
    QString ip = q->value("ip").toString();
    quint16 port = q->value("port").toInt();
    
    progress.setLabelText("Конфигурирование " + device_name);
    
    QSqlQuery* q1 = new QSqlQuery(PGDB->db);
    QSqlError err = PGDB->execSQL(QString("SELECT key_value FROM scuds WHERE (device_name='%1') or "
                                          "(device_name in (select device_name from devices where zone_name='%2'))")
                                  .arg(device_name)
                                  .arg(zone_name), q1);
    if(err.type() != QSqlError::NoError) return;  

    quint32 keys_count = q1->size();
    
    if(keys_count)
    { 
      void* m = malloc(keys_count * 3);
      memset(m, char(0), keys_count * 3);
      log_ns::log(m_Attention, QString("keys count=%1").arg(keys_count));
      int offset = 0;
      while (q1->next())
      {
        quint32 key = 0;
//        key = qrand();
        key = q1->value("key_value").toInt(); 
        
//        key = qrand();
//        key = qToBigEndian(/*(const uchar*)*/(key));
        log_ns::log(m_Attention, QString("device_name=%1  zone_name=%2  %3").arg(device_name).arg(zone_name).arg(key));
        memcpy(m + offset, &key, 3);
        offset += 3;
      }      
      
//      keys_count = 10;
      /* коннектимся к устройству и отправляем ключи. 
       * ключи разбиваем на пакеты по 1024 байта */
      SvTcpClient* tcp = new SvTcpClient(ip, port, true, true, false);
      if(tcp->connectToHost() != SOCKET_OK) return;
      log_ns::log(m_Attention, QString("keys_count=%1").arg(keys_count));
     
      for(int j = 0; j < (keys_count * 3) / 1014 + 1; j++)
      {
        if(progress.wasCanceled())
        {
//          if(tcp->connected) tcp->disconnectFromHost();
//          tcp->responseStatus = -1;
          break;
        }
        
        QByteArray* b = new QByteArray();
        b->append("KEYS");
        
        int keys_byte_cnt  = (keys_count - j * 338 > 338 ? 338 : keys_count - j * 338) * 3;
        log_ns::log(m_Attention, QString("keys_byte_cnt=%1").arg(keys_byte_cnt));
        b->append((const char*)(&keys_byte_cnt), sizeof(int));
        b->append((const char*)(m + j * 1014), keys_byte_cnt);
        
        tcp->sendData(b, 2000 , this);
        if(tcp->responseStatus != SOCKET_OK) break;
        
      }
            
      if(tcp->responseStatus != SOCKET_OK) break;
      
      tcp->sendData("END_KEYS", 2000, this);
      if(tcp->responseStatus == SOCKET_OK)
        tcp->disconnectFromHost();
      
    }
    pval++;
  }
  
  
  progress.setValue(numDevices);
}

/** *********** СОТРУДНИКИ ****************** **/
void SvTreeView::on_actionNewEmployee_triggered()
{
  EMPLOYEE_UI = new SvEmployee(this);
  connect(EMPLOYEE_UI, SIGNAL(accepted()), this, SLOT(on_EMPLOYEE_UI_closed()));
  connect(EMPLOYEE_UI, SIGNAL(rejected()), this, SLOT(on_EMPLOYEE_UI_closed()));
}

void SvTreeView::on_actionEditEmployee_triggered()
{
  EMPLOYEE_UI = new SvEmployee(this, SvEmployee::smEdit, treeModel->itemFromIndex(this->currentIndex())->data().toInt());
//  SCUD_UI = new SvSCUD(this, SvSCUD::smEdit, reinterpret_cast<SvKeyItem*>(treeModel->itemFromIndex(this->currentIndex()))->db_id);
  connect(EMPLOYEE_UI, SIGNAL(accepted()), this, SLOT(on_EMPLOYEE_UI_closed()));
  connect(EMPLOYEE_UI, SIGNAL(rejected()), this, SLOT(on_EMPLOYEE_UI_closed()));
}

void SvTreeView::on_EMPLOYEE_UI_closed()
{
  if(EMPLOYEE_UI->result() == QDialog::Accepted)
  {
    loadEmployees(true);
  }
  EMPLOYEE_UI->~SvEmployee();
}

void SvTreeView::on_actionReloadEmployees_triggered()
{
  loadEmployees(true);
}

/** ********* АРХИВЫ ************** */

void SvTreeView::on_actionArchVideo_triggered()
{
  if(!mdiWindow) return;

  if(!mdiWindow->findChild<QWidget*>(ARCHVIDEO_SUBWINDOW_NAME))
  {
    ARCHVIDEO_WINDOW_UI = new SvArchVideoView(mdiWindow, "Архив видео");
    ARCHVIDEO_WINDOW_UI->show();
  }
  else
    ARCHVIDEO_WINDOW_UI->setFocus();

}

void SvTreeView::on_actionArchRls_triggered()
{
  SELECT_RSL_ARCH_UI = new SvSelectRlsArchWindow();
//  connect(SELECT_RSL_ARCH_UI, SIGNAL(accepted()), this, SLOT(on_SELECT_RSL_ARCH_UI_closed()));
//  connect(SELECT_RSL_ARCH_UI, SIGNAL(rejected()), this, SLOT(on_SELECT_RSL_ARCH_UI_closed()));
}

void SvTreeView::on_SELECT_RSL_ARCH_UI_closed()
{
  if(SELECT_RSL_ARCH_UI->result() == QDialog::Accepted)
  {
//    SINGLERLS_UI = new SvSingleRlsWindow(SELECT_RSL_ARCH_UI->DataPort(),
//                                         SELECT_RSL_ARCH_UI->DeviceName(),
//                                         QString("Архив РЛС: %1 с %2 по %3")
//                                                 .arg(SELECT_RSL_ARCH_UI->DeviceName())
//                                                 .arg(SELECT_RSL_ARCH_UI->DateTimeBegin().toString("dd.MM.yyyy hh:mm:ss"))
//                                                 .arg(SELECT_RSL_ARCH_UI->DateTimeEnd().toString("dd.MM.yyyy hh:mm:ss")));
  
//    connect(SINGLERLS_UI, SIGNAL(destroyed()), this, SLOT(on_SINGLERLS_UI_closed()));
  }
  SELECT_RSL_ARCH_UI->~SvSelectRlsArchWindow();
}

void SvTreeView::on_SINGLERLS_UI_closed()
{
//  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
//  SvSettings *sett = new SvSettings(s, this);
 
//  SvTcpClient* client = new SvTcpClient(sett->readValue("SELECT_RLS_ARCH", "ServerIP", "169.254.1.2").toString(),
//                                        sett->readValue("SELECT_RLS_ARCH", "ServerPort", 35000).toInt());
//  if(client->connectToHost() != SOCKET_OK) return;
  
//  client->sendData("STOP:TRANSLATE", 2000);
//  client->disconnectFromHost();
}

void SvTreeView::on_actionArchSCUD_triggered()
{
  if(!mdiWindow) return;

  if(!mdiWindow->findChild<QWidget*>(ARCHSCUD_SUBWINDOW_NAME))
  {
    ARCHSCUD_WINDOW_UI = new SvArchSCUDView(mdiWindow, "Архив СКУД");
    ARCHSCUD_WINDOW_UI->show();
  }
  else
    ARCHSCUD_WINDOW_UI->setFocus();
}


/** ************* прочее ************** **/
void SvTreeView::on_actionVariables_triggered()
{
    
}

void SvTreeView::on_actionEmployeers_triggered()
{
    
}


/** **********************************************
 *           ЗАГРУЖАЕМ ЭЛЕМЕНТЫ ДЕРЕВА 
*********************************************** **/

void SvTreeView::loadDevices(QString zoneName, bool reload)
{
  if(!reload)
  {
    itemDevices =  new SvDevicesItem("Устройства");
    itemDevices->setIcon(QIcon(":/tree32/icons/cpu_16.ico"));
    
    rootNode->appendRow(itemDevices);
  }
  else
  {
    if(!itemDevices) return;
    while(itemDevices->rowCount()) itemDevices->removeRow(0);
  }

  itemVideo =  new SvVideoItem("Видеокамера");  
  itemVideo->setIcon(QIcon(":/tree32/icons/videocam.ico"));
  
  itemRls =  new SvRlsItem("РЛС"); 
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
  QFont fnt_inZone = QFont(this->font().family(), this->font().pixelSize(), QFont::Bold);
  QFont fnt_outZone = QFont(this->font().family(), this->font().pixelSize() - 1, QFont::Normal);
  
  QList<QStandardItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/bullet_blue.png");

  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(D_SELECT_DEV_DEVICES_LIST, q);
  if(err.type() != QSqlError::NoError) return;

//  QString s = qApp->applicationDirPath() + "/ini/devices.ini";
//  SvSettings* devsett = new SvSettings(s);
//  QStringList lst = devsett->appSettings->childGroups();

  while(q->next())
//  for(int i = 0; i < lst.count(); i++)
  {
    QString s_device_name = q->value("device_name").toString();
    QString s_class = q->value("device_class").toString();
    QString s_zoneName = q->value("zone_name").toString();
    
//    s = devsett->readValue(lst.at(i), "device", "").toString();
//    QString class_name = s.section('%', 2, 2);
//    QString device_name = s.section('%', 1, 1);
  
    itemsList.append(new SvDeviceItem(s_device_name));
    itemsList.last()->setIcon(ico);
    itemsList.last()->setData(q->value("id").toInt());
    
    if(zoneName == "") itemsList.last()->setFont(fnt_normal);
    else if(zoneName == s_zoneName /*s.section('%', 7, 7)*/)
    {
      itemsList.last()->setFont(fnt_inZone);     
      itemsList.last()->setForeground(QBrush(QColor(Qt::blue).dark()));
    }
    else
    {
      itemsList.last()->setFont(fnt_outZone);
      itemsList.last()->setForeground(QBrush(Qt::gray));
    }

    if(s_class == "Видеокамера")
      itemVideo->appendRow(itemsList.last());
    
    else if(s_class == "РЛС")
      itemRls->appendRow(itemsList.last());
    
    else if(s_class == "Контроллер")
      itemControllers->appendRow(itemsList.last());
      
    else if(s_class == "Датчик")
      itemSensors->appendRow(itemsList.last());
      
    else if(s_class == "СКУД")
      itemScud->appendRow(itemsList.last());
      
    else if(s_class == "Сервер видеоаналитики")
      itemVAnalitics->appendRow(itemsList.last());
      
    else if(s_class == "Сервер архивации")
      itemArchServer->appendRow(itemsList.last());

  }
  q->finish();
  free(q);
}

void SvTreeView::loadZones(bool reload)
{
  if(!reload)
  {
    itemZones =  new SvZonesItem("Зоны безопасности");     
    itemZones->setIcon(QIcon(":/tree32/icons/Shield_16.ico"));
    
    rootNode->appendRow(itemZones);
  }
  else
  {
    if(!itemZones) return;
    while(itemZones->rowCount()) itemZones->removeRow(0);
  }
  
  QSqlQuery* q = NULL;
  
//  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* zsett = new SvSettings(s);  
//  QStringList zlst = zsett->appSettings->childGroups();
  
  QList<QStandardItem*> itemsList;
  
  QIcon ico;

  itemsList.append(itemZones);
  QString currentParentName = "";

  while(itemsList.count())
  {
    QStandardItem* parentItem = itemsList.first();
    if(parentItem == itemZones) currentParentName = "";
    else currentParentName = parentItem->text();

    q = new QSqlQuery(PGDB->db);
    QSqlError err = PGDB->execSQL(D_SELECT_ZONES_LIST, q);
    if(err.type() != QSqlError::NoError) return;
    
    while(q->next())
//    for(int i = 0; i < zlst.count(); i++)
    {
      /* читаем имя родителя */
//      s = zsett->readValue(zlst.at(i), "zone", "").toString();

      QString parent_name = q->value("parent_zone_name").toString(); // s.section('%', 2, 2);
      QString img_path = q->value("img_path").toString();
      
      /* если имя родителя соответствует текущему,
       * то смотрим, есть ли уже такой элемент */
      if(parent_name == currentParentName)
      {
        /* имя зоны */
        QString zone_name = q->value("zone_name").toString(); //s.section('%', 1, 1);
  
        bool found = false;
        for(int j = 0; j < parentItem->rowCount(); j++)
          found = found | ((parentItem->child(j)->type() == itZone) & 
                           (zone_name == parentItem->child(j)->text()));
          
        if(!found)
        {
          SvZoneItem* item = new SvZoneItem(zone_name);
          ico = img_path /*s.section('%', 3, 3)*/ == "" ? QIcon(":/tree32/icons/zone.ico") : QIcon(":/tree32/icons/zone_plans.ico") ;
          item->setIcon(ico);
          item->setWhatsThis(QString("Зона %1").arg(zone_name));
          parentItem->appendRow(item);
          itemsList.append(item);
        }
      }
    }
    q->finish();
    itemsList.removeFirst();
  }
  
  free(q);
  
}


void SvTreeView::loadVars()
{
  itemVariables =  new QStandardItem("Переменные");        
  itemVariables->setIcon(QIcon(":/tree32/icons/struct.ico"));
  
  rootNode->appendRow(itemVariables);
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(D_SELECT_VARIABLES_LIST, q);
  if(err.type() != QSqlError::NoError) return;
  
//  QString s = QApplication::applicationDirPath() + "/ini/" + "vars.ini";
//  SvSettings* vsett = new SvSettings(s);
  
  QList<QStandardItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/bullet_blue.png");
  
//  QStringList lst = vsett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
  while(q->next())
  {
//    s = vsett->readValue(lst.at(i), "var", "").toString();
    QString var_name = q->value("var_name").toString(); // s.section('%', 1, 1);
    QString device_name = q->value("device_name").toString(); //s.section('%', 2, 2);
   
    itemsList.append(new SvVariableItem(QString("%1 (%2)").arg(var_name, device_name)));
    itemsList.last()->setIcon(ico);
    
    itemVariables->appendRow(itemsList.last());
    
  }
  q->finish();
  free(q);
}    

void SvTreeView::loadKeys(bool reload)
{
  if(!reload)
  {
    itemKeys =  new SvKeysItem("Ключи");        
    itemKeys->setIcon(QIcon(":/tree32/icons/Key_16.ico"));
    
    rootNode->appendRow(itemKeys);
  }
  else
  {
    if(!itemKeys) return;
    while(itemKeys->rowCount()) itemKeys->removeRow(0);
  }
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(D_SELECT_SCUDS_LIST, q);
  if(err.type() != QSqlError::NoError) return;

  QList<SvKeyItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/bullet_blue.png");
//  QIcon ico_key = QIcon(":/tree32/icons/User_key.ico");
  
  while(q->next())
  {
    QString key_value = q->value("key_value").toString();
    QString emp_name = q->value("employee_name").toString();
    QString emp_patronymic = q->value("employee_patronymic").toString();
    QString emp_surename = q->value("employee_surename").toString();
   
    QString itemText = emp_surename == "" ? key_value : QString("%1 (%2 %3. %4.)")
                                                                .arg(key_value)
                                                                .arg(emp_surename)
                                                                .arg(emp_name.at(0))
                                                                .arg(emp_patronymic.at(0));
    
    itemsList.append(new SvKeyItem(itemText));
    itemsList.last()->setIcon(ico);
    itemsList.last()->setData(q->value("id").toInt());
//    itemsList.last()->db_id = q->value("id").toInt();
    
    itemKeys->appendRow(itemsList.last());
  }
  q->finish();
  free(q);
}

void SvTreeView::loadEmployees(bool reload)
{
  if(!reload)
  {
    itemEmployees =  new SvEmployeesItem("Сотрудники");        
    itemEmployees->setIcon(QIcon(":/tree32/icons/Users.ico"));
    
    rootNode->appendRow(itemEmployees);
  }
  else
  {
    if(!itemEmployees) return;
    while(itemEmployees->rowCount()) itemEmployees->removeRow(0);
  }

  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(D_SELECT_EMPLOYEES_LIST, q);
  if(err.type() != QSqlError::NoError) return;

  QList<SvEmployeeItem*> itemsList;
  QIcon ico = QIcon(":/tree32/icons/User_1.ico");
  QIcon ico_key = QIcon(":/tree32/icons/User_key.ico");
  
  while(q->next())
  {
    QString emp_name = q->value("employee_name").toString();
    QString emp_patronymic = q->value("employee_patronymic").toString();
    QString emp_surename = q->value("employee_surename").toString();
    int key_value = q->value("key_value").isValid() ? q->value("key_value").toInt() : -1;
   
    itemsList.append(new SvEmployeeItem(QString("%1 %2. %3. (%4)")
                                        .arg(emp_surename)
                                        .arg(emp_name.at(0))
                                        .arg(emp_patronymic.at(0))
                                        .arg(q->value("employee_position").toString())));
    
    itemsList.last()->setData(q->value("id").toInt());
    if(key_value == -1) itemsList.last()->setIcon(ico);
    else itemsList.last()->setIcon(ico_key);
    
    itemEmployees->appendRow(itemsList.last());
  }
  q->finish();
  free(q);
}

void SvTreeView::loadView()
{
  itemView =   new QStandardItem("Просмотр");              
  itemView->setIcon(QIcon(":/tree32/icons/Eye.bmp"));
  
  itemVideoView =   new SvVideoViewItem("Видеокамеры");  
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
  itemArchiving =  new QStandardItem("Архив");         
  itemArchiving->setIcon(QIcon(":/tree32/icons/Database.ico"));
  
  itemArchVideo =  new SvArchVideoItem("Видео");              
  itemArchVideo->setIcon(QIcon(":/tree32/icons/videocam.ico"));
  
  itemArchRls =  new SvArchRlsItem("РЛС");              
  itemArchRls->setIcon(QIcon(":/tree32/icons/rls.ico"));
  
  itemArchSCUD =  new SvArchSCUDItem("СКУД");              
  itemArchSCUD->setIcon(QIcon(":/tree32/icons/Key_16.ico"));  
  
  rootNode->appendRow(itemArchiving);
  itemArchiving->appendRow(itemArchVideo);
  itemArchiving->appendRow(itemArchRls);
  itemArchiving->appendRow(itemArchSCUD);
  
}    
    
    
    
    
    
    
    
    
