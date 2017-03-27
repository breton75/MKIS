#ifndef SVPLANSWINDOW_H
#define SVPLANSWINDOW_H

#include "sv_zonedraw.h"
#include "sv_treeview.h"
#include "sv_zone.h"

#include <QObject>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QList>
#include <QTableView>
#include <QApplication>
#include <QStringList>
#include <QStandardItem>
#include <QTextCodec>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QMap>
#include <QTreeView>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QEvent>
#include <QFrame>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QSplitter>

QT_BEGIN_NAMESPACE
class QSlider;
class QSplitter;
QT_END_NAMESPACE

#define ZONES_SUBWINDOW_NAME "subw_zones"

class SvZonesWindow : public QWidget //   QMdiSubWindow
{
    Q_OBJECT
      
  public:
    explicit SvZonesWindow(QMdiArea* parent,
                           QString title,
                           QString zoneName = "");
    ~SvZonesWindow();
    
//    QString currentPlanName = "";
//    QString currentZoneName = "";
    QComboBox* cbCameraList;
    QWidget* widgetPlans;
    SvTreeView* treeDevices; 
    QPushButton* bnPlay;
    QTableView* tablePlans; 
    QStandardItemModel* model = new QStandardItemModel();

    SvZoneDrawWidget* zoneDrawWidget;
    
    QVBoxLayout* widgetLay;
    
//    QGraphicsScene* scene = new QGraphicsScene;
//    QPixmap* pix = new QPixmap;
    
    QList<QPointF>* p_list = new QList<QPointF>;
//    QList<NodeRect>* n_list = new QList<NodeRect>;
    
    
  protected:
//    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
//    void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);
    
  private:
    QString currentZoneName = "";
//    GraphicsView *graphicsView;
    
  public slots:
    void tableClicked(QModelIndex mi);
    void zoneClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName);
    void zoneDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName);
    void on_ZONE_UI_closed();
    void treeZoneChanged(QString zoneName);
    
  private slots:
//    void onClick(QMouseEvent * event);
    
};



#endif // SVPLANSWINDOW_H
