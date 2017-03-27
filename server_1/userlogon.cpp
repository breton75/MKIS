#include "userlogon.h"
#include "ui_userlogon.h"
#include "../../Common/sv_pgdb.h"
#include "../../Common/log.h"

using namespace log_ns;

extern SvPGDB *pgdb;

UserLogon::UserLogon(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  ui->textEdit->hide();
  
//  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(slotConnectToDB()));
  connect(ui->bnCancel, SIGNAL(pressed()), this, SLOT(slotCloseApp()));
  connect(ui->bnConnect, SIGNAL(pressed()), this, SLOT(slotConnectToDB()));
}

UserLogon::~UserLogon()
{
  delete ui;
}

QTextEdit* UserLogon::get_log()
{
  return ui->textEdit;
}

void UserLogon::slotConnectToDB()
{
  int errCnt = 0;
//  ui->buttonBox->setEnabled(false);
  ui->bnConnect->setEnabled(false);
  ui->bnCancel->setEnabled(false);
  QApplication::processEvents();
  
  if(!pgdb) delete &pgdb;
  pgdb = new SvPGDB();

  pgdb->setConnectionParams("postgres", /* ui->editDBName->text(),*/
                            ui->editHostDB->text(),
                            5432, /*quint16(ui->editPortDB->text().toInt()),*/
                            ui->editUserDb->text(),
                            ui->editPassDB->text());
  
  log(m_Info, "Connecting to database");
  QSqlError err = pgdb->connectToDB();
  log_SQL_error(err);
  
  if((err.type() != QSqlError::NoError) & (!errCnt))
  {
    ui->textEdit->show();
    ui->resizeDialog(this, 250);
    errCnt++;
  }
  this->setResult(err.type() == QSqlError::NoError ? QDialog::Accepted : -1);
  
  
  ui->bnCancel->setEnabled(true);
  ui->bnConnect->setEnabled(true);
  QApplication::processEvents();
  
}

void UserLogon::slotCloseApp()
{
  this->setResult(QDialog::Rejected);
}
