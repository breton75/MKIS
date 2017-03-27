#ifndef SV_DEVICE_DRAW_H
#define SV_DEVICE_DRAW_H

#include <QObject>
#include <QStandardItemModel>
#include <QList>
#include <QApplication>
#include <QStringList>
#include <QStandardItem>
#include <QTextCodec>
#include <QMap>
#include <QTreeView>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <qmath.h>
#include <QThread>


QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

enum SvGraphicTypes
{
  gtNode = 65537,
  gtZone,
  
  gtVideocamera,
  gtRls,
  gtController
};

class SvZoneDrawWidget;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(SvZoneDrawWidget *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent * e) Q_DECL_OVERRIDE;

    
#endif
    
  private:
      SvZoneDrawWidget *view;
};

class ZonePath;
class SvZoneDrawWidget : public QWidget // QMdiSubWindow
{
    Q_OBJECT
      
  public:
    explicit SvZoneDrawWidget(QWidget* parent,
                              QString planName = "",
                              QString zoneName = "",
                              bool allowEdit = false,
                              bool showSlider = true);
    ~SvZoneDrawWidget();
    
    QGraphicsScene* scene;
    
    bool saveCurrentZone();
    
    void updateDraw(QSize size,
                    QString planName = "",
                    QString zoneName = "",
                    bool allowEdit = false,
                    int alarmType = 0);
    
    void _zoneClicked(int zoneId, QString zoneName, QString planName)
      { emit zoneClicked(zoneId, zoneName, planName); }
    
    void _zoneDoubleClicked(int zoneId, QString zoneName, QString planName)
      { emit zoneDoubleClicked(zoneId, zoneName, planName); }
    
  private:
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
    void newNode(int zoneId, int x, int y);
    
    bool ediable;

    QMap<int, ZonePath*> mapZone;
    QMap<int, QList<QPointF>*> mapPoints;
//    int zoneCount;
    int currentZoneId = -1;
    QString currentPlanName = "";
    QString currentZoneName = "";
    
    GraphicsView *graphicsView;
    QSlider *zoomSlider;
    
  public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    
  private slots:
    void setupMatrix(qreal scaleXY = 0);
    
  signals:
    void zoneClicked(int zoneId, QString zoneName, QString planName);
    void zoneDoubleClicked(int zoneId, QString zoneName, QString planName);
    
};

class NodeRect : public QGraphicsItem/*, public QObject*/
{
//    Q_OBJECT
   
  public:
    explicit NodeRect(int id,
                      int zone_id,
                      QList<QPointF>* p_list);
    
    ~NodeRect();
    
    int type() const { return gtNode; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    int id;
    int zone_id;
    QList<QPointF>* p_list;
    QAction *removeAction;
    
  private:
    int x;
    int y;
    QColor brushColor;
    QColor penColor;
    
    void deleteNode();
    
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);
  

};

class ZoneColorThread;

class ZonePath : public QGraphicsPathItem /*, public QObject*/
{
//  Q_OBJECT
  public:
    explicit ZonePath(SvZoneDrawWidget* parent,
                      QString zone_name,
                      QString plan_name,
                      int zone_id,
                      int* currentZoneId,
                      QString* currentZoneName,
                      QString* currentPlanName,
                      QList<QPointF>* points_list,
                      int alarmType = 0);

    int type() const { return gtZone; }    
    
//    ~ZonePath();
    
//  protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    void keyPressEvent(QKeyEvent * event);
    
    SvZoneDrawWidget *parent;
    int* currentZoneId;
    QString* currentZoneName;
    QString* currentPlanName;
    
    int zone_id;
    QString zone_name;
    QString plan_name;
    
    QList<QPointF>* p_list;
    
    QColor brushColor;
    QColor penColor;
    
    qreal maxX;
    qreal maxY;
    
    ZoneColorThread* zcthr = NULL;
    
};

class ZoneColorThread : public QThread
{
  private:
    int intrvl = 0;
    ZonePath* zone;
    bool isActive = true;
    
  public:
    explicit ZoneColorThread(int interval, ZonePath* z):
      zone(z),
      intrvl(interval) { }      

    void run()
    {
      quint64 i;
      QColor brush = zone->brushColor;
      QColor pen = zone->penColor;
      while(isActive)
      {
        zone->brushColor = i%2 ? brush.darker(30) : brush;
        zone->penColor   = i%2 ? pen.darker(255) : pen;
        zone->scene()->update();
        i++;
        msleep(intrvl);
      }
      quit();
    }  
    
    void stop() { isActive = false; }
};

#endif // SV_DEVICE_DRAW_H
