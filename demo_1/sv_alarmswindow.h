#ifndef SVALARMSWINDOW_H
#define SVALARMSWINDOW_H

#include "sv_zonedraw.h"
#include "./COMMON/sv_ffmpeg.h"

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
#include <QToolButton>

#define ALARMS_SUBWINDOW_NAME "subw_alarms"

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE

class SvAlarmsWindow : public QWidget //   QMdiSubWindow
{
    Q_OBJECT
      
  public:
    explicit SvAlarmsWindow(QMdiArea* parent,
                            QString title);
    ~SvAlarmsWindow();
    
//    QTreeView* treeDevPlans; 
    
    QTableView* tableAlarms; 
    QStandardItemModel* model = new QStandardItemModel();

    QWidget* rightWidget;
    SvZoneDrawWidget* zoneDrawWidget;
    SvFFMpegWidget* ffmpegWidget;
    
    QVBoxLayout* vlayZoneDraw;
    QToolButton* bnAddDevice;
    QToolButton* bnEditDevice;
    QToolButton* bnDeleteDevice;

    QList<QPointF>* p_list = new QList<QPointF>;
   
  public slots:
    void tableClicked(QModelIndex mi);
    
  private slots:
//    void onClick(QMouseEvent * event);
    
};



#endif // SVALARMSWINDOW_H
