#include "mydraw.h"
int x2 = 30;
int y2 = 30;

MyDraw::MyDraw(QWidget *parent) /*: QWidget(parent)*/  
{
  this->setParent(parent);
  this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  
//  this->setGeometry(0, 0, 400, 408);
//  img = QImage(); // QImage::Format_RGB888);
  
  if(!pix.load("D:/c++/MKIS/demo_1/plans/of_sx.jpg"))
    qDebug() << "not loaded";
  
  p_list =new QList<QPoint>; // .clear();
  n_list.clear();
   this->parent = parent;
  
  this->setDragMode(QGraphicsView::RubberBandDrag);
  this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  
//  painter = new QPainter(this);
  
//  painter.begin(this);
//  
  
//  connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(onClick(QMouseEvent*)));
  
//  view  = new QGraphicsView(this);
  scene = new QGraphicsScene(/*this*/);
//  scene.setForegroundBrush(QColor(255, 255, 255, 127));
//  scene->setForegroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
//  scene->setForegroundBrush(QBrush(QColor(0, 0, 255, 30), Qt::CrossPattern));
  scene->addPixmap(pix); //.scaled(this->width(), this->height(), Qt::KeepAspectRatio));
//  scene->setStyle(QStyle::);
  

//  this->path = new QPainterPath();
  
//  path->moveTo(10, 10);
//  path->lineTo(60, 60);
//  path->lineTo( 120, 30);
////  path.closeSubpath();
  
//  path = (QPainterPath*)(scene->addPath(*path));
  

  p_list->append(QPoint(10, 10));
  p_list->append(QPoint(80, 10));
  p_list->append(QPoint(80, 180));
  p_list->append(QPoint(10, 170));
  
  
  path = new DrawPath(0, p_list);
  scene->addItem(path);
  
  scene->addItem(new NodeRect(10, 10));
  scene->addItem(new NodeRect(80, 10));
  scene->addItem(new NodeRect(80, 180));
  scene->addItem(new NodeRect(10, 170));
  
  this->setScene(scene);
//  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//  this->setGeometry(0,0, 200, 300);
//    NodeRect* nr = new NodeRect(this, 20, 20);
//  nr->setParent(this);
//  scene->addItem(nr);
//  scene->addPath(path);
//  qDebug() << "222222";
//  this->show();
//  scene->update();
// this->show();
  
}

MyDraw::~MyDraw()
{
  this->deleteLater();
}

void MyDraw::mousePressEvent(QMouseEvent * event)
{
  if(event->modifiers() & Qt::ShiftModifier)
    onClick(event);
  else QGraphicsView::mousePressEvent(event);
}

//void MyDraw::paintEvent(QPaintEvent *event)
//{
//  QPainter painter;
////  painter.begin(this->paintEngine());
////  this->pa
////  painter.drawPixmap(0, 0, pix);
////qDebug() << "222222";
////  if(p_list.count() > 1)
////  {
  
//    QPen pen;
//    pen.setStyle(Qt::SolidLine);
//    pen.setColor(Qt::blue);
//    pen.setWidth(2);
//    painter.setPen(pen);
    
    
//    QPainterPath path;
////    path.moveTo(p_list.at(0));
    
//    path.moveTo(10, 10);
//    path.lineTo(100, 100);
//    path.lineTo(010, 130);
  
////    for(int i = 1; i < p_list.count(); i++)
////    {
////      path.lineTo(p_list.at(i));
    
////    }
//    path.closeSubpath();
//  qDebug() << "222222";
////    painter.drawPath(path);
  
////  for(int i = 1; i < n_list.count(); i++)
////  {
    
////  }
////  path.closeSubpath();
  
////  painter.drawPath(path);
////  }
  
////  view->update();
  
//}

void MyDraw::onClick(QMouseEvent *event)
{
  
  
  QPoint pnt;
  pnt.setX(event->x());
  pnt.setY(event->y());
  
  p_list->append(pnt);
  qDebug() << "event->x()=" << event->x() << "event->y()=" << event->y();// <<'\n' 
//           << "pnt.x()=" << pnt.x() << "pnt.y()=" << pnt.y();
  
  n_list.append(new NodeRect(pnt.x(), pnt.y()));
//  n_list.at(n_list.count() - 1)->setParent(this);
  scene->addItem(n_list.at(n_list.count() - 1));
//  scene->items().append();
//  path->lineTo(pnt.x(), pnt.y());
//QPainterPath(scene->items(path).at(0)).lineTo(pnt.x(), pnt.y());

//  scene->removeItem();
  
//  x2 = x2 + 30;
//  y2 = y2 + 30;
  
//  n_list.at(n_list.count() - 1)->show();
  scene->update();
//  this->repaint();
  
}

/***********************************************************/

NodeRect::NodeRect(int id, QList<QPointF> *p_list)
{
  
  this->id = id;
  this->p_list = p_list;
  this->setPos(p_list->at(id));
  
  brushColor = Qt::yellow;
  penColor = Qt::blue;
  
  setFlags(ItemIsMovable);   //ItemIsSelectable | 
  setAcceptHoverEvents(true);
  
}

QPainterPath NodeRect::shape() const
{
    QPainterPath path;
    path.addRect(-4, -4, 8, 8); /**  !!! **/
    return path;
}

void NodeRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);

//  QColor fillColor = (option->state & QStyle::State_Selected) ? brushColor.dark(150) : brushColor;
  QColor fillColor = option->state & QStyle::State_MouseOver ? fillColor = Qt::red : brushColor;// fillColor = fillColor.light(125);
  painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));
  painter->setPen(QPen(penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(-4, -4, 8, 8);
}

QRectF NodeRect::boundingRect() const
{
  return QRectF(-4, -4, 8, 8); /**  !!! **/
}

void NodeRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() << "x=" << event->pos().x() << "y=" << event->pos().y();
  x = event->pos().x();
  y = event->pos().y();
  QGraphicsItem::mousePressEvent(event);
  update();
}

void NodeRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() << "x=" << event->scenePos().x() << "y=" << event->scenePos().y();
  p_list->replace(id, event->scenePos());
  QGraphicsItem::mouseMoveEvent(event);
  update();
}

void NodeRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);
  update();
}

/***********************************************************/

DrawPath::DrawPath(QList<QPointF> *points_list)
{
  this->p_list = points_list;
  
  brushColor = QColor(255, 0, 0, 120);
  penColor = Qt::blue;
}

void DrawPath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);
  
  if(p_list->count() < 2) return;
  
//  QColor fillColor = (option->state & QStyle::State_Selected) ? brushColor.dark(150) : brushColor;
//  if (option->state & QStyle::State_MouseOver)
//      fillColor = fillColor.light(125);
  QColor fillColor = (option->state & QStyle::State_MouseOver) ? brushColor.dark(150) : brushColor;
  painter->setPen(QPen(penColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

//  painter->drawRect(0, 0, 100, 100);
  QPainterPath p;
  p.moveTo(p_list->at(0).x(), p_list->at(0).y());
  for(int i = 1; i < p_list->count(); i++)
    p.lineTo(p_list->at(i));
  p.closeSubpath();
  
  painter->drawPath(p);
}

QRectF DrawPath::boundingRect() const
{
  return QRectF(0, 0, 300, 300);
}

//QPainterPath DrawPath::shape() const
//{
//    QPainterPath path;
//    path.addRect(0, 0, 300, 300); /**  !!! **/
//    return path;
//}
