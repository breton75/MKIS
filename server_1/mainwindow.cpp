#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Common/sv_serverclient.h"
#include "../../Common/log.h"
#include "../../Common/sv_pgdb.h"
#include "../../Common/sv_settings.h"
//#include "../../Common/sv_tcpclient.h"

using namespace log_ns;

SvServerClient *sc;
SvPGDB *pgdb;
SvSettings *sett;

void LogSQLError(QSqlError error, QString noErrorMsg = "");

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  connect(ui->actionSend, SIGNAL(triggered()), this, SLOT(SendMessage()));
  connect(ui->actionStart_server, SIGNAL(triggered()), this, SLOT(StartServer()));
  connect(ui->actionStop_server, SIGNAL(triggered()), this, SLOT(StopServer()));
  
  connect(ui->editIp, SIGNAL(textChanged(QString)), this, SLOT(SaveSettings()));
  connect(ui->editPort, SIGNAL(textChanged(QString)), this, SLOT(SaveSettings()));
  connect(ui->sbStreamVer, SIGNAL(valueChanged(int)), this, SLOT(SaveSettings()));
  connect(ui->chbAdvStream, SIGNAL(stateChanged(int)), this, SLOT(SaveSettings()));
  connect(ui->editMsg, SIGNAL(textChanged(QString)), this, SLOT(SaveSettings()));
  connect(ui->chbDisconnectAfterSend, SIGNAL(stateChanged(int)), this, SLOT(SaveSettings()));
  connect(ui->chbShowSimbols, SIGNAL(stateChanged(int)), this, SLOT(SaveSettings()));  
  
  connect(ui->bnConnectDB, SIGNAL(pressed()), this, SLOT(slotConnectToDB()));
  connect(ui->bnDisconnectDB, SIGNAL(pressed()), this, SLOT(slotDisconnectDB()));
  connect(ui->bnExecQuery, SIGNAL(pressed()), this, SLOT(slotExecSQL()));

  connect(ui->chbShowSimbols, SIGNAL(clicked()), this, SLOT(slotShowSimbols()));
  
//  connect(ui->bnPlay, SIGNAL(pressed()), this, SLOT(say_cam()));
//  connect(ui->bnStop, SIGNAL(pressed()), this, SLOT(say_stop()));
  
//  connect(this, SIGNAL(sig_options()), this, SLOT(do_options()));
//  connect(this, SIGNAL(sig_describe()), this, SLOT(do_describe()));
//  connect(this, SIGNAL(sig_setup()), this, SLOT(do_setup()));
//  connect(this, SIGNAL(sig_play()), this, SLOT(do_play()));
  
}

MainWindow::~MainWindow()
{
  delete ui;
}

QTextEdit* MainWindow::get_log()
{
  return ui->textLog;
}

void MainWindow::AfterShow()
{
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  sett = new SvSettings(s);
  
  ui->editIp->setText(sett->readValue("Client", "IP", "169.254.110.130").toString());
  ui->editPort->setText(sett->readValue("Client", "Port", "35580").toString());
  ui->sbStreamVer->setValue(sett->readValue("Client", "Stream version", 15).toInt());
  ui->chbAdvStream->setChecked(sett->readValue("Client", "Advanced stream", false).toBool());
  ui->editMsg->setText(sett->readValue("Client", "Message", "This is message").toString());
  ui->chbDisconnectAfterSend->setChecked(sett->readValue("Client", "Disconnect after send", false).toBool());
  ui->chbShowSimbols->setChecked(sett->readValue("Client", "Show symbols", false).toBool());
  
  sc = new SvServerClient(/*0, "", 0, true*/);
  sc->streamVersion = ui->sbStreamVer->value();
  sc->advancedStream = ui->chbAdvStream->isChecked();
  
//  sc->runServer(35580);
  
}

void MainWindow::SendMessage()
{

  ui->bnSendMsg->setEnabled(false);
  QApplication::processEvents();
  
  if((ui->editIp->text() == "") | (ui->editPort->text().toInt() == 0))
  {
    log(m_Err, "Wrong IP or port");
    return;
  }
  
  if (!sc->connected)
  {

    if ((sc->outIp != ui->editIp->text()) | (sc->outPort != quint16(ui->editPort->text().toInt())))
      {
          sc->outIp = ui->editIp->text();
          sc->outPort = quint16(ui->editPort->text().toInt());
      }

      sc->connectToHost();

    }
  else
    {
      if ((sc->outIp != ui->editIp->text()) | (sc->outPort != ui->editPort->text().toInt()))
        {
          sc->clientSocket->disconnectFromHost();
          sc->outIp = ui->editIp->text();
          sc->outPort = ui->editPort->text().toInt();
          sc->connectToHost();          
        }
    }
  
  ui->bnSendMsg->setEnabled(true);
  if (!sc->connected) return;

  sc->sayToServer(ui->editMsg->text());
  
  if (ui->chbDisconnectAfterSend->isChecked())
  {
    connect(&(sc->timer), SIGNAL(timeout()), this, SLOT(disconnectFromServer()));
    sc->timer.setSingleShot(true);
    sc->timer.start(ui->sbTimer->value());
  }
  else 
  {
    disconnect(&(sc->timer), SIGNAL(timeout()), this, SLOT(disconnectFromServer()));
  }
}

void MainWindow::disconnectFromServer()
{
  if(sc->connected)
  {
    sc->clientSocket->disconnectFromHost();
  }
}

void MainWindow::StartServer()
{
  if(ui->editPort_2->text().toInt() <= 0)
  {
    log(m_Err, "Listen port is not assigned");
    return;
  }
  
  sc->runServer(quint16(ui->editPort_2->text().toInt()));
  
  ui->bnStartServer->setEnabled(false);
  ui->bnStopServer->setEnabled(true);
  QApplication::processEvents();
}

void MainWindow::StopServer()
{
  sc->stopServer();
  
  ui->bnStartServer->setEnabled(true);
  ui->bnStopServer->setEnabled(false);
  QApplication::processEvents();
}

void MainWindow::SaveSettings()
{
  if(!sc) return;
  
  sett->writeValue("Client", "IP", ui->editIp->text());
  sett->writeValue("Client", "Port", ui->editPort->text());
  sett->writeValue("Client", "Stream version", ui->sbStreamVer->value());
  sett->writeValue("Client", "Advanced stream", ui->chbAdvStream->isChecked());
  sett->writeValue("Client", "Message", ui->editMsg->text());
  sett->writeValue("Client", "Disconnect after send", ui->chbDisconnectAfterSend->isChecked());
  sett->writeValue("Client", "Show symbols", ui->chbShowSimbols->isChecked());
  
  sc->streamVersion = ui->sbStreamVer->value(); 
  sc->advancedStream = ui->chbAdvStream->isChecked();
}

void MainWindow::slotConnectToDB()
{
  ui->bnConnectDB->setEnabled(false);
  QApplication::processEvents();
  
  if(!pgdb) pgdb = new SvPGDB();
  pgdb->setConnectionParams(ui->editDBName->text(),
                            ui->editHostDB->text(),
                            quint16(ui->editPortDB->text().toInt()),
                            ui->editUserDb->text(),
                            ui->editPassDB->text());
  
  log(m_Info, "Connecting to database");
  QSqlError err = pgdb->connectToDB();
  log_SQL_error(err, QString("User %1 connected to DB(%2)").arg(ui->editUserDb->text()).arg(ui->editHostDB->text()));
  
  if(err.type() != QSqlError::NoError)
  {
    pgdb->~SvPGDB();
    ui->bnConnectDB->setEnabled(true);
  }
  else ui->bnDisconnectDB->setEnabled(true);
  
  QApplication::processEvents();
  
  
}

void MainWindow::slotDisconnectDB()
{
  ui->bnDisconnectDB->setEnabled(false);
  QApplication::processEvents();
  
  log(m_Info, "Disconnecting from database");
  QSqlError err = pgdb->disconnectFromDb();
  log_SQL_error(err, QString("User %1 disconnected from DB(%2)").arg(ui->editUserDb->text()).arg(ui->editHostDB->text()));
  
  if(err.type() == QSqlError::NoError) ui->bnConnectDB->setEnabled(true);
  else ui->bnDisconnectDB->setEnabled(true);
  
  QApplication::processEvents();
  
  
}

void MainWindow::slotExecSQL()
{
  QSqlError err = pgdb->execSQL(ui->textQuery->toPlainText());
  log_SQL_error(err);
}

void MainWindow::slotShowSimbols()
{
  sc->showSymbols = ui->chbShowSimbols->isChecked();
}




