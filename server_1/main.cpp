#include "mainwindow.h"
//#include "../../Common/logon.h"
#include "userlogon.h"
 
#include <QApplication>
#include "../../Common/log.h"
#include <QDebug>
#include <QSqlDatabase>

using namespace log_ns;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  qDebug() << QSqlDatabase::drivers();
  
//  UserLogon l;
//  l.show();
//  assign_log(l.get_log());
//  l.setResult(-1);
  
//  while (l.result() == -1) { QApplication::processEvents(); }
  
//  if (l.result() != QDialog::Accepted)
//  {
//    a.exit(-1);
//    return -1;
//  }
//  l.close();
  
  MainWindow w;
  w.show();
  
  
  assign_log(w.get_log());
  w.AfterShow();
  
  return a.exec();
}
