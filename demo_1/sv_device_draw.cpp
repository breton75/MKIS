#include "sv_zonedraw.h"
#include "./COMMON/sv_settings.h"
#include "sv_treeview.h"

SvSettings* zd_sett;

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
                                   QString planName,
                                   QString zoneName,
                                   bool allowEdit,
                                   bool showSlider):
  scene(new QGraphicsScene)
//  pix(new QPixmap)
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
  
  if(planName == "") return;
  
//  updateDraw(planName, zoneName, allowEdit, points_list);
  
}

void SvZoneDrawWidget::updateDraw(QSize size,
                                  QString planName,
                                  QString zoneName,
                                  bool allowEdit,
                                  int alarmType)
{
  this->ediable = allowEdit;
  zoomSlider->setEnabled(false);
  
  QString pix_file_name = "";
  
  /******************************************/
 
  QString s = QApplication::applicationDirPath() + "/ini/plans.ini";
  zd_sett = new SvSettings(s);
  
  QStringList lst = zd_sett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    s = zd_sett->readValue(lst.at(i), "plan", "").toString();
    if(s.section('%', 1, 1) == planName)
    {
      pix_file_name = s.section('%', 3, 3);
      break;
    }
  }

  /******************************************/
  
  scene->clear();
  mapZone.clear();
  mapPoints.clear();
  int zoneCount = 0;
  currentPlanName = "";
  currentZoneName = "";
  currentZoneId = -1;
  
  QPixmap* pix = new QPixmap;
  
  if(!pix->load(pix_file_name))
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

  scene->addPixmap(*pix);
  zoomSlider->setEnabled(true);
  
  s = QApplication::applicationDirPath() + "/ini/zones.ini";
  zd_sett = new SvSettings(s);
 
  lst.clear();
  lst = zd_sett->appSettings->childGroups();

  /* ищем нужный план. если имя зоны задано,
   * то ищем точное соответсвие имени плана и зоны. при этом редактирование
   * возможно только если имя зоны задано. если же имя зоны не задано, 
   * то выводим все зоны относящиеся к данному плану в режиме просмотра */
  for(int i = 0; i < lst.count(); i++)
  {
    s = zd_sett->readValue(lst.at(i), "zone", "").toString();

    if((s.section('%', 2, 2) == planName) & 
       (zoneName == "" ? true : zoneName == s.section('%', 1, 1)))
    {
      QStringList point_lst = s.section('%', 3, 3).split('|');
                
      mapPoints.insert(zoneCount, new QList<QPointF>());
      for(int j = 0; j < point_lst.count(); j+=2)
        mapPoints.value(zoneCount)->append(QPoint(point_lst.at(j).toFloat(), point_lst.at(j + 1).toFloat()));
      
      mapZone.insert(zoneCount, new ZonePath(this,
                                             s.section('%', 1, 1),
                                             s.section('%', 2, 2),
                                             zoneCount,
                                             &currentZoneId,
                                             &currentZoneName,
                                             &currentPlanName,
                                             mapPoints.value(zoneCount),
                                             alarmType));
      scene->addItem(mapZone.value(zoneCount));
      
      if(ediable & (zoneName != ""))
      {
        for(int i = 0; i < mapPoints.value(zoneCount)->count(); i++)
        {
          NodeRect* nr = new NodeRect(i, zoneCount, mapPoints.value(zoneCount)); // p_list->at(i).x(), p_list->at(i).y());
          scene->addItem(nr);
        }
      }
      
      if(zoneName != "") break;
      else zoneCount++;
    }
  }
    
  this->graphicsView->setScene(scene);
  scene->update();
  
  /* задаем масштаб, чтобы все помещалосьв окне */
  this->updateGeometry();
  qreal rw = qreal(pix->width() / qreal(size.width()));  //scene->sceneRect().width());
  qreal rh = qreal(pix->height()) / qreal(size.height()) ; // scene->sceneRect().height());
//  qDebug() << "this->width()=" << this->rect().width()
//           << "this->height()=" << this->rect().height() 
//           << "sceneRect().width() =" << scene->sceneRect().width() 
//           << "sceneRect().height()=" << scene->sceneRect().height() 
//           << "rw=" << rw << "rh=" << rh;

  qreal scl = rw > rh ? rw : rh;
//  scl = scl > 1 ? 1/scl : scl;
  qDebug() << size.width() << size.height() << scl;
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
      {qDebug() << "(ZonePath*)(var))->zcthr->isFinished()";
        ((ZonePath*)(var))->zcthr->stop();
        while(!((ZonePath*)(var))->zcthr->isFinished()) QApplication::processEvents();
        free(((ZonePath*)(var))->zcthr);
      }
    }
  }
  this->deleteLater();
}

bool SvZoneDrawWidget::saveCurrentZone()
{
  if((currentPlanName == "") | (currentZoneName == "")) return false;
  
  QList<QPointF>* p_list = mapPoints.value(currentZoneId);
  
  QString vals = "";
  for(int i = 0; i < p_list->count(); i++)
    vals += (i==0 ? "" : "|") + QString("%1|%2").arg(p_list->at(i).x()).arg(p_list->at(i).y());
  
  QString s = QApplication::applicationDirPath() + "/ini/zones.ini";
  zd_sett = new SvSettings(s);
  
  QStringList lst = zd_sett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    s = zd_sett->readValue(lst.at(i), "zone", "").toString();
    
    /* ищем точное соответсвие имени плана и зоны и записываем текущие данные о точках*/
    if((s.section('%', 2, 2) == currentPlanName) & 
       (s.section('%', 1, 1) == currentZoneName))
    {
      zd_sett->writeValue(lst.at(i), "zone", QString("\%%1\%%2\%%3\%").
                                                                     arg(currentZoneName).
                                                                     arg(currentPlanName).
                                                                     arg(vals));
      break;
    }
  }
  
  return true;
}

void SvZoneDrawWidget::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
//  if(contextMenuEvent->widget())
}

void SvZoneDrawWidget::mousePressEvent(QMouseEvent * event)
{
  qDebug() << "event->y()" << event->y();
  currentZoneId = -1;
  if(event->modifiers().testFlag(Qt::ShiftModifier) & this->ediable)
  {
    newNode(currentZoneId, event->localPos().x(), event->localPos().y());
  }
  else QWidget::mousePressEvent(event);
}

void SvZoneDrawWidget::newNode(int zoneId, int x, int y)
{
  QPointF pnt;
  pnt.setX(x);
  pnt.setY(y);
  
  mapPoints.value(zoneId)->append(pnt);
  qDebug() << "x=" << x << "y=" << y;// <<'\n' 
//           << "pnt.x()=" << pnt.x() << "pnt.y()=" << pnt.y();
  
  NodeRect* nr = new NodeRect(0, mapPoints.value(zoneId)->count() - 1, mapPoints.value(zoneId)); // p_list->at(i).x(), p_list->at(i).y());
  scene->addItem(nr);
  
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

/************************************************/

NodeRect::NodeRect(int id, int zone_id, QList<QPointF> *p_list)
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

NodeRect::~NodeRect()
{
  p_list->removeAt(id);
  for(int i = 0; i < this->scene()->items().count(); i++)
  {
    if(this->scene()->items().at(i)->type() == UserType + 1)
    {
      NodeRect* nr = qgraphicsitem_cast<NodeRect*>(this->scene()->items().at(i));
      if(nr->id > id) nr->id--;      
    }
  }
  this->scene()->update();
  this->scene()->removeItem(this); /** ураааа, заработало! **/
}

void NodeRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

//  QColor fillColor = (option->state & QStyle::State_Selected) ? brushColor.dark(150) : brushColor;
  QColor fillColor = option->state & QStyle::State_MouseOver ? Qt::red : brushColor;// fillColor = fillColor.light(125);
  painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
  painter->setPen(QPen(penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(-4, -4, 8, 8);
  painter->drawText(-8, -8, QString("%1").arg(id));
      
}

QRectF NodeRect::boundingRect() const
{
  return QRectF(-4, -4, 8, 8); /**  !!! **/
}

void NodeRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//  qDebug() << "x=" << event->pos().x() << "y=" << event->pos().y();
//  x = event->pos().x();
//  y = event->pos().y();
  QGraphicsItem::mousePressEvent(event);
  update();
}

void NodeRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//  qDebug() << "x=" << event->scenePos().x() << "y=" << event->scenePos().y();
  p_list->replace(id, event->scenePos());
  QGraphicsItem::mouseMoveEvent(event);
  this->scene()->update();
}

void NodeRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  update();
}

void NodeRect::contextMenuEvent(QGraphicsSceneContextMenuEvent * event)
{
  QMenu menu;
  menu.addAction(removeAction);
  if(removeAction == menu.exec(event->screenPos()))
  {
    this->~NodeRect();
  }
  
//  qDebug() << int(event->type());
}

QPainterPath NodeRect::shape() const
{
    QPainterPath path;
    path.addRect(-4, -4, 8, 8); /**  !!! **/
    return path;
}

/***********************************************************/

ZonePath::ZonePath(SvZoneDrawWidget *parent,
                   QString zone_name,
                   QString plan_name,
                   int zone_id,
                   int* currentZoneId,
                   QString* currentZoneName,
                   QString* currentPlanName,
                   QList<QPointF> *points_list,
                   int alarmType)
{
  this->parent = parent;
  this->p_list = points_list;
  this->zone_name = zone_name;
  this->plan_name = plan_name;
  this->zone_id = zone_id;
  this->currentZoneId = currentZoneId;
  this->currentZoneName = currentZoneName;
  this->currentPlanName = currentPlanName;
  
  switch (alarmType) {
    case 0:
    {
      brushColor = QColor(0, 0, 255, 30); //.darker(10);
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
      
    case 2: // оповещение
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
}

//ZonePath::~ZonePath()
//{
//  if(zcthr) zcthr->stop();
////  zcthr->quit();
//}

void ZonePath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);
  
  if(p_list->count() < 2) return;

  QColor fillColor = (option->state & QStyle::State_MouseOver) ? QColor(0, 0, 255, 140) : brushColor;
  
  int penWidth = ((option->state & QStyle::State_MouseOver) | (option->state & QStyle::State_Selected)) ? 3 : 1;
  painter->setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->setBrush( QBrush(fillColor)); //, Qt::Dense6Pattern));

//  painter->drawRect(0, 0, 100, 100);
  QPainterPath p;
//  p.setFillRule(Qt::OddEvenFill);
  p.moveTo(p_list->at(0).x(), p_list->at(0).y());
  for(int i = 1; i < p_list->count(); i++)
    p.lineTo(p_list->at(i));
  p.closeSubpath();
  
//  p.setPen(QPen(penColor, 1, Qt::SolidLine);//, Qt::RoundCap, Qt::RoundJoin));
//  p.addText(p_list->at(0).x() + 10, p_list->at(0).y() + 30, QFont("Courier", 14), zone_name);
  
  painter->drawPath(p);
  
  painter->setPen(QPen(penColor, 1, Qt::SolidLine));//, Qt::RoundCap, Qt::RoundJoin));
  painter->drawText(p_list->at(0).x() + 10, p_list->at(0).y() + 30, zone_name);
}

QRectF ZonePath::boundingRect() const
{
  
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
    p.moveTo(p_list->at(0).x(), p_list->at(0).y());
    for(int i = 1; i < p_list->count(); i++)
      p.lineTo(p_list->at(i));
    p.closeSubpath();
    return p;
}

void ZonePath::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  *currentZoneId = zone_id;
  *currentZoneName = zone_name;
  *currentPlanName = plan_name;
  parent->_zoneClicked(zone_id, zone_name, plan_name);
  
  QGraphicsPathItem::mousePressEvent(event);
}

void ZonePath::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  *currentZoneId = zone_id;
  *currentZoneName = zone_name;
  *currentPlanName = plan_name;
  parent->_zoneDoubleClicked(zone_id, zone_name, plan_name);
  
  QGraphicsPathItem::mousePressEvent(event);
}
