#include "sv_zonedraw.h"
#include "./COMMON/sv_settings.h"
#include "sv_treeview.h"
#include "sv_zone.h"
#include "sv_treeview.h"
#include "./COMMON/sv_pgdb.h"
#include "../Panel/panel_tcp.h"
#include "./COMMON/sv_device.h"
#include "./sv_videoviewwindow.h"
#include "./sv_rls2bitwidget.h"

#include "./COMMON/sql_fields_defs.h"
#include "./COMMON/sql_select_defs.h"
#include "./COMMON/sql_create_defs.h"

using namespace sql_select_defs;
using namespace sql_create_defs;

//SvSettings* zd_sett;
//SvSettings* zzsett;
//SvSettings* dsett;
//SvSettings* zdd_sett;

extern SvZone* ZONE_UI;
extern SvPGDB* PGDB;
extern SvSingleVideoWindow* SINGLEVIDEO_UI;
extern SvSingleRlsWindow* SINGLERLS_UI;

#ifndef QT_NO_WHEELEVENT
void GraphicsView::wheelEvent(QWheelEvent *e)
{
    if (e->modifiers() & Qt::ControlModifier)
    {
        if (e->delta() > 0) view->zoomIn(6);
        else view->zoomOut(6);
        e->accept(); 
    }
    else { QGraphicsView::wheelEvent(e);  }
}
#endif

SvZoneDrawWidget::SvZoneDrawWidget(QWidget *parent,
                                   bool showSlider):
  scene(new QGraphicsScene)
{
  this->setParent(parent);
//  this->setGeometry(parent->geometry());
  
  graphicsView = new GraphicsView(this);
  graphicsView->setRenderHint(QPainter::Antialiasing, false);
  graphicsView->setDragMode(QGraphicsView::NoDrag); //RubberBandDrag);
  graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  QHBoxLayout* hlay = new QHBoxLayout(this);
  hlay->setSpacing(0);
  hlay->setObjectName(QStringLiteral("vlay"));
  
  QVBoxLayout* sliderLay = new QVBoxLayout();
  sliderLay->setSpacing(0);
  sliderLay->setObjectName(QStringLiteral("sliderLay"));
  
  if(showSlider)
  {
    zoomSlider = new QSlider;
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksRight);
    zoomSlider->setEnabled(false);
    sliderLay->addWidget(zoomSlider);
    hlay->addLayout(sliderLay);
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(setupMatrix()));
  }
  
  hlay->addWidget(graphicsView);
  
//  connect(this, SIGNAL())
    
}

void SvZoneDrawWidget::updateDraw(QSize size,
                                  QString zoneName,
                                  int alarmType)
{
  bool isChildZone;
  this->editable = false;
  
  int sliderPos = -1;
  
  /* 1. определяем, назначена ли карта выбранной зоне */
  QString pix_file_name = "";
  QByteArray pix_data;
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QString sql = QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + zoneName + "'");
  
  QSqlError err = PGDB->execSQL(sql, q);
  if(err.type() != QSqlError::NoError) return;
  q->first();

  QString parentZoneName = "";
  isChildZone = q->value("img_path").toString() == "";
  parentZoneName = q->value("parent_zone_name").toString();
  
  if(isChildZone & (parentZoneName == "")) return;
  
  /* 2. если карта назначена */
  if((parentZoneName == "") | (!isChildZone))
  {
    pix_file_name = q->value("img_path").toString();
  }
  else /* если карта не назначена */
  {
    /* 2.2 ищем родителя зоны и его карту */
    QSqlQuery* q2 = new QSqlQuery(PGDB->db);
    QString sql2 = QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + parentZoneName + "'");
    
    QSqlError err = PGDB->execSQL(sql2, q2);
    if(err.type() != QSqlError::NoError) return;
    
    q2->first();
    pix_file_name = q2->value("img_path").toString();
//    pix_data = q2->value("img_data").toByteArray();
    
    q2->finish();
    free(q2);
  }

  if((pix_file_name == "")/* | pix_data.isEmpty()*/) return;
  
  if(!q->value("scene_size").isNull())
    sliderPos = q->value("scene_size").toInt();

  /******************************************/
  
  zoomSlider->setEnabled(false);
  
  scene->clear();
  mapZones.clear();
  mapPoints.clear();
  mapDevices.clear();
  int zoneCount = 0;
  int deviceCount = 0;
//  currentPlanName = "";
  currentZoneName = "";
  currentZoneId = -1;
  currentZoneParentName = "";
  
  
  /* 2.1 и 2.3 загружаем и отрисовываем карту */
//  QPixmap* pix = new QPixmap;
  img = new QImage();
  currentPix = new QPixmap;
  if(!currentPix->load(pix_file_name)) // pix_file_name))
  {
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text =  scene->addText("Файл изображения не найден или имеет неизвестный формат"); //, QFont());
    text->setPos(100, 100);
    text->setDefaultTextColor(Qt::red);
    text->setScale(2);
    this->graphicsView->setScene(scene);
    scene->update();
    return;
  }
  
  img->load(pix_file_name);
//  currentPix = fromImage(*img);
  scene->addPixmap(*currentPix);
  scene->setSceneRect(0, 0, currentPix->width(), currentPix->height());
  zoomSlider->setEnabled(true);

  q->finish();
  free(q);
  q = new QSqlQuery(PGDB->db);
  err = PGDB->execSQL(D_SELECT_ZONES_LIST, q);
  
  /* 3. отрисовываем заданную зону. она будет иметь индекс 0  */
  q->first();
  do
//  for(int i = 0; i < zlst.count(); i++)
  {
    QString s_zone_name = q->value("zone_name").toString();
    QString s_parent_zone_name = q->value("parent_zone_name").toString();
    QString s_points = q->value("points").toString();
    
//    QString s = zzsett->readValue(zlst.at(i), "zone", "").toString();
    
    /* сложное условие для правильного отображения зон */
//    bool b = (parentZoneName == "") & ((s.section('%', 1, 1) == zoneName) | (s.section('%', 2, 2) == zoneName));
//    b =  b | ((parentZoneName != "")
//              & (isChildZone | editable ? ((s.section('%', 1, 1) == parentZoneName) & (s.section('%', 2, 2) == "")) 
//                                            | (s.section('%', 2, 2) == parentZoneName) 
//                                        : s.section('%', 2, 2) == zoneName));
    
    bool b;                                     
    b = (parentZoneName == "") & ((s_zone_name == zoneName) | (s_parent_zone_name == zoneName));
    b =  b | ((parentZoneName != "")
            & (isChildZone ? ((s_zone_name == parentZoneName) & (s_parent_zone_name == "")) 
                                          | (s_parent_zone_name == parentZoneName) 
                                      : (s_parent_zone_name == zoneName) /*| (s_zone_name == zoneName)*/));
//    b = (parentZoneName == "") & ((s.section('%', 1, 1) == zoneName) | (s.section('%', 2, 2) == zoneName));
//    b =  b | ((parentZoneName != "")
//            & (isChildZone /*| editable*/ ? ((s.section('%', 1, 1) == parentZoneName) & (s.section('%', 2, 2) == "")) 
//                                          | (s.section('%', 2, 2) == parentZoneName) 
//                                      : s.section('%', 2, 2) == zoneName));
    if(b)
    {
        QStringList point_lst = s_points.split('|'); // s.section('%', 4, 4).split('|');
        
        mapPoints.insert(zoneCount, new QList<QPointF>());
        
        if((point_lst.count() > 0) &  !(point_lst.count() % 2))
        {
          for(int j = 0; j < point_lst.count(); j+=2)
            mapPoints.value(zoneCount)->append(QPoint(point_lst.at(j).toFloat(), point_lst.at(j + 1).toFloat()));
        }
        
        mapZones.insert(zoneCount, new ZonePath(this,
                                                s_zone_name, //s.section('%', 1, 1),
                                                s_parent_zone_name, //s.section('%', 2, 2),
                                                zoneCount,
                                                &currentZoneId,
                                                &currentZoneName,
                                                &currentZoneParentName,
                                                true,
                                                mapPoints.value(zoneCount),
                                                s_zone_name /*s.section('%', 1, 1)*/ == zoneName,
                                                alarmType));
        
    
        scene->addItem(mapZones.value(zoneCount));
    
        if(s_zone_name /*s.section('%', 1, 1)*/ == zoneName)
        {
          currentZoneId = zoneCount;
          currentZoneName = zoneName;
          currentZoneParentName = parentZoneName;
        }
        zoneCount++;
    }
  } while(q->next());


    
  /* 5. если задана возможность редактирования, то отрисовываем узлы для заданной зоны */
  
//  if(editable & (mapPoints.count() > 0))
//  {
//    for(int i = 0; i < mapPoints.value(currentZoneId)->count(); i++)
//    {
//      ZoneNode* zn = new ZoneNode(i, currentZoneId, mapPoints.value(currentZoneId)); // p_list->at(i).x(), p_list->at(i).y());
//      scene->addItem(zn);
//    }
//  }

  /* 5. отрисовываем устройства для заданной зоны */
  q->finish();
  free(q);
  q = new QSqlQuery(PGDB->db);
  sql = QString(D_SELECT_FROM_DEVICES_WHERE_2).arg("zone_name").arg("'" + zoneName + "'");
  err = PGDB->execSQL(sql, q);
  if(err.type() != QSqlError::NoError) return;
  
//  q->first();
  
//  QString sd = QApplication::applicationDirPath() + "/ini/devices.ini";
//  SvSettings* zdd_sett = new SvSettings(sd);
//  QStringList lstd = zdd_sett->appSettings->childGroups();
  
  while(q->next())
  {
    int     s_id = q->value("id").toInt();
    QString s_device_name = q->value("device_name").toString();
    QString s_model = q->value("device_model").toString();
    QString s_class = q->value("device_class").toString();
    QString s_brand = q->value("device_brand").toString();
    QString s_ip = q->value("ip").toString();
    int     s_port = q->value("port").toInt();
    QString s_video_path = q->value("video_path").toString();
    float   s_pos_x = q->value("pos_x").toFloat();
    float   s_pos_y = q->value("pos_y").toFloat();
    QString s_zoneName = q->value("zone_name").toString();
    QString s_description = q->value("description").toString();
    
    int devType = -1;
//    if(zoneName == sd.section('%', 7, 7))
//    {
      if(s_class /*sd.section('%', 2, 2)*/ == "Видеокамера")
        devType = gtVideocamera;
      
      else if(s_class == "Контроллер")
        devType = gtController;
      
      else if(s_class == "РЛС")
        devType = gtRls;
      
      else if(s_class == "СКУД")
        devType = gtSCUD;

      mapDevices.insert(deviceCount, new GraphSimbolDevice(this,
                                                           false,
                                                           devType,
                                                           deviceCount,
                                                           currentZoneId,
                                                           currentZoneName,
                                                           s_device_name, //sd.section('%', 1, 1),
                                                           s_pos_x, //sd.section('%', 9, 9).toFloat(),
                                                           s_pos_y)); //sd.section('%', 10, 10).toFloat()));
          scene->addItem(mapDevices.value(deviceCount));
          deviceCount++;
      }
//    }
//  }

  q->finish();
  free(q);
  /****************************************************/
  
  this->graphicsView->setScene(scene);
//  scene->update();
  
  /* задаем масштаб, чтобы все помещалось в окне */
//  this->updateGeometry();
  
  if(sliderPos != -1)
  {
    this->zoomSlider->setValue(sliderPos);
    return;
  }
  
  qreal rw = qreal(currentPix->width() / qreal(size.width()));  //scene->sceneRect().width());
  qreal rh = qreal(currentPix->height()) / qreal(size.height()) ; // scene->sceneRect().height());
//  qDebug() << "this->width()=" << this->rect().width()
//           << "this->height()=" << this->rect().height() 
//           << "sceneRect().width() =" << scene->sceneRect().width() 
//           << "sceneRect().height()=" << scene->sceneRect().height() 
//           << "rw=" << rw << "rh=" << rh;

  qreal scl = rw > rh ? rw : rh;

//  scl = scl > 1 ? 1/scl : scl;
//  qDebug() << size.width() << size.height() << scl;
  zoomSlider->setValue(280 / scl);
 
  return;
  
  if((rw < 1) & (rh < 1))
    zoomSlider->setValue(350 - (this->rect().width() - (rw > rh ? rw : rh) * this->rect().width()));
  else if((rw < 1) & (rh > 1))
    zoomSlider->setValue(360 - (this->rect().width() - rw * this->rect().width()));
  else if((rw > 1) & (rh < 1))
    zoomSlider->setValue(360 - (this->rect().height() - rh * this->rect().height()));
    
}

void SvZoneDrawWidget::editZone(QSize size,
                                QString zoneName)
{
  bool isChildZone;
  this->editable = true;
  
  int sliderPos = -1;
  
  /* 1. определяем, назначена ли карта выбранной зоне */
  QString pix_file_name = "";
  QByteArray pix_data;
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QString sql = QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + zoneName + "'");
  
  QSqlError err = PGDB->execSQL(sql, q);
  if(err.type() != QSqlError::NoError) return;
  q->first();
  
//  QString zonesini = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* zzsett = new SvSettings(zonesini);
//  QStringList zlst = zzsett->appSettings->childGroups();
  QString parentZoneName = "";
  
//  for(int i = 0; i < zlst.count(); i++)
//  {
//    QString s = zzsett->readValue(zlst.at(i), "zone", "").toString();
//    if(s.section('%', 1, 1) == zoneName)
//    {
  
      isChildZone = q->value("img_path").toString() == "";
//      isChildZone = (s.section('%', 3, 3) == "");
      
      parentZoneName = q->value("parent_zone_name").toString();
//      parentZoneName = s.section('%', 2, 2);
      
      if(isChildZone & (parentZoneName == "")) return;
      
      /* 2. если карта назначена */
      if((parentZoneName == "") /*| (!isChildZone)*/)
      {
        pix_file_name = q->value("img_path").toString();
//        pix_data = q->value("img_data").toByteArray();
      }
//      if((parentZoneName == "") | !isChildZone) pix_file_name = s.section('%', 3, 3);
      
      else /* если карта не назначена */
      {
        /* 2.2 ищем родителя зоны и его карту */
        QSqlQuery* q2 = new QSqlQuery(PGDB->db);
        QString sql2 = QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + parentZoneName + "'");
        
        QSqlError err = PGDB->execSQL(sql2, q2);
        if(err.type() != QSqlError::NoError) return;
        
        q2->first();
        pix_file_name = q2->value("img_path").toString();
//        pix_data = q2->value("img_data").toByteArray();
        q2->finish();
        free(q2);
//        for(int j = 0; j < zlst.count(); j++)
//        {
//          QString ss = zzsett->readValue(zlst.at(j), "zone", "").toString();
//          if(ss.section('%', 1, 1) == parentZoneName)
//          {
//            pix_file_name = ss.section('%', 3, 3);
//            break;
//          }
//        }
      }

      if((pix_file_name == "")/* | pix_data.isEmpty()*/) return;
      
      if(!q->value("scene_size").isNull())
        sliderPos = q->value("scene_size").toInt();
      
//      if(s.section('%', 5, 5) != "") sliderPos = s.section('%', 5, 5).toInt();
      
//      break;
//    }
//  }

  /******************************************/
  
  zoomSlider->setEnabled(false);
  
  scene->clear();
  mapZones.clear();
  mapPoints.clear();
  mapDevices.clear();
  int zoneCount = 0;
  int deviceCount = 0;
//  currentPlanName = "";
  currentZoneName = "";
  currentZoneId = -1;
  currentZoneParentName = "";
  
  /* 2.1 и 2.3 загружаем и отрисовываем карту */
//  QPixmap* pix = new QPixmap;
  currentPix = new QPixmap;
  
  if(!currentPix->load(pix_file_name))
  {
    QGraphicsTextItem *text = new QGraphicsTextItem();
    text =  scene->addText("Файл изображения не найден или имеет неизвестный формат"); //, QFont());
    text->setPos(100, 100);
    text->setDefaultTextColor(Qt::red);
    text->setScale(2);
    this->graphicsView->setScene(scene);
    scene->update();
    return;
  }

  scene->addPixmap(*currentPix);
  scene->setSceneRect(0, 0, currentPix->width(), currentPix->height());
  zoomSlider->setEnabled(true);
  
  q->finish();
  free(q);
  q = new QSqlQuery(PGDB->db);
  err = PGDB->execSQL(D_SELECT_ZONES_LIST, q);
//  q->first();
  qDebug() << "editZone 1";
  /* 3. отрисовываем заданную зону. она будет иметь индекс 0  */
  while(q->next())
//  for(int i = 0; i < zlst.count(); i++)
  {
    QString s_zone_name = q->value("zone_name").toString();
    QString s_parent_zone_name = q->value("parent_zone_name").toString();
    QString s_points = q->value("points").toString();
    
//    QString s = zzsett->readValue(zlst.at(i), "zone", "").toString();
    
    /* сложное условие для правильного отображения зон */
    bool b;                                     
    b = s_zone_name == zoneName;
//    b = s.section('%', 1, 1) == zoneName;
    
    if(b)
    {
      QStringList point_lst = s_points.split('|'); // s.section('%', 4, 4).split('|');
      
      mapPoints.insert(zoneCount, new QList<QPointF>());
      
      if((point_lst.count() > 0) & !(point_lst.count() % 2))
      {
        for(int j = 0; j < point_lst.count(); j+=2)
          mapPoints.value(zoneCount)->append(QPoint(point_lst.at(j).toFloat(), point_lst.at(j + 1).toFloat()));
      }
      
      mapZones.insert(zoneCount, new ZonePath(this,
                                              s_zone_name, //s.section('%', 1, 1),
                                              s_parent_zone_name, //s.section('%', 2, 2),
                                              zoneCount,
                                              &currentZoneId,
                                              &currentZoneName,
                                              &currentZoneParentName,
                                              false,
                                              mapPoints.value(zoneCount),
                                              s_zone_name /*s.section('%', 1, 1)*/ == zoneName,
                                              0));
      
      scene->addItem(mapZones.value(zoneCount));
      
      if(s_zone_name /*s.section('%', 1, 1)*/ == zoneName)
      {
        currentZoneId = zoneCount;
        currentZoneName = zoneName;
        currentZoneParentName = parentZoneName;
      }
      zoneCount++;
    }
  }

  /* 5. если задана возможность редактирования, то отрисовываем узлы для заданной зоны */
  if(mapPoints.count() > 0)
  {
    for(int i = 0; i < mapPoints.value(currentZoneId)->count(); i++)
    {
      ZoneNode* zn = new ZoneNode(i, currentZoneId, mapPoints.value(currentZoneId)); // p_list->at(i).x(), p_list->at(i).y());
      scene->addItem(zn);
    }
  }

  /* 5. отрисовываем устройства для заданной зоны */
  q->finish();
  free(q);  
  q = new QSqlQuery(PGDB->db);
  sql = QString(D_SELECT_FROM_DEVICES_WHERE_2).arg("zone_name").arg("'" + zoneName + "'");
  err = PGDB->execSQL(sql, q);
  if(err.type() != QSqlError::NoError) return;
  
//  q->first();
  
//  QString sd = QApplication::applicationDirPath() + "/ini/devices.ini";
//  SvSettings* zdd_sett = new SvSettings(sd);
//  QStringList lstd = zdd_sett->appSettings->childGroups();

  while(q->next())
//  for(int i = 0; i < lstd.count(); i++)
  {
//    sd = zdd_sett->readValue(lstd.at(i), "device", "").toString();
    int     s_id = q->value("id").toInt();
    QString s_device_name = q->value("device_name").toString();
    QString s_model = q->value("device_model").toString();
    QString s_class = q->value("device_class").toString();
    QString s_brand = q->value("device_brand").toString();
    QString s_ip = q->value("ip").toString();
    int     s_port = q->value("port").toInt();
    QString s_video_path = q->value("video_path").toString();
    float   s_pos_x = q->value("pos_x").toFloat();
    float   s_pos_y = q->value("pos_y").toFloat();
    QString s_zoneName = q->value("zoneName").toString();
    QString s_description = q->value("description").toString();
    
    int devType = -1;
//    if(zoneName == sd.section('%', 7, 7))
//    {
      if(s_class /*sd.section('%', 2, 2)*/ == "Видеокамера")
        devType = gtVideocamera;
      
      else if(s_class == "Контроллер")
        devType = gtController;
      
      else if(s_class == "РЛС")
        devType = gtRls;
      
      else if(s_class == "СКУД")
        devType = gtSCUD;

      mapDevices.insert(deviceCount, new GraphSimbolDevice(this,
                                                           true,
                                                           devType,
                                                           deviceCount,
                                                           currentZoneId,
                                                           currentZoneName,
                                                           s_device_name, //sd.section('%', 1, 1),
                                                           s_pos_x, //sd.section('%', 9, 9).toFloat(),
                                                           s_pos_y)); //sd.section('%', 10, 10).toFloat()));
          scene->addItem(mapDevices.value(deviceCount));
          deviceCount++;
    }
//  }
  q->finish();
  free(q);

  /****************************************************/

  this->graphicsView->setScene(scene);
//  scene->update();
  
  /* задаем масштаб, чтобы все помещалосьв окне */
//  this->updateGeometry();
  if(sliderPos != -1)
  {
    this->zoomSlider->setValue(sliderPos);
    return;
  }
  
  qreal rw = qreal(currentPix->width() / qreal(size.width()));  //scene->sceneRect().width());
  qreal rh = qreal(currentPix->height()) / qreal(size.height()) ; // scene->sceneRect().height());
//  qDebug() << "this->width()=" << this->rect().width()
//           << "this->height()=" << this->rect().height() 
//           << "sceneRect().width() =" << scene->sceneRect().width() 
//           << "sceneRect().height()=" << scene->sceneRect().height() 
//           << "rw=" << rw << "rh=" << rh;

  qreal scl = rw > rh ? rw : rh;

//  scl = scl > 1 ? 1/scl : scl;
//  qDebug() << size.width() << size.height() << scl;
  zoomSlider->setValue(280 / scl);

  return;
  
  if((rw < 1) & (rh < 1))
    zoomSlider->setValue(350 - (this->rect().width() - (rw > rh ? rw : rh) * this->rect().width()));
  else if((rw < 1) & (rh > 1))
    zoomSlider->setValue(360 - (this->rect().width() - rw * this->rect().width()));
  else if((rw > 1) & (rh < 1))
    zoomSlider->setValue(360 - (this->rect().height() - rh * this->rect().height()));
    
}

SvZoneDrawWidget::~SvZoneDrawWidget()
{
  foreach (QGraphicsItem* var, scene->items())
  {
    if(var->type() == gtZone)
    {
      if(((ZonePath*)(var))->zcthr != NULL)
      {
//      qDebug() << "(ZonePath*)(var))->zcthr->isFinished()";
        ((ZonePath*)(var))->zcthr->stop();
        while(!((ZonePath*)(var))->zcthr->isFinished()) QApplication::processEvents();
        free(((ZonePath*)(var))->zcthr);
      }
    }
  }
  qDebug() << "SvZoneDrawWidget::~SvZoneDrawWidget 1";
  this->deleteLater();
}

bool SvZoneDrawWidget::saveCurrentZone()
{
  if(currentZoneName == "") return false;
  
  QList<QPointF>* p_list = mapPoints.value(currentZoneId);
  
  QString vals = "";
  for(int i = 0; i < p_list->count(); i++)
    vals += (i==0 ? "" : "|") + QString("%1|%2").arg(p_list->at(i).x()).arg(p_list->at(i).y());
  
  QSqlError err = PGDB->execSQL(QString(D_UPDATE_ZONE_POINTS).arg(vals)
                                                             .arg(zoomSlider->value())
                                                             .arg(currentZoneName));
  if(err.type() != QSqlError::NoError) return false;

//  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* zzsett = new SvSettings(s, QSettings::IniFormat);
  
//  QStringList lst = zzsett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
//  {
//    s = zzsett->readValue(lst.at(i), "zone", "").toString();
    
//    /* ищем точное соответсвие имени зоны и записываем текущие данные о точках*/
//    if(s.section('%', 1, 1) == currentZoneName)
//    {
//      zzsett->writeValue(lst.at(i), "zone", QString("\%%1\%%2\%%3\%%4\%%5\%")
//                                                           .arg(currentZoneName)
//                                                           .arg(currentZoneParentName)
//                                                           .arg(s.section('%', 3, 3))
//                                                           .arg(vals)
//                                                           .arg(zoomSlider->value()));
//      break;
//    }
//  }
  
  /** сохраняем устройства **/
//  s = QApplication::applicationDirPath() + "/ini/devices.ini";
//  SvSettings* dsett = new SvSettings(s);
//  lst.clear();
//  lst = dsett->appSettings->childGroups();
  foreach (QGraphicsItem* item, mapDevices.values())
  {
    if(item->type() == gtDevice)
    {
      QString device_name = reinterpret_cast<GraphSimbolDevice*>(item)->device_name;
      QString zone_name = reinterpret_cast<GraphSimbolDevice*>(item)->zone_name;
      float x = reinterpret_cast<GraphSimbolDevice*>(item)->x();
      float y = reinterpret_cast<GraphSimbolDevice*>(item)->y();
      
      err = PGDB->execSQL(QString(D_UPDATE_DEVICE_POSITION).arg(x)
                                                           .arg(y)
                                                           .arg(device_name)
                                                           .arg(zone_name));
      
//      for(int i = 0; i < lst.count(); i++)
//      {
//        s = dsett->readValue(lst.at(i), "device", "").toString();
////        qDebug() << s << '\n' << reinterpret_cast<GraphSimbolDevice*>(item)->device_name << reinterpret_cast<GraphSimbolDevice*>(item)->zone_name;
//        if((s.section('%', 1, 1) == reinterpret_cast<GraphSimbolDevice*>(item)->device_name) &
//           (s.section('%', 7, 7) == reinterpret_cast<GraphSimbolDevice*>(item)->zone_name))
//        {
//          QString str = "%";// QString("\%%1\%%2\%%3\%%4\%%5\%%6\%%7\%%8\%%9\%%10\%");
//          for(int j = 1; j < 9; j++) str = str + s.section('%', j, j) + "%";
              
//          str += QString("%1\%%2\%").arg(reinterpret_cast<GraphSimbolDevice*>(item)->x()).arg(reinterpret_cast<GraphSimbolDevice*>(item)->y());
//          dsett->writeValue(lst.at(i), "device", str);
//          break;
//        }
//      }
    }
  }

  return true;
}

void SvZoneDrawWidget::makeZoneFullName()
{
  
}

void SvZoneDrawWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
//  if(contextMenuEvent->widget())
}

void SvZoneDrawWidget::mousePressEvent(QMouseEvent * event)
{
  if(event->modifiers().testFlag(Qt::ShiftModifier) & this->editable)
  {
//    qDebug() << event->localPos().x() << event->pos().x() << event->pos().rx() << event->x();
    
//    qDebug() << scene->sceneRect().width() - event->localPos().x() << event->pos().x() << event->pos().rx() << event->x();
//    QMatrix mat = this->graphicsView->matrix();
//    mat.translate()
//    float dx = graphicsView->matrix().m11();
//    float gw = graphicsView->width();
//    float pw = currentPix->width();
//    float lpos = event->localPos().x();
//    float lb = lpos - (pw - gw) / 2;
    
//    float pos = (pw / gw) * lpos /*+ */ - 35; // lpos - (gw - pw * dx) / 2;
//    qDebug() << "lb="<< lb << "gw=" << gw << "pw=" << pw << "lpos=" << lpos << "dx=" << dx 
//             << "(gw - pw * dx) / 2=" << (gw - pw * dx) / 2 << "pos=" << pos;
    newNode(currentZoneId, event->localPos().x(), event->localPos().y());
  }
  else QWidget::mousePressEvent(event);
}

void SvZoneDrawWidget::newNode(int zoneId, float x, float y)
{
  mapPoints.value(zoneId)->append(QPointF(x, y));
  
  ZoneNode* zn = new ZoneNode(mapPoints.value(zoneId)->count() - 1, zoneId, mapPoints.value(zoneId));
  scene->addItem(zn);
  
  mapZones.value(zoneId)->update();
  scene->update();
}

void SvZoneDrawWidget::zoomIn(int level)
{
  zoomSlider->setValue(zoomSlider->value() + level);
}

void SvZoneDrawWidget::zoomOut(int level)
{
  zoomSlider->setValue(zoomSlider->value() - level);
}

void SvZoneDrawWidget::setupMatrix(qreal scaleXY)
{
  qreal scale; 
  if(scaleXY) scale = scaleXY;
  else scale= qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

  QMatrix matrix;
  matrix.scale(scale, scale);
//  matrix.rotate(rotateSlider->value());

  graphicsView->setMatrix(matrix);
}

void SvZoneDrawWidget::runRLS(float x, float y)
{
  this->x = x;
  this->y = y;
  
  
  
  img_resolution = currentPix->width() < currentPix->height() ? currentPix->width() : currentPix->height();
  draw_points_per_line = 1024;
  
  img_rls = new QImage(img_resolution, img_resolution, QImage::Format_RGB888);
//  qDebug() << x << y;
//  return;
  for(int xx = 0; xx < img_resolution; xx++)
  {
    for(int yy = 0; yy < img_resolution; yy++)
    {
      img_rls->setPixel(xx, yy, img->pixel(xx, yy));
    }
  }

  wdg = new QWidget();
  wdg->resize(img_resolution, img_resolution);
  
  vlay = new QVBoxLayout(wdg);
  
  lbl = new QLabel(wdg);
  lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  lbl->setVisible(true);
  QPixmap p = QPixmap();
//  p.load("D:/c++/MKIS/demo_1/plans/of_sx.bmp", "BMP");
  p = QPixmap::fromImage(*img_rls);
  lbl->setPixmap(p);
//  lbl->setText("asfsdfasdfasdfgafsg");
  
  vlay->addWidget(lbl);
//  lbl->resize(100, 100);
  
  QGraphicsProxyWidget* pwdg = scene->addWidget(wdg);
  pwdg->setVisible(true);
  pwdg->setZValue(10); 
  
  /** убедились, что кусок картинки вырезается с нужными размерами **/
  
  
//  wdg->show();
  
//  rlswdg = new SvRls2BitWidget(8000, "RLS",
//                               img_resolution,
//                               img_resolution,
//                               img_resolution,
//                               draw_points_per_line,
//                               img_rls);
////  rlswdg->show();
  
//  QGraphicsProxyWidget* pwdg = scene->addWidget(rlswdg);
//  pwdg->setPos(x - float(img_resolution / 2), y - float(img_resolution / 2));
//  pwdg->setVisible(true);
  
  
//  rlswdg = new QWidget(this);
//  rlswdg->resize(img_resolution, img_resolution);
//  rlswdg->pa
  
//  _buffer = malloc(AZIMUTHS_COUNT * 1024);
//  memset(_buffer, char(0), AZIMUTHS_COUNT * 1024);
  
//  angle = double(2 * M_PI) / double(AZIMUTHS_COUNT);

//  timer.setInterval(30);
//  timer.setSingleShot(false);
//  connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
//  timer.start();
  
//  rls = new SvRlsDataBuffering(_buffer, 8000, this);
//  connect(rls, QThread::finished, rls, &QObject::deleteLater);
//  connect(rls, SIGNAL(lineUpdated(int)), this, SLOT(drawLine(int)));
//  rls->start();

}

void SvZoneDrawWidget::paintEvent(QPaintEvent *event)
{

}

//void SvZoneDrawWidget::drawLine(int lineNum)
//{
//  void* d;
//  d = _buffer + lineNum * 1024;
  
//  // угол 
//  double a = double(0.5 * M_PI) + angle * double(lineNum);
  
//  // угол для индикатора
//  double ind1 = double(0.5 * M_PI) + angle * double(lineNum + 1);
  
//  for(int i = 0; i < draw_points_per_line; i++)
//  {
//    int x = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * cos(a);
//    int y = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * sin(a);
    
//    if((x < currentPix->width()) & (y < currentPix->height()))
//    {
//      quint8* v = (quint8*)(d + i);
//      if(*v < 0x55) currentPix.setPixel(x, y, qRgb(3, 98, 155));
//      else if(*v < 0xAA) img.setPixel(x, y, qRgb(255, 255, 50));
//      else if(*v < 0xFF) img.setPixel(x, y, qRgb(255, 255, 150));
//      else img.setPixel(x, y, qRgb(255, 255, 0));
      
//      // индикатор
//      x = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * cos(ind1);
//      y = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * sin(ind1);
//      img.setPixel(x, y, qRgb(255, 100, 30));
//    }
       
//  }
//}

/************************************************/

ZoneNode::ZoneNode(int id, int zone_id, QList<QPointF> *p_list)
{
  
  this->id = id;
  this->zone_id = zone_id;
  this->p_list = p_list;
  this->setPos(p_list->at(id));
  
  brushColor = Qt::yellow;
  penColor = Qt::blue;
  
  setFlags(ItemIsMovable);   //ItemIsSelectable | 
  setAcceptHoverEvents(true);
  
  QIcon ico = QIcon(":/editors/icons/Close.ico");
  removeAction = new QAction(ico, QString("Удалить"), 0);

//  QObject::connect(removeAction, removeAction->triggered(), this, delete(this));
}

ZoneNode::~ZoneNode()
{
  p_list->removeAt(id);
  for(int i = 0; i < this->scene()->items().count(); i++)
  {
    if(this->scene()->items().at(i)->type() == UserType + 1)
    {
      ZoneNode* zn = qgraphicsitem_cast<ZoneNode*>(this->scene()->items().at(i));
      if(zn->id > id) zn->id--;      
    }
  }
  this->scene()->update();
  this->scene()->removeItem(this); /** ураааа, заработало! **/
}

void ZoneNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

//  QColor fillColor = (option->state & QStyle::State_Selected) ? brushColor.dark(150) : brushColor;
  QColor fillColor = option->state & QStyle::State_MouseOver ? Qt::red : brushColor;// fillColor = fillColor.light(125);
  painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
  painter->setPen(QPen(penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(-4, -4, 8, 8);
  painter->drawText(-8, -8, QString("%1").arg(id));
}

QRectF ZoneNode::boundingRect() const
{
  return QRectF(-4, -4, 8, 8); /**  !!! **/
}

void ZoneNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mousePressEvent(event);
  update();
}

void ZoneNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//  qDebug() << "x=" << event->scenePos().x() << "y=" << event->scenePos().y();
  p_list->replace(id, event->scenePos());
  QGraphicsItem::mouseMoveEvent(event);
  this->scene()->update();
}

void ZoneNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  update();
}

void ZoneNode::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
  QMenu menu;
  menu.addAction(removeAction);
  if(removeAction == menu.exec(event->screenPos()))
  {
    this->~ZoneNode();
  }
}

QPainterPath ZoneNode::shape() const
{
    QPainterPath path;
    path.addRect(-4, -4, 8, 8); /**  !!! **/
    return path;
}

/***********************************************************/

ZonePath::ZonePath(SvZoneDrawWidget *parent,
                   QString zone_name,
                   QString zone_parent_name,
                   int zone_id,
                   int* currentZoneId,
                   QString* currentZoneName,
                   QString *currentZoneParentName,
                   bool doFeedback,
                   QList<QPointF> *points_list,
                   bool isSelected,
                   int alarmType)
{
  this->parent = parent;
  this->p_list = points_list;
  this->zone_name = zone_name;
  this->zone_parent_name = zone_parent_name;
  this->zone_id = zone_id;
  this->currentZoneId = currentZoneId;
  this->currentZoneName = currentZoneName;
  this->currentZoneParentName = currentZoneParentName;
  this->doFeedback = doFeedback;
//  this->currentPlanName = currentPlanName;
  this->setSelected(isSelected);
  
  switch (alarmType) {
    case 0:
    {
      brushColor = QColor(0, 0, 255, 80); //.darker(10);
      penColor = Qt::blue;
      break;
    } 
    
    case 1: // тревога
    {
      brushColor = QColor(255, 0, 0, 80);
      penColor = Qt::red;
      zcthr = new ZoneColorThread(300, this);
      zcthr->start();
      break;
    }
      
    default: // оповещение
    {
      brushColor = QColor(255, 240, 10, 80);
      penColor = Qt::yellow;
      zcthr = new ZoneColorThread(300, this);
      zcthr->start();
      break;
    }
  }
  
  setFlags(ItemIsFocusable | ItemIsSelectable);   //ItemIsSelectable |ItemIsMovable
  setAcceptHoverEvents(true);
  setAcceptDrops(true);

}

//ZonePath::~ZonePath()
//{
//  if(zcthr) zcthr->stop();
////  zcthr->quit();
//}

void ZonePath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);
//  if(p_list->count() == 0) qDebug() <<  "cnt = 0";
//  else  qDebug() << p_list->count();
  
  if(p_list->count() < 2) return;

  QColor fillColor = option->state & QStyle::State_MouseOver ? brushColor.darker() : brushColor;
         fillColor = option->state & QStyle::State_Selected ? QColor(255, 0, 0, 80) : fillColor;
         
  QColor penc = option->state & QStyle::State_MouseOver ? Qt::blue : penColor;
         penc = option->state & QStyle::State_Selected  ? Qt::red  : penc;
  
  int penWidth = ((option->state & QStyle::State_MouseOver) | (option->state & QStyle::State_Selected)) ? 2 : 1;
  
  painter->setPen(QPen(penc, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->setBrush( QBrush(fillColor/*, Qt::DiagCrossPattern*/));

//  painter->drawRect(0, 0, 100, 100);
  QPainterPath p;
//  p.setFillRule(Qt::OddEvenFill);
  p.moveTo(p_list->at(0).x(), p_list->at(0).y());
  for(int i = 1; i < p_list->count(); i++)
    p.lineTo(p_list->at(i));
  p.closeSubpath();
  
  painter->drawPath(p);
  
  painter->setPen(QPen(penColor, 1, Qt::SolidLine));//, Qt::RoundCap, Qt::RoundJoin));
  painter->drawText(p_list->at(0).x() + 10, p_list->at(0).y() + 30, zone_name);
}

QRectF ZonePath::boundingRect() const
{
  if(p_list->count() < 2) return QRectF(0, 0, 0, 0);
  
  // определяем границы нашей фигуры
  float minX = 3.4E+38;
  float minY = 3.4E+38;
  float maxX = 3.4E-38;
  float maxY = 3.4E-38;
  
  for(int i = 0; i < p_list->count(); i++)
  {
    if(p_list->at(i).x() > maxX) maxX = p_list->at(i).x();
    if(p_list->at(i).x() < minX) minX = p_list->at(i).x();
    
    if(p_list->at(i).y() > maxY) maxY = p_list->at(i).y();
    if(p_list->at(i).y() < minY) minY = p_list->at(i).y();
  }
  return QRectF(minX, minY, maxX - minX, maxY - minY);
}

QPainterPath ZonePath::shape() const
{
  QPainterPath p;
  if(p_list->count() < 2) return p;
  
  p.moveTo(p_list->at(0).x(), p_list->at(0).y());
  for(int i = 1; i < p_list->count(); i++)
    p.lineTo(p_list->at(i));
  p.closeSubpath();
  return p;
}

void ZonePath::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if(!doFeedback) QGraphicsPathItem::mousePressEvent(event);
  else
  {
    *currentZoneId = zone_id;
    *currentZoneName = zone_name;
    *currentZoneParentName = zone_parent_name;
    parent->_zoneClicked(event, zone_id, zone_name);
  }
}

void ZonePath::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  if(!doFeedback) QGraphicsPathItem::mouseDoubleClickEvent(event);
  else
  {
    *currentZoneId = zone_id;
    *currentZoneName = zone_name;
    *currentZoneParentName = zone_parent_name;
    parent->_zoneDoubleClicked(event, zone_id, zone_name);
  }
}

void ZonePath::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
//  event->source()
  qDebug() << int(event->type());
//  qDebug() << event->mimeData()->formats().count();
//  for(int i = 0; i < event->mimeData()->formats().count(); i++)  //hasFormat( hasUrls())
//    qDebug() << event->mimeData()->formats().at(i) ; // text();
}

void ZonePath::dropEvent(QGraphicsSceneDragDropEvent *event)
{
  qDebug() << event->mimeData()->text();
}

/** ***************************************************** **/
/** ********************** devices ********************** **/
/** ***************************************************** **/


GraphSimbolDevice::GraphSimbolDevice(SvZoneDrawWidget *parent,
                                     bool allowEdit,
                                     int device_type,
                                     int id,
                                     int zone_id,
                                     QString zone_name,
                                     QString device_name,
                                     float X,
                                     float Y)
{
  this->parent = parent;
  this->id = id;
  this->device_type = device_type;
  this->zone_id = zone_id;
  this->position = QPointF(X, Y);
  this->setPos(position);
  this->device_name = device_name;
  this->isEditable = allowEdit;
  this->zone_name = zone_name;
  
  switch (device_type) {
    case gtVideocamera:
    {
      this->setToolTip(QString("Видеокамера\n%1\nX=%2\nY=%3").arg(device_name).arg(X).arg(Y));
      brushColor = Qt::gray;
      penColor = Qt::black;
      break;
    }
      
    case gtRls:
    {
      this->setToolTip(QString("РЛС\n%1\nX=%2\nY=%3").arg(device_name).arg(X).arg(Y));
      brushColor = Qt::green;
      penColor = Qt::black;
      break;
    }
      
    case gtController:
    {
      this->setToolTip(QString("Контроллер\n%1\nX=%2\nY=%3").arg(device_name).arg(X).arg(Y));
      brushColor = Qt::yellow;
      penColor = Qt::black;
      break;      
    }
      
    case gtSCUD:
    {
      this->setToolTip(QString("СКУД\n%1\nX=%2\nY=%3").arg(device_name).arg(X).arg(Y));
      brushColor = Qt::magenta;
      penColor = Qt::black;
      break;      
    }      
  }
 
  if(isEditable) setFlags(ItemIsMovable | ItemIsSelectable);
  else setFlags(ItemIsSelectable);
  
  setAcceptHoverEvents(true);
  
  QIcon ico = QIcon(":/editors/icons/Close.ico");
  removeAction = new QAction(ico, QString("Удалить"), 0);
   
  QIcon ico_1 = QIcon(":/tree32/icons/Gears.ico");
  editDeviceAction = new QAction(ico_1, QString("Редактировать устройство"), 0);
  
  QIcon ico_2 = QIcon(":/tree32/icons/Eye.bmp");
  playVideoAction = new QAction(ico_2, QString("Просмотр"), 0); 
  
  QIcon ico_3 = QIcon(":/tree32/icons/rls.ico");
  playRLSAction = new QAction(ico_3, QString("Просмотр"), 0); 
  
  QIcon ico_4 = QIcon(":/tree32/icons/rls.ico");
  playRLSOnMapAction = new QAction(ico_4, QString("Отобразить с наложением"), 0);   
  
  
  
//  QObject::connect(removeAction, removeAction->triggered(), this, delete(this));
}

GraphSimbolDevice::~GraphSimbolDevice()
{
//  p_list->removeAt(id);
//  for(int i = 0; i < this->scene()->items().count(); i++)
//  {
//    if(this->scene()->items().at(i)->type() == UserType + 1)
//    {
//      ZoneNode* zn = qgraphicsitem_cast<ZoneNode*>(this->scene()->items().at(i));
//      if(zn->id > id) zn->id--;      
//    }
//  }
//  this->scene()->update();
//  this->scene()->removeItem(this); /** ураааа, заработало! **/
}

void GraphSimbolDevice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

  QColor fillColor = option->state & (QStyle::State_MouseOver | QStyle::State_Selected) ? brushColor.light() : brushColor;// fillColor = fillColor.light(125);
  if(!led) painter->setBrush(QBrush(fillColor));
  else painter->setBrush(QBrush(Qt::red));
  QColor pen = option->state & (QStyle::State_MouseOver | QStyle::State_Selected) ? Qt::red : penColor;
  int penWidth = option->state & (QStyle::State_MouseOver | QStyle::State_Selected) ? 2 : 1;
  painter->setPen(QPen(pen, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));  
  
  switch (device_type)
  {
    case gtVideocamera:
    {
      static const QPointF points[8] =
      {
        QPointF(-10.0, -8.0),
        QPointF(10.0, -8.0),
        QPointF(10.0, -1.0),
        QPointF(18.0, -8.0),
        QPointF(18.0, 8.0),
        QPointF(10.0, 1.0),
        QPointF(10.0, 8.0),
        QPointF(-10.0, 8.0)        
      };
      painter->drawPolygon(points, 8);
      break;
    }
      
    case gtController:
    {
      painter->drawRect(- 10, - 10, 20, 20);
      break;
    }
      
    case gtRls:
    {
      static const QPointF points[3] =
      {
        QPointF(-10.0, 10.0),
        QPointF(0.0, -10.0),
        QPointF(10.0, 10.0)
      };
      painter->drawPolygon(points, 3);
      break;
    }
      
    case gtSCUD:
    {
      static const QPointF points[4] =
      {
        QPointF(-10.0, 0.0),
        QPointF(0.0, -10.0),
        QPointF(10.0, 0.0),
        QPointF(0.0, 10.0)
      };
      painter->drawPolygon(points, 4);
      break;
    }
  }
}

QRectF GraphSimbolDevice::boundingRect() const
{
  return QRectF(-10, -10, 20, 20); /**  !!! **/
}

void GraphSimbolDevice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//  qDebug() << "x=" << event->pos().x() << "y=" << event->pos().y();
//  x = event->pos().x();
//  y = event->pos().y();
  QGraphicsItem::mousePressEvent(event);
  update();
}

void GraphSimbolDevice::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//  QMessageBox::information(0, "dddd", "dsdsdsds", QMessageBox::Ok);
//  qDebug() << id;
  led = !led;
  panel = new Panel_tcp();
  panel->conectTCP(led, id + 1);
  
  
  QGraphicsItem::mouseDoubleClickEvent(event);
  update();
}

void GraphSimbolDevice::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//  qDebug() << "x=" << event->scenePos().x() << "y=" << event->scenePos().y();
//  p_list->replace(id, event->scenePos());
  QGraphicsItem::mouseMoveEvent(event);
  this->scene()->update();
}

void GraphSimbolDevice::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  update();
}

void GraphSimbolDevice::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
  QMenu menu;
  qDebug() << this->type();
  switch (this->device_type)
  {
    case gtVideocamera:
    {
      menu.addAction(playVideoAction);
      menu.addSeparator();
      break;
    }
      
    case gtRls:
    {
      menu.addAction(playRLSAction);
      menu.addAction(playRLSOnMapAction);
      menu.addSeparator();
      break;
    }
  }
  
  menu.addAction(editDeviceAction);
  menu.addSeparator();
  menu.addAction(removeAction);
  
  QAction *a = menu.exec(event->screenPos());
  if(removeAction == a)
  {
    this->~GraphSimbolDevice();
  }
  else if (editDeviceAction == a)
  {
    SvDevice* dd = new SvDevice(0, this->device_name, SvDevice::smEdit);
  }
  else if (playRLSAction == a)
  {
    qDebug() << "SINGLERLS_UI";
    SINGLERLS_UI = new SvSingleRlsWindow(8000, this->device_name,
                                         "Данные РЛС реального времени");
  }
  else if (playVideoAction == a)
  {
    QSqlQuery* q = new QSqlQuery(PGDB->db);
    QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_DEVICES_WHERE_2)
                                  .arg("device_name")
                                  .arg("'" + this->device_name + "'"), q);
    
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

  else if (playRLSOnMapAction == a)
  {
    parent->runRLS(this->position.x(), this->position.y());
    
  }
}

QPainterPath GraphSimbolDevice::shape() const
{
    QPainterPath path;
    path.addRect(-10, -10, 20, 20); /**  !!! **/
    return path;
}

//void GraphSimbolDevice::on_removeAction_triggered()
//{
  
//}

//void GraphSimbolDevice::on_editDeviceAction_triggered()
//{
  
//}

//void GraphSimbolDevice::on_playVideoAction_triggered()
//{
  
//}

//void GraphSimbolDevice::on_playRLSAction_triggered()
//{
  
//}
