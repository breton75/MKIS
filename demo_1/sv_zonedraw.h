#ifndef SVNODERECT_ZPNEPATH_H
#define SVNODERECT_ZPNEPATH_H

#include "../Panel/panel_tcp.h"
#include "./sv_rls2bitwidget.h"

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
#include <QMimeData>
#include <QDrag>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QGraphicsProxyWidget>
#include <QPicture>

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

enum SvGraphicTypes
{
  gtNode = 65537,
  gtZone,
  gtDevice,
  
  gtVideocamera,
  gtRls,
  gtController,
  gtSCUD
  
};

class SvZoneDrawWidget;
class GraphSimbolDevice;

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
                              bool showSlider = true);
    ~SvZoneDrawWidget();
    
    QGraphicsScene* scene;
    
    bool saveCurrentZone();
    
    void updateDraw(QSize size,
                    QString zoneName = "",
                    int alarmType = 0);
    
    void editZone(QSize size,
                  QString zoneName = "");
    
    void _zoneClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
      { emit zoneClicked(event, zoneId, zoneName); }
    
    void _zoneDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
      { emit zoneDoubleClicked(event, zoneId, zoneName); }
    
    void _deviceClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
      { emit deviceClicked(event, zoneId, zoneName); }
    
    void _deviceDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
      { emit deviceDoubleClicked(event, zoneId, zoneName); }
    
    void makeZoneFullName();
    
    void runRLS(float x, float y);
    
    QString currentZoneFullName = "";
    
  private:
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
    void newNode(int zoneId, float x, float y);
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    
    bool editable;

    QMap<int, ZonePath*> mapZones;
    QMap<int, QList<QPointF>*> mapPoints;
//    QMap<int, QList<QPointF>*> mapDev;
    
    QMap<int, QGraphicsItem*> mapDevices;
    
//    int zoneCount;
    int currentZoneId = -1;
    int currentDeviceId = -1;
    QPixmap* currentPix;
    QString currentZoneParentName = "";
    QString currentZoneName = "";
    QString currentDeviceName = "";
    
    GraphicsView *graphicsView;
    QSlider *zoomSlider;
    
    QImage* img;
    QImage* img_rls;
    SvRls2BitWidget* rlswdg;
    SvRlsDataBuffering* rls;
    void* _buffer;
    QTimer timer;
    float angle;
    float x;
    float y;
    int img_resolution;
    int draw_points_per_line;
    
    QWidget* wdg;
    QVBoxLayout* vlay;
    QLabel* lbl;
    
//    QSqlQueryModel *m_zones_model;
//    QSqlQuery* query;
    
  public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    
  private slots:
    void setupMatrix(qreal scaleXY = 0);
    
  signals:
    void zoneClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName);
    void zoneDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName);
    void deviceClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString deviceName);
    void deviceDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString deviceName);
};

class ZoneNode : public QGraphicsItem/*, public QObject*/
{
//    Q_OBJECT
   
  public:
    explicit ZoneNode(int id,
                      int zone_id,
                      QList<QPointF>* p_list);
    
    ~ZoneNode();
    
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
                      QString zone_parent_name,
                      int zone_id,
                      int* currentZoneId,
                      QString* currentZoneName,
                      QString* currentZoneParentName,
                      bool doFeedback,
                      QList<QPointF>* points_list,
                      bool isSelected,
                      int alarmType = 0);

    int type() const { return gtZone; }    
    
//    ~ZonePath();
    
    QColor brushColor;
    QColor penColor;
    
    ZoneColorThread* zcthr = NULL;   
    
  protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    
//    void keyPressEvent(QKeyEvent * event);
  private:
    SvZoneDrawWidget *parent;
    int* currentZoneId;
    QString* currentZoneName;
    QString* currentZoneParentName;
    bool doFeedback;
    int zone_id;
    QString zone_name;
    QString zone_parent_name;
    
    QList<QPointF>* p_list;

    qreal maxX;
    qreal maxY;
 
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

/** **************************** **/
/** ********** devices ********* **/
/** **************************** **/

class GraphSimbolDevice : public QGraphicsItem/*, public QObject*/
{
  public:
    explicit GraphSimbolDevice(SvZoneDrawWidget* parent,
                               bool allowEdit,
                               int device_type,
                               int id,
                               int zone_id,
                               QString zone_name,                               
                               QString device_name,
                               float X,
                               float Y);
    
    ~GraphSimbolDevice();
    
    int type() const { return gtDevice; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) Q_DECL_OVERRIDE;

    SvZoneDrawWidget* parent;
    int id;
    int zone_id;
    QString zone_name;
    QString device_name;
    int device_type;
    QPointF position;
    QAction *removeAction;
    QAction* editDeviceAction;
    QAction* playVideoAction;
    QAction* playRLSAction;
    QAction* playRLSOnMapAction;

  private:
    QColor brushColor;
    QColor penColor;
    bool isEditable;
    
    Panel_tcp* panel;
    bool led = false;
    
    void deleteItem();
    
//  private slots:
//    void on_removeAction_triggered();
//    void on_editDeviceAction_triggered();
//    void on_playVideoAction_triggered();
//    void on_playRLSAction_triggered();
    
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *);
};

#endif // SVNODERECT_ZPNEPATH_H
