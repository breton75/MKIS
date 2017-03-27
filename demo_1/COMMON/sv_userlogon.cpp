#include "sv_userlogon.h"
#include "ui_userlogon.h"
#include "sv_pgdb.h"
#include "log.h"

using namespace log_ns;

extern SvPGDB *PGDB;

SvUserLogon::SvUserLogon(QWidget *parent,
                         bool showHost,
                         bool showPort,
                         bool showDBName,
                         bool showUser,
                         bool showPass,
                         bool showLog,
                         QString host,
                         quint16 port,
                         QString dbName,
                         QString user,
                         QString pass) :
  QDialog(parent),
  ulogon(new Ui::SvUserLogonDialog)
{
  ulogon->ShowDialog(this,
                     showHost, showPort, showDBName, showUser, showPass, showLog,
                     host, port, dbName, user, pass);
  
//  ulogon->showLog(this);
  ulogon->connectionErrorCount = 0;
  PGDB = 0;
  
  
//  connect(ulogon->buttonBox, SIGNAL(accepted()), this, SLOT(slotConnectToDB()));
  connect(ulogon->bnCancel, SIGNAL(pressed()), this, SLOT(slotCloseApp()));
  connect(ulogon->bnConnect, SIGNAL(pressed()), this, SLOT(slotConnectToDB()));
}

SvUserLogon::~SvUserLogon()
{
  delete ulogon;
}

QTextEdit* SvUserLogon::get_log()
{
  return ulogon->textEdit;
}

void SvUserLogon::slotConnectToDB()
{
//  ulogon->buttonBox->setEnabled(false);
  ulogon->bnConnect->setEnabled(false);
  ulogon->bnCancel->setEnabled(false);
  QApplication::processEvents();

  t_host = ulogon->editHost->text();
  t_port = ulogon->editPort->text().toInt();
  t_dbName = ulogon->editDbName->text();
  t_user = ulogon->editUser->text();
  t_pass = ulogon->editPass->text();
  
  if(PGDB) PGDB->~SvPGDB();
  PGDB = new SvPGDB();
//  PGDB->start();
  PGDB->setConnectionParams(t_dbName,
                            t_host,
                            t_port, /*qulogonnt16(ulogon->editPortDB->text().toInt()),*/
                            t_user,
                            t_pass);
  
  log(m_Info, QString("Connecting to database (%1)").arg(ulogon->connectionErrorCount));
  QApplication::processEvents();
  
  QSqlError err = PGDB->connectToDB();
  log_SQL_error(err);
  
  if((err.type() != QSqlError::NoError) & (!ulogon->connectionErrorCount))
  {
    ulogon->showLog(this);
    ulogon->connectionErrorCount++;
  }
  this->setResult(err.type() == QSqlError::NoError ? QDialog::Accepted : -1);
  
  
  ulogon->bnCancel->setEnabled(true);
  ulogon->bnConnect->setEnabled(true);
  QApplication::processEvents();
  
}

void SvUserLogon::slotCloseApp()
{
  this->setResult(QDialog::Rejected);
}
