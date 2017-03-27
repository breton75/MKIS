#include "sv_videoviewwindow.h"
#include "./COMMON/sv_settings.h"
#include "./COMMON/sv_ffmpeg.h"
#include "./COMMON/sv_pgdb.h"

SvSettings* vvsett;
SvFFMpegWidget* player;
SvSingleVideoWindow* SINGLEVIDEO_UI;

extern SvPGDB* PGDB;
 
QMap<int, SvFFMpegWidget*> vwm;
//QMap<int, QThread*> vwthr;
//QMutex *mutex;

int posx = 0;
int posy = 0;
int indx = 0;

SvVideoViewWindow::SvVideoViewWindow(QMdiArea *parent,
                                     QString title,
                                     int width,
                                     int height)
{
//  QTextCodec * codec = QTextCodec::codecForName("UTF-8");
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  
  this->setObjectName(QStringLiteral("videoViewWindow"));
  this->setParent(parent);
  this->setWindowTitle(title);
  this->setGeometry(100, 100, width, height);
  
  
  
  QPalette palette;
  QBrush brush(QColor(0, 0, 0, 255));
  brush.setStyle(Qt::SolidPattern);
  palette.setBrush(QPalette::Active, QPalette::Base, brush);
  palette.setBrush(QPalette::Active, QPalette::Window, brush);
  palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
  palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
  palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
  palette.setBrush(QPalette::Disabled, QPalette::Window, brush);  
  
//  this->setPalette(palette);
  
  QVBoxLayout* vlay3 = new QVBoxLayout(this);
  vlay3->setSpacing(6);
  vlay3->setContentsMargins(11, 11, 11, 11);
  vlay3->setObjectName(QStringLiteral("vlay3"));
  
  QHBoxLayout* hlay = new QHBoxLayout();
  hlay->setSpacing(6);
  hlay->setObjectName(QStringLiteral("hlay"));
  
  QLabel* lblCameraList = new QLabel(this);
  lblCameraList->setObjectName(QStringLiteral("lblCameraList"));
  
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(lblCameraList->sizePolicy().hasHeightForWidth());
  lblCameraList->setSizePolicy(sizePolicy);
  lblCameraList->setText("Список видеокамер ");
  hlay->addWidget(lblCameraList);

  cbCameraList = new QComboBox(this);
  cbCameraList->setObjectName(QStringLiteral("cbCameraList"));
  QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(cbCameraList->sizePolicy().hasHeightForWidth());
  cbCameraList->setSizePolicy(sizePolicy1);
  cbCameraList->setMinimumSize(QSize(200, 0));

  hlay->addWidget(cbCameraList);

  bnPlay = new QPushButton(this);
  bnPlay->setObjectName(QStringLiteral("bnPlay"));
  QIcon icon9;
  icon9.addFile(QStringLiteral("../../Common/Icons/16x16freeapplicationicons/ico/Play.ico"), QSize(), QIcon::Normal, QIcon::Off);
  bnPlay->setIcon(icon9);

  hlay->addWidget(bnPlay);

  QSpacerItem* spacer1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

  hlay->addItem(spacer1);

  vlay3->addLayout(hlay);

  widgetVideo = new QWidget(this);
  widgetVideo->setObjectName(QStringLiteral("widgetVideo"));
  QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(widgetVideo->sizePolicy().hasHeightForWidth());
  widgetVideo->setSizePolicy(sizePolicy2);
  widgetVideo->setPalette(palette);
  
  vlay3->addWidget(widgetVideo);

  parent->addSubWindow(this);
  
/****************************************/
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_DEVICES_WHERE_2).arg("device_class").arg("'Видеокамера'"), q);
  
  if(!q->size()) return;
  
  paths = new QStringList();
  
  while(q->next())
  {
    cbCameraList->addItem(q->value("device_name").toString());
    paths->append(q->value("video_path").toString());
  }
  
//  QString s = QApplication::applicationDirPath() + "/ini/" + "view_cameras.ini";
//  vvsett = new SvSettings(s);
  
//  QStringList lst = vvsett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
//  {
//    s = vvsett->readValue(lst.at(i), "camera", "").toString();
//    cbCameraList->addItem(s.section('%', 1, 1));
//  }
  cbCameraList->setCurrentIndex(0);

  connect(bnPlay, SIGNAL(clicked()), this, SLOT(slotPlay()));  
  
//  mutex = new QMutex();
  
}

SvVideoViewWindow::~SvVideoViewWindow()
{
  foreach (SvFFMpegWidget* var, vwm.values())
  {
    var->~SvFFMpegWidget();  
  }
}

void SvVideoViewWindow::slotPlay()
{

  QString s = cbCameraList->currentText();
  QString link = paths->at(cbCameraList->currentIndex()); // s.section('%', 2, 2);
  
  int w = 480;
  int h = 360;

  if(posx + w > this->width())
    {
      posx = 0;
      posy = posy + h + 2;
    }
  
//  qDebug() << "2: posx + w=" << posx + w << "posy=" << posy << "width=" << this->width();
  vwm.insert(vwm.constEnd(), indx, new SvFFMpegWidget(indx,
                                                      link,
                                                      w,
                                                      h,
                                                      posx,
                                                      posy,
                                                      s,
                                                      link.left(4) == "rtsp" ? 0 : 40));
  vwm.value(indx)->setParent(widgetVideo);
  vwm.value(indx)->show();
  
  connect(vwm.value(indx), SIGNAL(clicked(int)), this, SLOT(slotVideoClick(int)));
  
  indx++;
  posx = posx + w + 2;

}

void SvVideoViewWindow::slotVideoClick(int index)
{
//  qDebug() << "clicked index 22 =" << index;
//  vwm.value(index)->setDrawRect(true);
  
  for(int i = 0; i < vwm.count(); i++) 
    vwm.value(i)->setDrawRect(index == vwm.value(i)->index);
}

/****************************************************/
SvSingleVideoWindow::SvSingleVideoWindow(QString link,
                                         QString device_name,
                                         QString title,
                                         int width,
                                         int height)
{
  this->setWindowTitle(title);
  this->resize(QSize(width, height));
  vlay = new QVBoxLayout(this);
  
  ffm = new SvFFMpegWidget(0,
                           link,
                           width,
                           height,
                           0,
                           0,
                           device_name,
                           link.left(4) == "rtsp" ? 0 : 40);
  ffm->setParent(this);
  vlay->addWidget(ffm);
  ffm->show();
  
//  connect(this, SIGNAL(rejected()), this, SLOT(on_reject()));
  
  this->setModal(true);
  this->show();
  
}

SvSingleVideoWindow::~SvSingleVideoWindow()
{
  ffm->~SvFFMpegWidget();
  close();
  deleteLater();
}
