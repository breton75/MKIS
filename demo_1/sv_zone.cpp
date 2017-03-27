#include "sv_zone.h"
#include "./COMMON/sv_settings.h"
#include "./COMMON/sv_pgdb.h"

SvZone* ZONE_UI;
SvNewZone* NEW_ZONE_UI;
extern SvZonesList *ZONELIST_UI;
extern DragInfo DRAG_INFO;
extern SvPGDB *PGDB;

SvSettings* zsett;

SvZone::SvZone(QString zoneName,
               bool allowEdit,
               QWidget *parent) :
  QDialog(parent),
  zui(new Ui::SvZoneDialog)
{
  zui->setupUi(this, "parentName");
  
  zui->bnAddDevice->setEnabled(allowEdit);
  zui->bnDeleteDevice->setEnabled(allowEdit);
  
  zdw = new SvZoneDrawWidget(zui->widget);
  
  if(allowEdit)
    zdw->editZone(QSize(this->width(), this->height()), zoneName);
  
  else
    zdw->updateDraw(QSize(this->width(), this->height()), zoneName);
  
  zui->hlayMain->addWidget(zdw);
  
  dtv = new SvTreeView(zui->widget);
  dtv->loadDevices(zoneName);
  dtv->setMinimumWidth(250);
  dtv->setMaximumWidth(250);
  dtv->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
  zui->hlayMain->addWidget(dtv);
  dtv->expandAll();
    qDebug() << "SvZone::SvZone 1";
  connect(zui->bnSaveClose, SIGNAL(pressed()), this, SLOT(accept()));
  connect(zui->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setModal(true);
  this->setResult(-1);
  this->show();
  qDebug() << "SvZone::SvZone 2";
}

SvZone::~SvZone()
{
  zdw->~SvZoneDrawWidget();
  dtv->~SvTreeView();
  this->close();
  delete zui;
}

void SvZone::accept()
{
  zdw->saveCurrentZone();  
  
  QDialog::accept();
}


/** ********* New Zone Dialog ************ **/
SvNewZone::SvNewZone(QWidget *parent,
                     int showMode,
                     QString zoneName) :
  QDialog(parent),
  nzui(new Ui_nz::SvNewZoneDialog)
{
  nzui->setupUi(this);
  
  this->showMode = showMode;
  nzui->editZoneName->setReadOnly(showMode != smNew);
  
  if(showMode == smEdit)
  {
    QSqlQuery* q = new QSqlQuery(PGDB->db);
    QSqlError err = PGDB->execSQL(QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + zoneName + "'"), q);
    if(err.type() != QSqlError::NoError) return;

    if(q->size() == 0) return;
    q->first();
    t_id = q->value("id").toInt();
    t_zoneName = q->value("zone_name").toString();
    t_parentZoneName = q->value("parent_zone_name").toString();
    t_imgPath = q->value("img_path").toString();
    t_points = q->value("points").toString();
    t_sceneSize = q->value("scene_size").toInt();
    t_description = q->value("description").toString();
  }
  else if(showMode == smNew)
    t_parentZoneName = zoneName;

//  QString parentZoneName;
//  QString imgPath;
  
//  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* sett = new SvSettings(s);
//  QStringList lst = sett->appSettings->childGroups();
//  for(int i = 0; i < lst.count(); i++)
//  {
//    s = sett->readValue(lst.at(i), "zone", "").toString();
//    if(s.section('%', 1, 1) == zoneName)
//    {
//      parentZoneName = s.section('%', 2, 2);
//      imgPath = s.section('%', 3, 3);
//    }
//  }
  nzui->editID->setText(showMode == smNew ? "<Новый>" : QString("%1").arg(t_id));
  nzui->editZoneName->setText(t_zoneName);
  nzui->editParentZoneName->setText(t_parentZoneName); 
  nzui->editImgPath->setText(t_imgPath);
  nzui->gbChildable->setChecked(t_imgPath != "");
  
  nzui->lblImgPath->setEnabled(nzui->gbChildable->isChecked());
  nzui->editImgPath->setEnabled(nzui->gbChildable->isChecked());
  nzui->bnImgPath->setEnabled(nzui->gbChildable->isChecked());

  connect(nzui->bnSelectParentZone, SIGNAL(clicked()), this, SLOT(on_bnSelectParentZone_pressed()));
  connect(nzui->bnSave, SIGNAL(pressed()), this, SLOT(accept()));
  connect(nzui->bnCancel, SIGNAL(pressed()), this, SLOT(reject()));
  
  this->setModal(true);
  this->setResult(-1);
  this->show();
}

SvNewZone::~SvNewZone()
{
  this->close();
  delete nzui;
}

void SvNewZone::on_bnImgPath_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                  tr("Выберите изображение"),
                                                  qApp->applicationDirPath(),
                                                  tr("Изображения (*.bmp *.jpg *.png);;Bceфайлы (*.*)"));

  if(fileName.isEmpty()) return;
  
  nzui->editImgPath->setText(fileName);
  
}

void SvNewZone::on_gbChildable_clicked()
{
  nzui->lblImgPath->setEnabled(nzui->gbChildable->isChecked());
  nzui->editImgPath->setEnabled(nzui->gbChildable->isChecked());
  nzui->bnImgPath->setEnabled(nzui->gbChildable->isChecked());
}

void SvNewZone::accept()
{
  QSqlError err;
  QSqlQuery* q;
  
  if(nzui->editZoneName->text() == "")
  {
    QMessageBox::critical(0, "Ошибка", "Необходимо указать имя зоны", QMessageBox::Ok);
    nzui->editZoneName->setFocus();
    return;
  }
  
  if(this->showMode  == smNew)
  {
    q = new QSqlQuery(PGDB->db);
    err = PGDB->execSQL(QString(D_SELECT_FROM_ZONES_WHERE).arg("zone_name").arg("'" + nzui->editZoneName->text() + "'"), q);
    if(err.type() != QSqlError::NoError) return;
    
    if(q->size())
    {
      QMessageBox::critical(0, "Ошибка", "Зона с таким именем уже существует", QMessageBox::Ok);
      nzui->editZoneName->setFocus();
      return;
    }
  }
  
  t_zoneName = nzui->editZoneName->text();
  t_parentZoneName = nzui->editParentZoneName->text();
  t_imgPath = nzui->gbChildable->isChecked() ? nzui->editImgPath->text() : ""; 
  
  
  
//  QString s = qApp->applicationDirPath() + "/ini/zones.ini";
//  SvSettings* sett = new SvSettings(s);
//  QStringList lst = sett->appSettings->childGroups();
//  char groupName;
//  QString zonePoints = "";
//  QString zoneSize = "";
  QString s;
  switch(this->showMode)
  {
    case smNew:
    {
      s = QString(D_INSERT_INTO_ZONES).arg(t_zoneName)
                                      .arg(t_parentZoneName)
                                      .arg(t_imgPath)
                                      .arg(t_description);
      
      //      if(lst.count())
//      {
//        groupName = lst.last().at(0).toLatin1();
//        if(groupName == 'z') return;
      
//        groupName =  groupName + 1;
//      }
//      else groupName = 'a'; 
      break;
    }

    case smEdit:
    {
      s = QString(D_UPDATE_ZONES).arg(t_zoneName)
                                 .arg(t_parentZoneName)
                                 .arg(t_imgPath)
                                 .arg(t_description)
                                 .arg(t_id);
      
//      for(int i = 0; i < lst.count(); i++)
//      {
//        s = sett->readValue(lst.at(i), "zone", "").toString();
//        if(s.section('%', 1, 1) == t_zoneName)
//        {
//          groupName = lst.at(i).at(0).toLatin1();
//          zonePoints = s.section('%', 4, 4);
//          zoneSize = s.section('%', 5, 5);
//          break;
//        }
//      }
      break;
    }
  }  
  
//  sett->writeValue(QString("%1").arg(groupName), "zone", QString("\%%1\%%2\%%3\%%4\%%5\%")
//                                                      .arg(nzui->editZoneName->text())
//                                                      .arg(nzui->editParentZoneName->text())
//                                                      .arg(nzui->editImgPath->text())
//                                                      .arg(zonePoints)
//                                                      .arg(zoneSize));

  err = PGDB->execSQL(s);
  if(err.type() != QSqlError::NoError) QDialog::reject();  
  else QDialog::accept();
}

void SvNewZone::on_bnSelectParentZone_clicked()
{
  ZONELIST_UI = new SvZonesList(this, false, false);
  connect(ZONELIST_UI, SIGNAL(accepted()), this, SLOT(on_ZONELIST_UI_closed()));
  connect(ZONELIST_UI, SIGNAL(rejected()), this, SLOT(on_ZONELIST_UI_closed()));
}

void SvNewZone::on_ZONELIST_UI_closed()
{
  if(ZONELIST_UI->result() == QDialog::Accepted)
  {
    nzui->editParentZoneName->setText(ZONELIST_UI->t_zoneName);
  }
  ZONELIST_UI->~SvZonesList();
}


