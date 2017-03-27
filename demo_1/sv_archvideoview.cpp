#include "sv_archvideoview.h"
#include "./COMMON/sql_select_defs.h"
#include "./COMMON/sv_pgdb.h"
#include "../demo_1/sv_videoviewwindow.h"

SvArchVideoView* ARCHVIDEO_WINDOW_UI;
extern SvPGDB* PGDB;
extern SvSingleVideoWindow* SINGLEVIDEO_UI;

SvArchVideoView::SvArchVideoView(QMdiArea* parent,
                                 QString title) : 
  QWidget(parent),
  p_model(new QSqlQueryModel(this))
{
  this->setObjectName(QStringLiteral(ARCHVIDEO_SUBWINDOW_NAME));
  this->setParent(parent);
  this->setWindowTitle(title);
  parent->addSubWindow(this);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  QVBoxLayout* vlay = new QVBoxLayout(this);
  vlay->setParent(this);
  vlay->setSpacing(2);
  vlay->setContentsMargins(2, 2, 2, 2);
  vlay->setObjectName(QStringLiteral("vlay"));
  
  table = new QTableView(this);
  table->setParent(this);
  table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  table->setObjectName(QStringLiteral("tbl_devices"));
//  table->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  vlay->addWidget(table);
  
  setTable();
  
  connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotTableDoubleClicked(QModelIndex)));
  
}

SvArchVideoView::~SvArchVideoView()
{
  
}

int SvArchVideoView::setTable()
{
  QSqlError err = PGDB->execSQL(D_SELECT_ARHC_VIDEO_LIST, p_model);
  if(err.type() != QSqlError::NoError) return -1;
  
  table->setModel(p_model);
  
  QStringList headers = QString(D_ARCHVIDEO_COLUMN_LIST).split(';');
  
  for(int i = 0; i < headers.count(); i++)
  {
    p_model->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
    table->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
    table->setColumnWidth(i, 180);
  }

  return 0;
  
}

void SvArchVideoView::slotTableDoubleClicked(QModelIndex mi)
{
  int id = p_model->data(p_model->index(table->selectionModel()->currentIndex().row(), 0)).toInt();
  
  QSqlQuery* q = new QSqlQuery(PGDB->db);
  QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_ARHC_VIDEO_WHERE).arg("arch_video.id").arg(id), q);
  
  q->first();
  
  SINGLEVIDEO_UI = new SvSingleVideoWindow(q->value("file_name").toString(),
                                           QString("Архив <%1>. Начало %2 Конец %3")
                                             .arg(q->value("device_name").toString())
                                             .arg(q->value("record_begin").toDateTime().toString("dd.MM.yy hh:mm:ss"))
                                             .arg(q->value("record_end").toDateTime().toString("dd.MM.yy hh:mm:ss")),
                                           "Видео: " + q->value("file_name").toString(),
                                           800,
                                           600);
  q->finish();
  free(q);
  
}
