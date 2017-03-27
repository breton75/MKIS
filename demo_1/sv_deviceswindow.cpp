#include "sv_deviceswindow.h"
#include "./COMMON/sv_settings.h"
#include "./COMMON/sv_device.h"

extern SvDevice* DEV_UI;

#define DEV_CCNT 8


QString toUnicode(QString str);

SvDevicesWindow* DEV_WINDOW_UI;

SvSettings* devsett;
QList<QStandardItem *> rowItems;

QString toUnicode(QString str)
{
   QTextCodec * codec = QTextCodec::codecForName("UTF-8");//"IBM 866"
   return codec->toUnicode(QString(str).toStdString().c_str());
}

SvDevicesWindow::SvDevicesWindow(QMdiArea *parent,
                                 QString title)
{
//  QTextCodec * codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  
  this->setObjectName(QStringLiteral(DEVICES_SUBWINDOW_NAME));
  this->setParent(parent);
  this->setWindowTitle(title);
  parent->addSubWindow(this);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//  this->setGeometry(100, 100, width, height);
  
  QVBoxLayout* vlay = new QVBoxLayout(this);
  vlay->setParent(this);
  vlay->setSpacing(2);
  vlay->setContentsMargins(2, 2, 2, 2);
  vlay->setObjectName(QStringLiteral("vlay_devices"));
   
  /*************************************/
  QFrame* dw_frame = new QFrame(this);
  dw_frame->setObjectName(QStringLiteral("dw_frame"));
  QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(dw_frame->sizePolicy().hasHeightForWidth());
  dw_frame->setSizePolicy(sizePolicy1);
  dw_frame->setMinimumSize(QSize(0, 33));
  dw_frame->setMaximumSize(QSize(16777215, 36));
  dw_frame->setFrameShape(QFrame::Panel);
  dw_frame->setFrameShadow(QFrame::Raised);
  dw_frame->setAutoFillBackground(true);
  
  QHBoxLayout* horizontalLayout = new QHBoxLayout(dw_frame);
  horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
  horizontalLayout->setContentsMargins(-1, 2, -1, 2);
  
  bnAddDevice = new QToolButton(dw_frame);
  bnAddDevice->setObjectName(QStringLiteral("bnAddDevice"));
  bnAddDevice->setMinimumSize(QSize(26, 26));
  bnAddDevice->setMaximumSize(QSize(26, 26));
  horizontalLayout->addWidget(bnAddDevice);

//  QSpacerItem* spacer_1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
//  horizontalLayout->addItem(spacer_1);

  bnEditDevice = new QToolButton(dw_frame);
  bnEditDevice->setObjectName(QStringLiteral("bnEditDevice"));
  bnEditDevice->setMinimumSize(QSize(26, 26));
  bnEditDevice->setMaximumSize(QSize(26, 26));
  horizontalLayout->addWidget(bnEditDevice);
  
//  QSpacerItem* spacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
//  horizontalLayout->addItem(spacer_2);

  bnDeleteDevice = new QToolButton(dw_frame);
  bnDeleteDevice->setObjectName(QStringLiteral("bnDeleteDevice"));
  bnDeleteDevice->setMinimumSize(QSize(26, 26));
  bnDeleteDevice->setMaximumSize(QSize(26, 26));
  horizontalLayout->addWidget(bnDeleteDevice); 

  QSpacerItem* spacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  horizontalLayout->addItem(spacer_3);  
  
//  vlay->addLayout(horizontalLayout);
  vlay->addWidget(dw_frame);
  
  QIcon ic = QIcon(":/tree32/icons/wagon.ico");
  parent->subWindowList().at(parent->subWindowList().count() - 1)->setWindowIcon(ic);
  
  QMetaObject::connectSlotsByName(this);
  
  /*******************************************/
  
  
  table = new QTableView(this);
  table->setParent(this);
  table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  table->setObjectName(QStringLiteral("tbl_devices"));
  
  
  vlay->addWidget(table);
  model->setColumnCount(8);
  
  model->setHeaderData(0, Qt::Horizontal, QString("Устройство"));
  model->setHeaderData(1, Qt::Horizontal, QString("Класс"));
  model->setHeaderData(2, Qt::Horizontal, QString("Производитель"));
  model->setHeaderData(3, Qt::Horizontal, QString("Модель"));
  model->setHeaderData(4, Qt::Horizontal, QString("IP адрес"));
  model->setHeaderData(5, Qt::Horizontal, QString("Порт")); 
  model->setHeaderData(6, Qt::Horizontal, QString("Зона безопасности"));
  model->setHeaderData(7, Qt::Horizontal, QString("Описание"));
//  model->setHeaderData(7, Qt::Horizontal, QString("Высота"));

  table->setModel(model);
  table->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  QString s = QApplication::applicationDirPath() + "/ini/devices.ini";
  devsett = new SvSettings(s);

  QStringList lst = devsett->appSettings->childGroups();
  for(int i = 0; i < lst.count(); i++)
  {

    rowItems.clear();
    s = devsett->readValue(lst.at(i), "device", "").toString();
    for(int j = 1; j <= DEV_CCNT; j++)
      rowItems << new QStandardItem(toUnicode(s.section('%', j, j)));

    model->appendRow(rowItems);
    table->setRowHeight(i, 22);
  }
  
  for(int i = 0; i < DEV_CCNT; i++)
    table->setColumnWidth(i, 150);
  
  table->setEditTriggers(QTableView::NoEditTriggers);
  
  connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
  
  
}

SvDevicesWindow::~SvDevicesWindow()
{
  
}

void SvDevicesWindow::on_bnEditDevice_clicked()
{
  QString currentDeviceName = model->data(model->index(table->selectionModel()->currentIndex().row(), 0)).toString();
 
  DEV_UI = new SvDevice(this, currentDeviceName, SvDevice::smEdit);
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvDevicesWindow::doubleClicked(QModelIndex mi)
{
  on_bnEditDevice_clicked();
}

