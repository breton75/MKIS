#include "sv_zone_list.h"

#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_settings.h"
#include "sv_pgdb.h"

SvZonesList *ZONELIST_UI;
extern SvZone *ZONE_UI;
extern SvPGDB *PGDB;

SvZonesList::SvZonesList(QWidget *parent,
                         bool showEditDelete,
                         bool showNew,
                         bool showSelect) :
  QDialog(parent),
  dlg(new Ui::SvZonesListDialog),
  m_zones_model(new QSqlQueryModel(this))
{
  dlg->setupUi(this);

  zdw = new SvZoneDrawWidget(dlg->widget);
  zdw->setObjectName("zdw");
  zdw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  tblZonesList = new QTableView(dlg->widget);
  tblZonesList->setObjectName("tblZonesList");
  tblZonesList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  
  QSplitter *vSplitter = new QSplitter(Qt::Vertical, this);
  dlg->vlay->addWidget(vSplitter);
  
  vSplitter->addWidget(zdw);
  vSplitter->addWidget(tblZonesList);
  
  tblZonesList->setGeometry(tblZonesList->x(), tblZonesList->y(),
                            tblZonesList->width(), 80);
  
  setZonesListTable();
  
//  dlg->layoutWidget->addWidget(zdw);
  
  dlg->bnEditZone->setVisible(showEditDelete);
  dlg->bnDeleteZone->setVisible(showEditDelete);
  dlg->bnNewZone->setVisible(showNew);
  dlg->bnSelect->setVisible(showSelect);
  
  connect(dlg->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(dlg->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(dlg->bnNewZone, SIGNAL(pressed()), this, SLOT(slotNewZone()));
  connect(dlg->bnEditZone, SIGNAL(pressed()), this, SLOT(slotEditZone()));
  connect(dlg->bnDeleteZone, SIGNAL(pressed()), this, SLOT(slotDeleteZone()));
  
  connect(tblZonesList, SIGNAL(clicked(QModelIndex)), this, SLOT(tableClicked(QModelIndex)));
 
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
}

SvZonesList::~SvZonesList()
{
  zdw->deleteLater();
  this->close();
  delete dlg;
}

void SvZonesList::accept()
{
//  t_zoneName = model->data(model->index(tblZonesList->selectionModel()->currentIndex().row(), 0)).toString();
  
  QSqlRecord r = m_zones_model->record(tblZonesList->currentIndex().row());
  
  t_id = r.value("id").toInt();
  t_zoneName = r.value("zone_name").toString();      
  t_parentZoneName = r.value("parent_zone_name").toString(); ;
  t_description = r.value("description").toString();   
  
  QDialog::accept();
}

void SvZonesList::slotNewZone()
{
  ZONE_UI = new SvZone("", true, this);
  connect(ZONE_UI, SIGNAL(accepted()), this, SLOT(on_ZONE_UI_closed()));
  connect(ZONE_UI, SIGNAL(rejected()), this, SLOT(on_ZONE_UI_closed()));
}

void SvZonesList::on_ZONE_UI_closed()
{
  if(ZONE_UI->result() == QDialog::Accepted)
  {
    this->setZonesListTable();
  }
  
  ZONE_UI->~SvZone();
}

void SvZonesList::slotEditZone()
{
//  DEV_UI = new SvDevice(this, 1);
//  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
//  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvZonesList::slotDeleteZone()
{
  
}


int SvZonesList::setZonesListTable()
{
//  model->clear();
//  model->setColumnCount(2);
//  model->setHeaderData(0, Qt::Horizontal, QString("Зона"));
//  model->setHeaderData(1, Qt::Horizontal, QString("Входит в зону"));
////  model->setHeaderData(2, Qt::Horizontal, QString("Описание"));

//  tblZonesList->setModel(model);
//  tblZonesList->setSizeAdjustPolicy(QTableView::AdjustToContents);
  
//  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* sett = new SvSettings(s);

//  QStringList lst = sett->appSettings->childGroups();
//  QList<QStandardItem *> rowItems;
//  for(int i = 0; i < lst.count(); i++)
//  {
//    rowItems.clear();
//    s = sett->readValue(lst.at(i), "zone", "").toString();
//    for(int j = 1; j <= 2; j++)
//      rowItems << new QStandardItem(s.section('%', j, j));

//    model->appendRow(rowItems);
//    tblZonesList->setRowHeight(i, 22);
//  }

  QSqlError err = PGDB->execSQL(D_SELECT_ZONES_LIST, m_zones_model);
  if(err.type() != QSqlError::NoError) return -1;
  
  tblZonesList->setModel(m_zones_model);
  
  QStringList headers = QString(D_ZONES_COLUMN_LIST).split(';');
  
  for(int i = 0; i < headers.count(); i++)
  {
    m_zones_model->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
    tblZonesList->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
    tblZonesList->setColumnWidth(i, 150);
  }
  
  return 0;
}

void SvZonesList::tableClicked(QModelIndex mi)
{
  QSqlRecord r = m_zones_model->record(tblZonesList->currentIndex().row());
  QString currentZoneName = r.value("zone_name").toString(); 
  
//  QString currentZoneName = model->data(model->index(mi.row(), 0)).toString();
  zdw->updateDraw(QSize(dlg->widget->width(), dlg->widget->height()), currentZoneName);
}
