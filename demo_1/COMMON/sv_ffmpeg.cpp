#include "sv_ffmpeg.h"
#include "tthread.h"

//#include "log.h"

//using namespace log_ns;

extern "C"
{
    #define __STDC_CONSTANT_MACROS
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/mathematics.h"
    #include "libavutil/mem.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
    #include "libavutil/log.h"
//#include "libavutil/timestamp.h"
}

#undef main;

//static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt, const char *tag);

QPushButton *bnStop;
QPushButton *bnSettings;
QPushButton *bnSaveFrame;
  TThread* tth;

SvFFMpegWidget::SvFFMpegWidget(int index,
                               QString media_path,
                               int width,
                               int height,
                               int posX,
                               int posY,
                               QString caption,
                               int delay,
                               QString path_to_save_frames)
{
//  this->setParent(parent);
  this->setGeometry(posX, posY, width + 4, height + 4);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  this->img = QImage(width, height, QImage::Format_RGBX8888);
  this->caption = caption;
  this->index = index;
  this->media_path = media_path;
      
  QIcon icon;
  
  /* кнопка стоп */
//  bnStop = new QPushButton(this);
//  bnStop->setObjectName(QStringLiteral("bnStop1"));
//  bnStop->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//  bnStop->setMinimumSize(QSize(18, 18));
//  bnStop->setMaximumSize(QSize(18, 18));
//  bnStop->setGeometry(4, 4, 18, 18);
  
//  icon.addFile(QStringLiteral(":/icons/Icons/png2ico/cross.ico"),
//               QSize(16, 16),
//               QIcon::Normal,
//               QIcon::Off);
//  bnStop->setIcon(icon);
//  bnStop->show();
  
//  /* кнопка настройки */
//  bnSettings = new QPushButton(this);
//  bnSettings->setObjectName(QStringLiteral("bnSettings1"));
//  bnSettings->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//  bnSettings->setMinimumSize(QSize(18, 18));
//  bnSettings->setMaximumSize(QSize(18, 18));
//  bnSettings->setGeometry(24, 4, 18, 18);
////  QIcon icon;
//  icon.addFile(QStringLiteral(":/icons/Icons/google/Gears.bmp"),
//               QSize(16, 16),
//               QIcon::Normal,
//               QIcon::Off);
//  bnSettings->setIcon(icon);
//  bnSettings->show();
  
//  /* кнопка сделать снимок */
//  bnSaveFrame = new QPushButton(this);
//  bnSaveFrame->setObjectName(QStringLiteral("bnSaveFrame1"));
//  bnSaveFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//  bnSaveFrame->setMinimumSize(QSize(18, 18));
//  bnSaveFrame->setMaximumSize(QSize(18, 18));
////  bnSettings->setText("X");
//  bnSaveFrame->setGeometry(44, 4, 18, 18);
//  bnSaveFrame->setIcon(QIcon(":/icons/Icons/png2ico/disk.ico"));
//  bnSaveFrame->show();
  
//  connect(bnStop, SIGNAL(clicked()), SIGNAL(sigStop()));
//  connect(this, SIGNAL(sigStop()), this, SLOT(slotStop()));
  
//  connect(bnSettings, SIGNAL(pressed()), SIGNAL(sigSettings()));
//  connect(this, SIGNAL(sigSettings()), this, SLOT(slotSettings())); 
  
//  connect(bnSaveFrame, SIGNAL(clicked()), SIGNAL(sigSaveFrame()));
//  connect(this, SIGNAL(sigSaveFrame()), this, SLOT(slotSaveFrame()));   
  
//  tth = new TThread(30);
//  connect(tth, SIGNAL(progressed()), this, SLOT(repaint()));
  
  img_size = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 4;
//  uint header_size = sizeof(BITMAPFILEHEADER);
//  uint info_size = sizeof(BITMAPINFOHEADER);
//  uint frame_size = w * h * 4;
  
  connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(slotClicked(QMouseEvent*))); 
  
  this->_img = malloc(img_size);
  
  ffmpg = new Svffmpeg(media_path, this->_img, width, height, delay, path_to_save_frames);
  connect(ffmpg, QThread::finished, ffmpg, &QObject::deleteLater);
  connect(ffmpg, SIGNAL(sigImgLoaded()), this, SLOT(repaint()));
  ffmpg->start();
  
  this->repaint(); // paintEvent(0);
  
//  tth->start();
}

SvFFMpegWidget::~SvFFMpegWidget()
{
  ffmpg->stop();
  while(!ffmpg->isFinished()) QApplication::processEvents();
//  qDebug() << "ffmpg->isFinished()";
  
  free(this->_img);
  this->deleteLater();
}

void SvFFMpegWidget::slotClicked(QMouseEvent *event)
{
  emit clicked(this->index);
}

void SvFFMpegWidget::paintEvent(QPaintEvent *event)
{
  if(!ffmpg->isPlaying()) return;
  
  if(ffmpg->isConnecting)
  {
    QPainter painter(this);
    
    QPen pp;
    pp.setStyle(Qt::SolidLine);
    
    pp.setColor(Qt::gray);
    pp.setWidth(2);
    painter.setPen(pp);
    painter.drawRects(new QRect(0, 0, this->width() - 1, this->height() - 1), 1);
    
    pp.setColor(Qt::black);
    painter.setPen(pp);
    
    QFont fnt;
    fnt.setBold(true);
    fnt.setPixelSize(14);
    
    painter.setFont(fnt);
    
    painter.drawText(4,
                     4,
                     this->width() - 12,
                     this->height() - 12,
                     Qt::AlignCenter | Qt::AlignCenter | Qt::TextWordWrap,
                     "Connecting to " + this->media_path);
    return;
  }
  
  if(!this->img.loadFromData((const uchar*)(_img), img_size))
    return;
  
  QPainter painter(this);
  painter.drawImage(2, 2, img);

  
  QPen pp;
  pp.setStyle(Qt::SolidLine);
  
  if(drawRect)
  {
    pp.setColor(Qt::magenta);
    pp.setWidth(2);
    painter.setPen(pp);
    painter.drawRects(new QRect(1, 1, this->width() - 2, this->height() - 2), 1);
  }
//  else
  
  pp.setColor(Qt::white);
  painter.setPen(pp);
  
  QFont fnt;
  fnt.setBold(true);
  fnt.setPixelSize(14);
  
  painter.setFont(fnt);
  
  painter.drawText(4,
                   4,
                   this->width() - 12,
                   this->height() - 12,
                   Qt::AlignBottom | Qt::AlignCenter | Qt::TextWordWrap,
                   this->caption);

  
}

void SvFFMpegWidget::slotStop()
{

}

void SvFFMpegWidget::mouseDoubleClickEvent(QMouseEvent *)
{
  if(ffmpg)
  {
    this->setGeometry(this->x(), this->y(), 640, 480);
    ffmpg->img_width = 640;
    ffmpg->img_height = 480;
  }
}

void SvFFMpegWidget::slotSettings()
{

}

void SvFFMpegWidget::slotSaveFrame()
{
  if(ffmpg) ffmpg->saveframe = true;
}

/**************************************************************************/

Svffmpeg::Svffmpeg(QString media_path,
                   void* _img,
//                      QImage *img,
                   int width,
                   int height,
                   int delay,
                   QString path_to_save_frames)

{
  this->media_path = media_path;
  this->delay = delay;
  this->_img = _img;
  this->img_width = width;
  this->img_height = height;
  this->path_to_save_frames = path_to_save_frames;
}

Svffmpeg::~Svffmpeg()
{
  this->deleteLater();
}

void Svffmpeg::run()
{
  int err;

  AVCodecContext* codec_context;
  AVCodec* codec;
  AVFormatContext* avfc = NULL;

  int video_stream;
  SwsContext *img_convert_ctx;
  
  AVFrame *origin_frame; // исходный кадр
  AVFrame *scaled_frame; // кадр после преобразования формата и размера
  AVPacket packet; 
  
  av_register_all();
//  av_log_set_level(AV_LOG_QUIET);
  
  /* allocate the output media context */
/*
  AVFormatContext *oc;
  avformat_alloc_output_context2(&oc, NULL, NULL, media_path.toUtf8());
  if (!oc) {
    qDebug() << QString("FFMpeg: Unable to avformat_alloc_output_context2: %1\n").arg(media_path);
    avformat_alloc_output_context2(&oc, NULL, "mpeg", media_path.toUtf8());
  }
  if (!oc) {
    qDebug() << QString("FFMpeg: Unable mpeg: %1\n").arg(media_path);
    return;
  }
*/
  
  /* подключаемся к источнику видео */
  err = avformat_open_input(&avfc, media_path.toUtf8(), NULL, NULL);
  if (err < 0)
  {
    qDebug() << QString("FFMpeg: Unable to open: %1\n").arg(media_path);
    return;
  }
//  else qDebug() << QString("open input OK %1").arg(media_path);

  /* ищем информацию о потоке мультимедиа  */
  err = avformat_find_stream_info(avfc, NULL);
  if (err < 0)
  {
    qDebug() << "FFMpeg: Unable to find stream info\n";
    return;
  }
  else qDebug() << "find stream info OK";

  
  /*  */
//  av_dump_format(avfc, 0, media_path.toUtf8(), 0);
  
  /* ищем первый видеопоток в потоке мультимедиа */
  for (video_stream = 0; video_stream < avfc->nb_streams; ++video_stream)
  {
    if (avfc->streams[video_stream]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
      break;
  }
  
  /* если ни один видео поток не найден, то выходим */
  if (video_stream == avfc->nb_streams)
  {
      qDebug() << "FFMpeg: Unable to find video stream\n";
      return;
  }
  else qDebug() << QString("find video stream OK %1  avfc->nb_streams %2").arg(video_stream).arg(/*vdthr->*/avfc->nb_streams);
  
  /* создаем контекст кодека для выбранного видеопотока, ищем декодер и открываем его */
  codec_context = avfc->streams[video_stream]->codec;
  
  /* ищем и открываем декодер */
  codec = avcodec_find_decoder(codec_context->codec_id);
  err = avcodec_open2(codec_context, codec, NULL);
  if (err < 0)
  {
    qDebug() << "FFMpeg: Unable to open codec\n";
    quit();
  }
    
//  else qDebug() << QString(codec->name) + " open codec OK";
/* ЙУХХХХХХХУУУУУУ!!!!!!!!!!!!!*/
  /*********************************************************/
  
  int w = this->img_width  == 0 ? codec_context->width  : this->img_width;
  int h = this->img_height == 0 ? codec_context->height : this->img_height;
  
  
  img_convert_ctx = 0;
  
  /* готовим буферы для кадров */
  origin_frame = avcodec_alloc_frame();
  scaled_frame = avcodec_alloc_frame();
  
  avpicture_fill((AVPicture *)scaled_frame,  /*AV_PIX_FMT_YUVJ420P */
                 new uint8_t[avpicture_get_size(AV_PIX_FMT_RGB32, w, h)],
                 AV_PIX_FMT_RGB32, //  AV_PIX_FMT_YUVJ420P  AV_PIX_FMT_RGB32 
                 w,
                 h);

  /* определяем переменные для работы с буфером bmp */
  uint header_size = sizeof(BITMAPFILEHEADER);
  uint info_size = sizeof(BITMAPINFOHEADER);
  uint frame_size = w * h * 4;
  
  /* готовим буфер для формирования bmp */
//  uchar* bmpBuf = reinterpret_cast<uchar*>(malloc(header_size + info_size + frame_size));
  
  /* формируем заголовок bmp */
  BITMAPFILEHEADER bmpheader;
  bmpheader.bfReserved1 = 0;
  bmpheader.bfReserved2 = 0;
  bmpheader.bfOffBits = header_size + info_size;
  bmpheader.bfSize = bmpheader.bfOffBits + frame_size;
  bmpheader.bfType = 0x4d42;
  
  // create bmp info
  BITMAPINFO bmpinfo;
  bmpinfo.bmiHeader.biSize = info_size;
  bmpinfo.bmiHeader.biWidth = w;
  bmpinfo.bmiHeader.biHeight = -h;
  bmpinfo.bmiHeader.biPlanes = 1;
  bmpinfo.bmiHeader.biBitCount = 32;
  bmpinfo.bmiHeader.biCompression = BI_RGB; // ;BI_JPEG
  bmpinfo.bmiHeader.biSizeImage = 0;
  bmpinfo.bmiHeader.biXPelsPerMeter = 100;
  bmpinfo.bmiHeader.biYPelsPerMeter = 100;
  bmpinfo.bmiHeader.biClrUsed = 0;
  bmpinfo.bmiHeader.biClrImportant = 0;
  
  /* пишем заголовок в буфер bmp */
  memcpy(this->_img, &bmpheader, header_size);
  memcpy(this->_img + header_size, &bmpinfo.bmiHeader, info_size);
   
  isConnecting = false;
  
  while (_playing & (av_read_frame(avfc, &packet) >= 0))
  {
    
    if (packet.stream_index == video_stream)
    {
      int frame_finished;
      
      avcodec_decode_video2(codec_context, origin_frame, &frame_finished, &packet);

      if (frame_finished)
      {
        /* преобразуем кадр в формат bmp и к нужному размеру */
        img_convert_ctx = sws_getCachedContext(img_convert_ctx,
                                               codec_context->width,
                                               codec_context->height,
                                               codec_context->pix_fmt,
                                               w,
                                               h,
                                               AV_PIX_FMT_RGB32, /*AV_PIX_FMT_YUVJ420P,*/
                                               SWS_BICUBIC, // BICUBIC,
                                               NULL,
                                               NULL,
                                               NULL);
        
        sws_scale(img_convert_ctx,
                  origin_frame->data,
                  origin_frame->linesize,
                  0,
                  codec_context->height,
                  scaled_frame->data,
                  scaled_frame->linesize);

        /* пишем кадр в буфер bmp */
        memcpy(this->_img + header_size + info_size, scaled_frame->data[0], frame_size);
        
        emit this->sigImgLoaded();
        
        if(saveframe)
        {
          QString filename;
          filename = path_to_save_frames + QString("%1").arg(QDateTime::currentDateTime().toString("ddMMyy_hhmmss.zzz")) + ".bmp";

          FILE *fout;
          fout = fopen(filename.toUtf8(), "wb");
          fwrite( this->_img, header_size + info_size + frame_size, 1, fout);
          fclose( fout );
          qDebug() <<  "frame saved: " << filename;
          saveframe = false;
        }
        
        /************************************************/

        msleep(delay);

      }

      av_free_packet(&/*vdthr->*/packet); 
    }
  }
  
  avformat_close_input(&avfc);
  avformat_free_context(avfc);
  
  avcodec_free_context(&codec_context);
  avcodec_free_frame(&origin_frame); 
  avcodec_free_frame(&scaled_frame); 
  
  av_free(codec);
  av_free(img_convert_ctx);
    
  //  free(bmpBuf);
  free(&bmpinfo);
  free(&bmpheader);
  
  qDebug() <<  "finished";
    
  //  quit();
//  exec();
}

