#include "sv_alarmswindow.h"
#include "./COMMON/sv_settings.h"

#define P_CCNT 4

SvAlarmsWindow* ALARMS_UI;
SvSettings* alarm_sett;

QList<QStandardItem *> alarms_rowItems;

SvAlarmsWindow::SvAlarmsWindow(QMdiArea *parent,
                               QString title)
{
  this->setObjectName(QStringLiteral(ALARMS_SUBWINDOW_NAME));
  this->setParent(parent);
  this->setWindowTitle(title);
//  this->setGeometry(100, 100, width, height);
//  QPalette palette;
//  QBrush brush(QColor(255, 255, 255, 255));
//  brush.setStyle(Qt::SolidPattern);
//  palette.setBrush(QPalette::Active, QPalette::Base, brush);
//  QBrush brush1(QColor(240, 0, 0, 120));
//  brush1.setStyle(Qt::SolidPattern);
//  palette.setBrush(QPalette::Active, QPalette::Window, brush1);
//  palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
//  palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
//  palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
//  palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
//  this->setPalette(palette);
//  this->setAutoFillBackground(true);
  
  
  QVBoxLayout* vlay = new QVBoxLayout(this);
  vlay->setSpacing(2);
  vlay->setContentsMargins(2, 2, 2, 2);
  vlay->setObjectName(QStringLiteral("vlay"));
  
  /*************** панель кнопок ******************/  
  QFrame* aw_frame = new QFrame(this);
  aw_frame->setObjectName(QStringLiteral("aw_frame"));
  QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(aw_frame->sizePolicy().hasHeightForWidth());
  aw_frame->setSizePolicy(sizePolicy1);
  aw_frame->setMinimumSize(QSize(0, 33));
  aw_frame->setMaximumSize(QSize(16777215, 36));
  aw_frame->setFrameShape(QFrame::Panel);
  aw_frame->setFrameShadow(QFrame::Raised);
  aw_frame->setAutoFillBackground(true);
  
  QHBoxLayout* hlayButtons = new QHBoxLayout(aw_frame);
  hlayButtons->setObjectName(QStringLiteral("hlayButtons"));
  hlayButtons->setContentsMargins(-1, 2, -1, 2);
  
  bnAddDevice = new QToolButton(aw_frame);
  bnAddDevice->setObjectName(QStringLiteral("bnAddDevice"));
  bnAddDevice->setMinimumSize(QSize(26, 26));
  bnAddDevice->setMaximumSize(QSize(26, 26));
  hlayButtons->addWidget(bnAddDevice);

//  QSpacerItem* spacer_1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
//  hlayButtons->addItem(spacer_1);

  bnEditDevice = new QToolButton(aw_frame);
  bnEditDevice->setObjectName(QStringLiteral("bnEditDevice"));
  bnEditDevice->setMinimumSize(QSize(26, 26));
  bnEditDevice->setMaximumSize(QSize(26, 26));
  hlayButtons->addWidget(bnEditDevice);
  
//  QSpacerItem* spacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
//  hlayButtons->addItem(spacer_2);

  bnDeleteDevice = new QToolButton(aw_frame);
  bnDeleteDevice->setObjectName(QStringLiteral("bnDeleteDevice"));
  bnDeleteDevice->setMinimumSize(QSize(26, 26));
  bnDeleteDevice->setMaximumSize(QSize(26, 26));
  hlayButtons->addWidget(bnDeleteDevice); 

  QSpacerItem* spacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  hlayButtons->addItem(spacer_3);  
  
//  vlay->addLayout(hlayButtons);
  vlay->addWidget(aw_frame);
  
  /**********************************************/
  
  QHBoxLayout* hlayWidgets = new QHBoxLayout();
  hlayWidgets->setSpacing(2);
  hlayWidgets->setObjectName(QStringLiteral("hlayWidgets"));
  
//  vlayZoneDraw = new QVBoxLayout(this);
//  vlayZoneDraw->setObjectName(QStringLiteral("vlayZoneDraw"));

  zoneDrawWidget = new SvZoneDrawWidget(this);
  zoneDrawWidget->setObjectName(QStringLiteral("zoneDrawWidget"));
  zoneDrawWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
//  vlayZoneDraw->addWidget(zoneDrawWidget);
  
  hlayWidgets->addWidget(zoneDrawWidget);
//  hlayWidgets->addLayout(vlayZoneDraw); /**/
  
  rightWidget = new QWidget(this);
  rightWidget->setObjectName(QStringLiteral("rightWidget"));
  QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(rightWidget->sizePolicy().hasHeightForWidth());
  rightWidget->setSizePolicy(sizePolicy2);
  
  hlayWidgets->addWidget(rightWidget);
  
  
  vlay->addLayout(hlayWidgets);
  
  /***********************************************/
  
  tableAlarms = new QTableView(this);
  tableAlarms->setObjectName(QStringLiteral("tableAlarms"));
  QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(tableAlarms->sizePolicy().hasHeightForWidth());
  tableAlarms->setSizePolicy(sizePolicy3);
  
  vlay->addWidget(tableAlarms);

  parent->addSubWindow(this);
  QIcon ic = QIcon(":/tree32/icons/Warning.ico");
  parent->subWindowList().at(parent->subWindowList().count() - 1)->setWindowIcon(ic);
  
/****************************************/
  model->setColumnCount(4);
  
  model->setHeaderData(0, Qt::Horizontal, QString("План[Карта]"), Qt::DisplayRole);
  model->setHeaderData(1, Qt::Horizontal, QString("Входит в"), Qt::DisplayRole);
  model->setHeaderData(2, Qt::Horizontal, QString("Файл изображения"), Qt::DisplayRole);
  model->setHeaderData(3, Qt::Horizontal, QString("Описание"), Qt::DisplayRole);
  
  tableAlarms->setModel(model);
  tableAlarms->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  QString s = QApplication::applicationDirPath() + "/ini/plans.ini";
  alarm_sett = new SvSettings(s);
  
  QStringList lst = alarm_sett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {
    alarms_rowItems.clear();
    s = alarm_sett->readValue(lst.at(i), "alarm", "").toString();
    for(int j = 1; j <= P_CCNT; j++)
    {
      alarms_rowItems << new QStandardItem(s.section('%', j, j));
    }

    model->appendRow(alarms_rowItems);
    tableAlarms->setRowHeight(i, 22);
  }
  
  tableAlarms->setColumnWidth(0, 200);
  tableAlarms->setColumnWidth(1, 200);
  tableAlarms->setColumnWidth(2, 400);
  tableAlarms->setColumnWidth(3, 400);
  
  connect(tableAlarms, SIGNAL(clicked(QModelIndex)), this, SLOT(tableClicked(QModelIndex)));

}

void SvAlarmsWindow::tableClicked(QModelIndex mi)
{
  QString currentAlarmName = model->data(model->index(mi.row(), 0)).toString();
  zoneDrawWidget->updateDraw(QSize(zoneDrawWidget->width(), zoneDrawWidget->height()), currentAlarmName);
}

SvAlarmsWindow::~SvAlarmsWindow()
{

}
