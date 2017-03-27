#include "sv_archscudview.h"
#include "./COMMON/sql_select_defs.h"
#include "./COMMON/sv_pgdb.h"
#include "../demo_1/sv_videoviewwindow.h"

SvArchSCUDView* ARCHSCUD_WINDOW_UI;
extern SvPGDB* PGDB;

SvArchSCUDView::SvArchSCUDView(QMdiArea* parent,
                                 QString title) : 
  QWidget(parent),
  p_model(new QSqlQueryModel(this))
{
  this->setObjectName(QStringLiteral(ARCHSCUD_SUBWINDOW_NAME));
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
  table->setObjectName(QStringLiteral("tbl_archscud"));
//  table->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
  vlay->addWidget(table);
  
  setTable();
  
  connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotTableDoubleClicked(QModelIndex)));
  
}

SvArchSCUDView::~SvArchSCUDView()
{
  
}

int SvArchSCUDView::setTable()
{
  QSqlError err = PGDB->execSQL(D_SELECT_ARHC_SCUD_LIST, p_model);
  if(err.type() != QSqlError::NoError) return -1;
  
  table->setModel(p_model);
  
  QStringList headers = QString(D_ARCHSCUD_COLUMN_LIST).split(';');
  
  for(int i = 0; i < headers.count(); i++)
  {
    p_model->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
    table->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
    table->setColumnWidth(i, 180);
  }

  return 0;
  
}

void SvArchSCUDView::slotTableDoubleClicked(QModelIndex mi)
{

  
}
