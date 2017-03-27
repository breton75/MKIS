#ifndef MYDRAW_H
#define MYDRAW_H

#include <QWidget>
#include <QDebug>
#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPicture>
#include <QFile>
#include <QImage>
#include <QPainterPath>
#include <QList>
#include <QPoint>
#include <QGraphicsItem>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class NodeRect;
class DrawPath;

class MyDraw : public QGraphicsView // QWidget  /*, public QObject*/
{
    Q_OBJECT
  public:
    explicit MyDraw(QWidget *parent = 0);
    ~MyDraw();
    
    QImage img;
    QPixmap pix;
    QGraphicsScene *scene;
    
    QWidget* parent;
    
  private:
//    void paintEvent( QPaintEvent *event );
    
    QList<QPoint>* p_list;
    QList<NodeRect*> n_list;
    
//    QGraphicsView  *view; 
//    QGraphicsScene *scene;
    DrawPath* path;
//    QPainter painter;
    
  protected:
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    
  private slots:
    void onClick(QMouseEvent * event);
    
  public slots:
};

class NodeRect : public QGraphicsItem/*, public QObject*/
{
   
  public:
    explicit NodeRect(int id,
                      QList<QPointF>* p_list);
    
//    ~NodeRect();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    int id;
    QList<QPointF>* p_list;
    
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

//  signals:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;  
    
  private:
//    QPainter *painter;
    
    int x;
    int y;
    QColor brushColor;
    QColor penColor;
//    QVector<QPointF> stuff;
};

class DrawPath : public QGraphicsPathItem /*, public QObject*/
{
  public:
    explicit DrawPath(QList<QPointF>* points_list);
    
//    ~DrawPath();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
//    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    int id;

    QList<QPoint>* p_list;
    
  private:
//    QPainter *painter;
    
//    int x;
//    int y;
    QColor brushColor;
    QColor penColor;

};

#endif // MYDRAW_H
