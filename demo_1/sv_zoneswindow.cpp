#include "sv_zoneswindow.h"
#include "./COMMON/sv_settings.h"

//#include "mydraw.h"

#define P_CCNT 2



SvZonesWindow* ZONES_WINDOW_UI;
extern SvZone* ZONE_UI;

QList<QStandardItem *> zone_rowItems;

SvZonesWindow::SvZonesWindow(QMdiArea *parent,
                             QString title,
                             QString zoneName)
{
//  QTextCodec * codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  
  
  this->setObjectName(QStringLiteral(ZONES_SUBWINDOW_NAME));
  this->setParent(parent);
  this->setWindowTitle(title);
  this->setGeometry(0, 0, 1000, 800);
  
//  QHBoxLayout* hlay = new QHBoxLayout(this);
//  hlay->setSpacing(2);
//  hlay->setObjectName(QStringLiteral("hlay"));
  
  QVBoxLayout* vlay2 = new QVBoxLayout(this);
  vlay2->setSpacing(2);
  vlay2->setContentsMargins(2, 2, 2, 2);
  vlay2->setObjectName(QStringLiteral("vlay2"));
  
  QSplitter *hSplitter = new QSplitter(Qt::Horizontal, this);
//  hSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QSplitter *vSplitter = new QSplitter(Qt::Vertical, this);
//  vSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  vlay2->addWidget(hSplitter);
  vlay2->addWidget(vSplitter);
  
//  widgetLay = new QVBoxLayout(this);
//  widgetLay->setObjectName(QStringLiteral("widgetLay"));

  zoneDrawWidget = new SvZoneDrawWidget(this);
  zoneDrawWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  zoneDrawWidget->setGeometry(0, 0, 1000, 800);

//  zoneDrawWidget->setGeometry(zoneDrawWidget->pos().x(), zoneDrawWidget->pos().y(),
//                              1000, zoneDrawWidget->height());
//  widgetLay->addWidget(zoneDrawWidget);
  
//  hlay->addLayout(widgetLay);
//  hlay->addWidget(zoneDrawWidget);
  
  treeDevices = new SvTreeView(this);
  treeDevices->setObjectName(QStringLiteral("treeDevices"));
  QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(treeDevices->sizePolicy().hasHeightForWidth());
//  treeDevices->setMinimumWidth(400);
  treeDevices->setSizePolicy(sizePolicy1);
  
//  vlay2->addWidget(treeDevices);
  
  tablePlans = new QTableView(this);
  tablePlans->setObjectName(QStringLiteral("tablePlans"));
  QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
//  tablePlans->setMinimumWidth(400);
  sizePolicy2.setHeightForWidth(tablePlans->sizePolicy().hasHeightForWidth());
  tablePlans->setSizePolicy(sizePolicy2);
  
//  vlay2->addWidget(tablePlans);

//  hlay->addLayout(vlay2);
  
  hSplitter->addWidget(zoneDrawWidget);
  hSplitter->addWidget(vSplitter);
  vSplitter->addWidget(treeDevices);
  vSplitter->addWidget(tablePlans);
  
  parent->addSubWindow(this);
  
/****************************************/
  model->setColumnCount(P_CCNT);
  
  model->setHeaderData(0, Qt::Horizontal, QString("Зона"), Qt::DisplayRole);
  model->setHeaderData(1, Qt::Horizontal, QString("Входит в зону"), Qt::DisplayRole);
//  model->setHeaderData(2, Qt::Horizontal, QString("Файл изображения"), Qt::DisplayRole);
//  model->setHeaderData(3, Qt::Horizontal, QString("Описание"), Qt::DisplayRole);
  
  tablePlans->setModel(model);
  tablePlans->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
  SvSettings* zsett = new SvSettings(s);
  
  QStringList lst = zsett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    zone_rowItems.clear();
    s = zsett->readValue(lst.at(i), "zone", "").toString();
    for(int j = 1; j <= P_CCNT; j++)
    {
      zone_rowItems << new QStandardItem(s.section('%', j, j));
    }

    model->appendRow(zone_rowItems);
    tablePlans->setRowHeight(i, 22);
  }
  
  tablePlans->setColumnWidth(0, 200);
  tablePlans->setColumnWidth(1, 200);
//  tablePlans->setColumnWidth(2, 400);
//  tablePlans->setColumnWidth(3, 400);
  
  connect(tablePlans, SIGNAL(clicked(QModelIndex)), this, SLOT(tableClicked(QModelIndex)));
  connect(zoneDrawWidget, SIGNAL(zoneClicked(QGraphicsSceneMouseEvent*,int,QString)), this, SLOT(zoneClicked(QGraphicsSceneMouseEvent*,int,QString)));
  connect(zoneDrawWidget, SIGNAL(zoneDoubleClicked(QGraphicsSceneMouseEvent*,int,QString)), this, SLOT(zoneDoubleClicked(QGraphicsSceneMouseEvent*,int,QString)));
  
}

void SvZonesWindow::tableClicked(QModelIndex mi)
{
  currentZoneName = model->data(model->index(mi.row(), 0)).toString();
  zoneDrawWidget->updateDraw(QSize(1000, 800), currentZoneName);
//  zoneDrawWidget->updateDraw(QSize(this->width(), this->height()), currentZoneName);
}

void SvZonesWindow::treeZoneChanged(QString zoneName)
{
  currentZoneName = zoneName;
  zoneDrawWidget->updateDraw(QSize(1000, 800), currentZoneName);
  
  for(int i = 0; i < treeDevices->treeModel->rowCount(treeDevices->rootIndex()); i++)
    treeDevices->treeModel->removeRow(i, treeDevices->rootIndex());
//  qDebug() << treeDevices->treeModel->rowCount(treeDevices->rootIndex());
  treeDevices->loadDevices(zoneName);
  treeDevices->expandAll();
}

SvZonesWindow::~SvZonesWindow()
{

}

void SvZonesWindow::zoneClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
{
  /************ загружаем список устройств, для зоны ******************/
//  qDebug() << treeDevices->treeModel->rowCount(treeDevices->rootIndex());
  for(int i = 0; i < treeDevices->treeModel->rowCount(treeDevices->rootIndex()); i++)
    treeDevices->treeModel->removeRow(i, treeDevices->rootIndex());
//  qDebug() << treeDevices->treeModel->rowCount(treeDevices->rootIndex());
  treeDevices->loadDevices(zoneName);
  treeDevices->expandAll();
  
  currentZoneName = zoneName;
//  zoneDrawWidget->updateDraw(QSize(zoneDrawWidget->width(), zoneDrawWidget->height()), zoneName);
}

void SvZonesWindow::zoneDoubleClicked(QGraphicsSceneMouseEvent *event, int zoneId, QString zoneName)
{
  /************ загружаем список устройств, для зоны ******************/
//  if(treeDevices->treeModel->rowCount()) treeDevices->treeModel->clear();
  if(event->modifiers().testFlag(Qt::ControlModifier))
  {
    ZONE_UI = new SvZone(zoneName, true, this);
  
    connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
    connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
  }
  else 
  {
    currentZoneName = zoneName;
    zoneDrawWidget->updateDraw(QSize(this->width(), this->height()), zoneName);
    
  }
}

void SvZonesWindow::on_ZONE_UI_closed()
{
  if(ZONE_UI->result() == QDialog::Accepted)
  {
    zoneDrawWidget->updateDraw(QSize(zoneDrawWidget->width(), zoneDrawWidget->height()), currentZoneName);
  }
  ZONE_UI->~SvZone();
}
