#include "sv_rls2bitwidget.h"

#include "./COMMON/sv_settings.h"
#include "../demo_1/COMMON/sv_pgdb.h"

SvSingleRlsWindow* SINGLERLS_UI;
SvSelectRlsArchWindow* SELECT_RSL_ARCH_UI;
extern SvPGDB* PGDB;

SvRls2BitWidget::SvRls2BitWidget(quint16 port,
                                 QString caption,
                                 int window_width,
                                 int window_height,
                                 int img_resolution,
                                 int draw_points_per_line,
                                 QImage* background)
{
//  this->setParent(parent);
  this->resize(window_width, window_height);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
//  graphicsView = new GraphicsView(this);
//  graphicsView->setRenderHint(QPainter::Antialiasing, false);
//  graphicsView->setDragMode(QGraphicsView::NoDrag); //RubberBandDrag);
//  graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
//  graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
//  graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  
//  QVBoxLayout* vlay = new QVBoxLayout(this);
//  vlay->setSpacing(0);
//  vlay->setObjectName(QStringLiteral("vlay"));
//  vlay->addWidget(graphicsView);
  
  this->draw_points_per_line = draw_points_per_line;
  this->img_resolution = img_resolution;
  this->img = QImage(img_resolution, img_resolution, QImage::Format_RGB888);
  this->caption = caption;
  this->background = background;

//  currentPix = new QPixmap::fromImage(this->img);

  _buffer = malloc(AZIMUTHS_COUNT * 1024);
  memset(_buffer, char(0), AZIMUTHS_COUNT * 1024);

  angle = double(2 * M_PI) / double(AZIMUTHS_COUNT);

  timer.setInterval(30);
  timer.setSingleShot(false);
  connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
  timer.start();
  
  rls = new SvRlsDataBuffering(_buffer,
                               port,
                               this);
  
  connect(rls, QThread::finished, rls, &QObject::deleteLater);
//  connect(rls, QThread::finished, this, SLOT(close());
  connect(rls, SIGNAL(lineUpdated(int)), this, SLOT(drawLine(int)));
  rls->start();
  
  
}

SvRls2BitWidget::~SvRls2BitWidget()
{
  timer.stop();
//  rls->stop();
//  while(rls->isPlaying()) QApplication::processEvents();
//  while(!rls->isFinished()) QApplication::processEvents();
  rls->deleteLater();
//  free(this->_img);
  free(this->_buffer);
  this->deleteLater();
}

bool SvRls2BitWidget::isPlaying()
{
  return rls->isPlaying(); 
}

void SvRls2BitWidget::drawLine(int lineNum)
{
  void* d;
  d = _buffer + lineNum * 1024;
  
  // угол 
  double a = double(0.5 * M_PI) + angle * double(lineNum);
  
  // угол для индикатора
  double ind1 = double(0.5 * M_PI) + angle * double(lineNum + 1);
  
  for(int i = 0; i < draw_points_per_line; i++)
  {
    int x = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * cos(a);
    int y = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * sin(a);
    
    quint8* v = (quint8*)(d + i);
    if(*v < 0x55)
    {
//      if(background) img.setPixel(x, y, background->pixel(x, y));
//      else 
      img.setPixel(x, y, qRgb(3, 98, 155));
    }
    else if(*v < 0xAA) img.setPixel(x, y, qRgb(255, 255, 50));
    else if(*v < 0xFF) img.setPixel(x, y, qRgb(255, 255, 150));
    else img.setPixel(x, y, qRgb(255, 255, 0));
    
    // индикатор
    x = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * cos(ind1);
    y = img_resolution / 2 - double(i * img_resolution) / draw_points_per_line / 2 * sin(ind1);
    img.setPixel(x, y, qRgb(255, 100, 30));
       
  }
//  this->repaint();
  
}

void SvRls2BitWidget::paintEvent(QPaintEvent *event)
{
  if(!rls->isPlaying()) return;

  QPainter painter(this);
  painter.drawImage(0, 0, img);
}

void SvRls2BitWidget::stop()
{ 
  rls->stop(); 
}

//void SvRls2BitWidget::setupMatrix(qreal scaleXY)
//{
//  qreal scale; 
//  if(scaleXY) scale = scaleXY;
//  else scale= qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

//  QMatrix matrix;
//  matrix.scale(scale, scale);
////  matrix.rotate(rotateSlider->value());

//  graphicsView->setMatrix(matrix);
//}

/** *******  данные от РЛС  ************ **/
SvRlsDataBuffering::SvRlsDataBuffering(void *buffer,
                                       quint16 port,
                                       QObject *parent) 
{
  this->setParent(parent);
  
//  this->ip = ip;
  this->port = port;
  this->buffer = buffer;
//  this->linesCount = linesCount;
//  this->firstLineNum = firstLineNum;
//  this->lastLineNum = lastLineNum;
//  this->pointPerLine = pointPerLine;
//  this->bitPerPoint = bitPerPoint;
}

SvRlsDataBuffering::~SvRlsDataBuffering()
{
  this->deleteLater();
}

void SvRlsDataBuffering::run()
{
  _playing = true;
  
//  QUdpSocket* 
  socket = new QUdpSocket();
  socket->bind(port);
  
  void* datagram = malloc(0xFFFF); // максимальный возможный размер датаграммы
  
  Header2bit* header = new Header2bit;
  Line2bit* line_head = new Line2bit;
  
  void* line_data;

//  QFile file("e:/out2.rls");
//  if (!file.open(QIODevice::WriteOnly))
//    return;
//  QDataStream out(&file);

  qint64 datagram_size;
  qint64 aval;
  int offset = 0;

  while(_playing)
  {
    while (socket->waitForReadyRead(1))
    {
      while(socket->hasPendingDatagrams())
      {
        datagram_size = socket->pendingDatagramSize();
//        aval = socket->bytesAvailable();
        if(datagram_size <= 0) continue;
  
        socket->readDatagram((char*)(datagram), datagram_size);
        
        memcpy(header, datagram, Header2bitSize);
        offset = Header2bitSize;
        
        while(offset < datagram_size)
        {
          memcpy(line_head, datagram + offset, Line2bitHeaderSize);
          offset += Line2bitHeaderSize;
          
          int line_data_size = line_head->lineLen - Line2bitHeaderSize;
          line_data = datagram + offset; // указатель на начало данных текущей линейки
          
          offset += line_data_size; // передвигаем указатель на следующую линейку
          
          line_head->lineNum = line_head->lineNum & 0xFFFF;
          
//          qDebug() << "line_num=" << line_head->lineNum
//                   << "line_data_size=" << line_data_size;

          int i = 0;
          int cnt = 0;
          void* data = buffer + line_head->lineNum * 1024;
          while(i < line_data_size)
          {
            quint8* ch = (quint8*)(line_data + i);
            
            switch (*ch)
            {
              case 0x01:
                cnt += 1; // если ноль, то ничего не делаем. в массиве уже нули
                  i += 1;
//                  qDebug() << "case 0x01:" << "data + cnt * 4=" << cnt * 4;
                break;
                
              case 0x54:
              case 0xA9:
              case 0xFE:  
                *ch += 1;
                memset(data + cnt, *ch, 1);
                cnt += 1;
                  i += 1;
//                  qDebug() << "case 0x54:" << "data + cnt * 4=" << cnt * 4;
                break;
                
              case 0x00:
              case 0x55:
              case 0xAA:
              case 0xFF:
              {
                quint8* c = (quint8*)(line_data + i + 1);
                memset(data + cnt, *ch, *c);
                cnt += *c;
                  i += 2;
//                  qDebug() << "case 0x00:" << "c=" << int(*c) << "data + cnt * 4=" << cnt * 4;
                break;
              }
                
              default:
              {
                memset(data + cnt, *ch, 1);
                cnt += 1;
                  i += 1;
//                  qDebug() << "case dflt:" << "data + cnt * 4=" << cnt * 4 ;
                break;
              }
            }
          }

           emit lineUpdated(line_head->lineNum);
          
        }
      }
    }
  }
  
  free(datagram);
  socket->close();
  _playing = false;  
  qDebug() << "finished";  
}


/****************************************************/
SvSingleRlsWindow::SvSingleRlsWindow(quint16 port,
                                     QString device_name,
                                     QString title,
                                     int width,
                                     int height)
{
  this->setWindowTitle(title);
  this->resize(QSize(width, height));
  vlay = new QVBoxLayout(this);

  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  SvSettings *sett = new SvSettings(s, this);

//  debug = sett->readValue("RLS", "debug", false).toBool();
  
  rls = new SvRls2BitWidget(port,
                            title,
                            sett->readValue("RLS", "Width", 640).toInt(),
                            sett->readValue("RLS", "Height", 640).toInt(),
                            sett->readValue("RLS", "Resolution", 640).toInt(),
                            sett->readValue("RLS", "Draw radius", 1024).toInt());
  rls->setParent(this);
  vlay->addWidget(rls);
  rls->show();
  
//  connect(this, SIGNAL(rejected()), this, SLOT(on_reject()));
  
  this->setModal(true);
  this->show();
  
}

SvSingleRlsWindow::~SvSingleRlsWindow()
{

  rls->~SvRls2BitWidget();
  
  close();
  deleteLater();
}

void SvSingleRlsWindow::reject()
{
  rls->stop();
  while(rls->isPlaying()) QApplication::processEvents();
  
  QDialog::reject();
      
}


/****************************************************/
SvSelectRlsArchWindow::SvSelectRlsArchWindow()
{
  vlay_2 = new QVBoxLayout(this);
  vlay_2->setObjectName(QStringLiteral("vlay_2"));
  groupBox = new QGroupBox(this);
  groupBox->setObjectName(QStringLiteral("groupBox"));
  vlay = new QVBoxLayout(groupBox);
  vlay->setObjectName(QStringLiteral("vlay"));
  
  hlayDevice = new QHBoxLayout();
  hlayDevice->setObjectName(QStringLiteral("hlayDevice"));
  
  lblDevice = new QLabel(groupBox);
  lblDevice->setObjectName(QStringLiteral("lblDevice"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(lblDevice->sizePolicy().hasHeightForWidth());
  lblDevice->setSizePolicy(sizePolicy);
  lblDevice->setMinimumSize(QSize(75, 0));
  lblDevice->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  lblDevice->setText("РЛС");
  hlayDevice->addWidget(lblDevice);
 
  cbDevice = new QComboBox(groupBox);
  cbDevice->setObjectName(QStringLiteral("cbDevice"));
  hlayDevice->addWidget(cbDevice);
 
  /*************************************/
  hlayServer = new QHBoxLayout();
  hlayServer->setObjectName(QStringLiteral("hlayServer"));
  
  lblIP = new QLabel(groupBox);
  lblIP->setObjectName(QStringLiteral("lblIP"));
  QSizePolicy sizePolicy11(QSizePolicy::Fixed, QSizePolicy::Preferred);
  sizePolicy11.setHorizontalStretch(0);
  sizePolicy11.setVerticalStretch(0);
  sizePolicy11.setHeightForWidth(lblIP->sizePolicy().hasHeightForWidth());
  lblIP->setSizePolicy(sizePolicy11);
  lblIP->setMinimumSize(QSize(75, 0));
  lblIP->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  lblIP->setText("Сервера");
  hlayServer->addWidget(lblIP);
 
  editIP = new QLineEdit(groupBox);
  editIP->setObjectName(QStringLiteral("editIP"));
  editIP->setText("169.254.1.1");
  hlayServer->addWidget(editIP); 
  
  lblPort = new QLabel(groupBox);
  lblPort->setObjectName(QStringLiteral("lblPort"));
  QSizePolicy sizePolicy12(QSizePolicy::Fixed, QSizePolicy::Preferred);
  sizePolicy12.setHorizontalStretch(0);
  sizePolicy12.setVerticalStretch(0);
  sizePolicy12.setHeightForWidth(lblPort->sizePolicy().hasHeightForWidth());
  lblPort->setSizePolicy(sizePolicy12);
  lblPort->setMinimumSize(QSize(25, 0));
  lblPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  lblPort->setText("Порт");
  hlayServer->addWidget(lblPort);
  
  sbPort = new QSpinBox(groupBox);
  sbPort->setObjectName(QStringLiteral("sbPort"));
  sbPort->setMaximum(65535);
  sbPort->setValue(35000);
  hlayServer->addWidget(sbPort);

  /*****************************************/
  
  hlayBegin = new QHBoxLayout();
  hlayBegin->setObjectName(QStringLiteral("hlayBegin"));
  lblBegin = new QLabel(groupBox);
  lblBegin->setObjectName(QStringLiteral("lblBegin"));
  sizePolicy.setHeightForWidth(lblBegin->sizePolicy().hasHeightForWidth());
  lblBegin->setSizePolicy(sizePolicy);
  lblBegin->setMinimumSize(QSize(75, 0));
  lblBegin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  lblBegin->setText("Начало");
  hlayBegin->addWidget(lblBegin);
 
  dtBegin = new QDateTimeEdit(groupBox);
  dtBegin->setObjectName(QStringLiteral("dtBegin"));
  hlayBegin->addWidget(dtBegin);
 
  hlayEnd = new QHBoxLayout();
  hlayEnd->setObjectName(QStringLiteral("hlayEnd"));
  lblEnd = new QLabel(groupBox);
  lblEnd->setObjectName(QStringLiteral("lblEnd"));
  sizePolicy.setHeightForWidth(lblEnd->sizePolicy().hasHeightForWidth());
  lblEnd->setSizePolicy(sizePolicy);
  lblEnd->setMinimumSize(QSize(75, 0));
  lblEnd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
  lblEnd->setText("Окончание");
  hlayEnd->addWidget(lblEnd);
 
  dtEnd = new QDateTimeEdit(groupBox);
  dtEnd->setObjectName(QStringLiteral("dtEnd"));
  hlayEnd->addWidget(dtEnd);
 
  hlayButtons = new QHBoxLayout();
  hlayButtons->setObjectName(QStringLiteral("hlayButtons"));
  spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  hlayButtons->addItem(spacer);
 
  bnStart = new QPushButton(this);
  bnStart->setObjectName(QStringLiteral("bnStart"));
  bnStart->setText("Старт");
  hlayButtons->addWidget(bnStart);
 
  bnStop = new QPushButton(this);
  bnStop->setObjectName(QStringLiteral("bnStop"));
  bnStop->setText("Стоп");
  bnStop->setEnabled(false);
  hlayButtons->addWidget(bnStop);
  
  vlay->addLayout(hlayDevice);
  vlay->addLayout(hlayServer);
  vlay->addLayout(hlayBegin);
  vlay->addLayout(hlayEnd);
 
  vlay_2->addWidget(groupBox);
  vlay_2->addLayout(hlayButtons);
  
  
  
/*********************************************************/
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  SvSettings *sett = new SvSettings(s, this);
  
//  server_ip = this->editIP->text();
//  server_port = this->sbPort->value();
//  qDebug() << server_ip << server_port;
  server_ip = sett->readValue("SELECT_RLS_ARCH", "ServerIP", "169.254.1.1").toString();
  server_port = sett->readValue("SELECT_RLS_ARCH", "ServerPort", 35000).toInt();
  data_port = sett->readValue("SELECT_RLS_ARCH", "DataPort", 35001).toInt();
  
  rlswdg = new SvRls2BitWidget(data_port, "Архив РЛС");
  rlswdg->setParent(this);
  vlay_2->addWidget(rlswdg);
  rlswdg->show();  
  
  this->resize(640, 780);    
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  PGDB->execSQL("select id, device_name from devices where device_class = 'РЛС'", q);
  
  while(q->next())
  {
    devIdList.append(q->value("id").toInt()); // обязательно, сначала добавляем индекс
    this->cbDevice->addItem(q->value("device_name").toString());
  }
  q->finish();
  free(q);
  

  
  int i = sett->readValue("SELECT_RLS_ARCH", "LastDeviceID", -1).toInt();
  if((i > -1) & (this->cbDevice->count() > i))
    this->cbDevice->setCurrentIndex(i);

  this->dtBegin->setDateTime(QDateTime::fromString(sett->readValue("SELECT_RLS_ARCH", "LastBegin", "24.08.2015 08:30:00").toString(), "dd.MM.yyyy hh:mm:ss"));
  this->dtEnd->setDateTime(QDateTime::fromString(sett->readValue("SELECT_RLS_ARCH", "LastEnd", "24.08.2015 08:30:00").toString(), "dd.MM.yyyy hh:mm:ss"));
  
  connect(this->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(this->bnStop, SIGNAL(pressed()), this,  SLOT(slotStop()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
  
}

SvSelectRlsArchWindow::~SvSelectRlsArchWindow()
{
  this->close();
  this->deleteLater();
}

void SvSelectRlsArchWindow::slotStart()
{
//  rlswdg = new SvRls2BitWidget(data_port, "Архив РЛС");
//  rlswdg->setParent(this);
//  vlay_2->addWidget(rlswdg);
//  rlswdg->show(); 
  
  device_name = this->cbDevice->currentText();
  dateTimeBegin = this->dtBegin->dateTime();
  dateTimeEnd = this->dtEnd->dateTime();
  device_id = devIdList.at(this->cbDevice->currentIndex());
  
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  
  SvSettings *sett = new SvSettings(s, this);
  sett->writeValue("SELECT_RLS_ARCH", "LastDeviceID", this->cbDevice->currentIndex());
  sett->writeValue("SELECT_RLS_ARCH", "LastBegin", this->dtBegin->dateTime().toString("dd.MM.yyyy hh:mm:ss"));
  sett->writeValue("SELECT_RLS_ARCH", "LastEnd", this->dtEnd->dateTime().toString("dd.MM.yyyy hh:mm:ss"));
  
  SvTcpClient* client = new SvTcpClient(server_ip, server_port);
  if(client->connectToHost() != SOCKET_OK) return;
  
  time_t begin = dateTimeBegin.toTime_t();
  time_t end = dateTimeEnd.toTime_t();
  
  QByteArray* b = new QByteArray();
  b->append("TRANSLATE");
  b->append((const char*)(&begin), sizeof(time_t));
  b->append((const char*)(&end), sizeof(time_t));
  b->append((const char*)(&data_port), 2);
  b->append((const char*)(&device_id), 4);
  
  
  client->sendData(b, 2000);
  s = client->responseData.left(2);
  client->disconnectFromHost();
  free(client);
  
  bnStart->setEnabled(false);
  bnStop->setEnabled(true);
  
//  if(s == "OK") QDialog::accept();
//  else QDialog::reject();
  
}

void SvSelectRlsArchWindow::slotStop()
{
  SvTcpClient* client = new SvTcpClient(server_ip, server_port);
  client->connectToHost();
  client->sendData("STOP:TRANSLATE", 2000);
  client->disconnectFromHost();
  free(client);
  
  rlswdg->stop();
  while(rlswdg->isPlaying()) QApplication::processEvents();
//  free(rlswdg);
  
  bnStart->setEnabled(true);
  bnStop->setEnabled(false);
}
