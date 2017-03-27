#include "sv_device_list.h"
#include "sql_create_defs.h"
#include "sql_fields_defs.h"
#include "sql_select_defs.h"
#include "sv_pgdb.h"
#include <QMessageBox>

SvDevicesList *DEVICELIST_UI;
extern SvDevice *DEV_UI;
extern SvPGDB *PGDB;

SvDevicesList::SvDevicesList(QWidget *parent,
//                             QSqlDatabase* db,
                             bool showEditDelete,
                             bool showSelect) :
  QDialog(parent),
  Dialog(new Ui::SvDeviceListDialog),
  p_devices_model(new QSqlQueryModel(this))
{
  Dialog->setupUi(this);
  
  setDeviceListTable();
  
  Dialog->bnEditClass->setVisible(showEditDelete);
  Dialog->bnDeleteClass->setVisible(showEditDelete);
  Dialog->bnSelect->setVisible(showSelect);
  
  connect(Dialog->bnSelect, SIGNAL(pressed()), this, SLOT(accept()));
  connect(Dialog->bnClose, SIGNAL(pressed()), this, SLOT(reject()));
  connect(Dialog->bnNewClass, SIGNAL(pressed()), this, SLOT(slotNewDevice()));
  connect(Dialog->bnEditClass, SIGNAL(pressed()), this, SLOT(slotEditDevice()));
  connect(Dialog->bnDeleteClass, SIGNAL(pressed()), this, SLOT(slotDeleteDevice()));
  
  this->setResult(-1);
  this->setModal(true);
  this->show();
}

SvDevicesList::~SvDevicesList()
{
  this->close();
  delete Dialog;
}

void SvDevicesList::accept()
{
//  QSqlRecord r = this->p_model_devices->record(dlg->tblDeviceList->currentIndex().row());
  
//  t_id = r.value(F_DEVICE_ID).toInt();
//  t_deviceName = r.value(F_DEVICE_NAME).toString();
//  t_ip = r.value(F_DEVICE_IP).toString();
//  t_port = r.value(F_DEVICE_PORT).toInt();
//  t_modelId = r.value(F_DEVICE_MODEL_ID).toInt();
//  t_modelName = r.value(F_MODEL_NAME).toString();
//  t_className = r.value(F_CLASS_NAME).toString();    
//  t_brandName = r.value(F_BRAND_NAME).toString();    
//  t_libPath = r.value(F_MODEL_LIB).toString();    
//  t_X = r.value(F_DEVICE_POSX).toInt();
//  t_Y = r.value(F_DEVICE_POSY).toInt();    
//  t_Z = r.value(F_DEVICE_POSZ).toInt();    
//  t_description = r.value(F_DEVICE_DESCRIPT).toString();

  QSqlRecord r = p_devices_model->record(Dialog->tblDeviceList->currentIndex().row());
  t_id            = r.value("id").toInt();
  t_deviceName    = r.value("device_name").toString();
  t_ip            = r.value("ip").toString();
  t_port          = r.value("port").toInt();
  t_modelName     = r.value("model").toString();
  t_className     = r.value("class").toString();
  t_brandName     = r.value("brand").toString();
  t_libPath       = r.value("video_path").toString();
  t_X             = r.value("pos_x").toInt();
  t_Y             = r.value("pos_y").toInt();
  t_zoneName      = r.value("zoneName").toString();
  t_description   = r.value("description").toString();
    
  QDialog::accept();
}

void SvDevicesList::slotNewDevice()
{
  DEV_UI = new SvDevice(this);
  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvDevicesList::on_DEV_UI_closed()
{
  if(DEV_UI->result() == QDialog::Accepted)
  {
    this->setDeviceListTable();
  }
  
  DEV_UI->~SvDevice();
}

void SvDevicesList::slotEditDevice()
{
//  DEV_UI = new SvDevice(this, 1);
//  connect(DEV_UI, SIGNAL(accepted()), this, SLOT(on_DEV_UI_closed()));
//  connect(DEV_UI, SIGNAL(rejected()), this, SLOT(on_DEV_UI_closed()));
}

void SvDevicesList::slotDeleteDevice()
{
  
}


int SvDevicesList::setDeviceListTable(/*QSqlQueryModel* queryModel, QTableView* table*/)
{
  /* ----------- dev_list -------------*/
  
//  QSqlError err = PGDB->execSQL(SELECT_DEVICE_LIST, this->p_model_devices);
//  if(err.type() != QSqlError::NoError) return -1;
  
//  this->p_tbl_devices->setModel(this->p_model_devices);
  
//  QStringList headers = QString(DEVICES_COLUMN_LIST).split(';');
  
//  for(int i = 0; i < headers.count(); i++)
//  {
//    this->p_model_devices->setHeaderData(i,  Qt::Horizontal, headers.at(i).section("/", 1, 1));
//    this->p_tbl_devices->setColumnHidden(i, !(headers.at(i).section('/', 2, 2) == "true"));
//  }

    QSqlError err = PGDB->execSQL(D_SELECT_DEV_DEVICES_LIST, p_devices_model);
    if(err.type() != QSqlError::NoError) return -1;

    Dialog->tblDeviceList->setModel(p_devices_model);

    QStringList headers = QString(D_DEV_DEVICES_LIST).split(';');

    for(int i = 0; i < headers.count(); i++)
      p_devices_model->setHeaderData(i,  Qt::Horizontal, headers.at(i));

  return 0;
}
