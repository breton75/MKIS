#include "mainwindow.h"
#include <QApplication>
#include "../../Common/sv_userlogon.h"
#include "../../Common/log.h"
#include <QDebug>
#include "../../Common/sv_settings.h"

using namespace log_ns;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  QString s = QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini";
  SvSettings *sett = new SvSettings(s);
  
  SvUserLogon *l = new SvUserLogon(0,
                                  sett->readValue("LOGON", "ShowHost", true).toBool(),
                                  sett->readValue("LOGON", "ShowPort", false).toBool(),
                                  sett->readValue("LOGON", "ShowDBName", false).toBool(),
                                  sett->readValue("LOGON", "ShowUser", true).toBool(),
                                  sett->readValue("LOGON", "ShowPass", true).toBool(),
                                  sett->readValue("LOGON", "ShowLog", false).toBool(),
                                  sett->readValue("LOGON", "Host", "169.254.1.1").toString(),
                                  sett->readValue("LOGON", "Port", 5432).toInt(),
                                  sett->readValue("LOGON", "DBName", "PSSDB").toString(),
                                  sett->readValue("LOGON", "User", "").toString(),
                                  sett->readValue("LOGON", "Pass", "").toString());
  l->show();
  assign_log(l->get_log());
  l->setResult(-1);
  
  while (l->result() == -1) { QApplication::processEvents(); }
  
  if (l->result() != QDialog::Accepted)
  {
    a.exit(-1);
    return -1;
  }

  sett->writeValue("LOGON", "Host", l->t_host);
  sett->writeValue("LOGON", "Port", l->t_port);
  sett->writeValue("LOGON", "DBName", l->t_dbName);
  sett->writeValue("LOGON", "User", l->t_user);
  sett->writeValue("LOGON", "Pass", l->t_pass);
  
  l->close();
  sett->~SvSettings();
  
  
  MainWindow w;
  assign_log(w.get_log());
  
  w.show();
  
  w.setWindowState(Qt::WindowMaximized);
  
  w.AfterShow();
    
  return a.exec();
}
