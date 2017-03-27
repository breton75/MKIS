#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystream.h"
#include "log.h"
#include "time.h"

#include <QMap>
#include <QStringList>

using namespace log_ns;

myStream *str;
QMap<QString, myStream*> *map;
bool stopped;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  
  connect(ui->bnStart, SIGNAL(pressed()), this, SLOT(slotStart()));
  connect(ui->bnStop, SIGNAL(pressed()), this, SLOT(slotStop()));
//  connect(str, SIGNAL(uu()), this, SLOT(slotLog()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

QTextEdit* MainWindow::get_log()
{
  return ui->textEdit;
}

void MainWindow::slotStart()
{
  QStringList sl = ui->textEdit_2->toPlainText().split('\n');

  QString ip = "";
  quint16 port = ui->lineEdit->text().toInt();
  
  map = new QMap<QString, myStream*>();
  
  for(int i = 0; i < sl.count(); i++)

  {

    ip = sl.at(i);

    if(QHostAddress(ip).toIPv4Address() > 0)
    {
 
      map->insert(ip, new myStream(ip, port));

      connect(map->value(ip), SIGNAL(started()), this, SLOT(slotStarted()));
      connect(map->value(ip), SIGNAL(finished()), this, SLOT(slotStopped()));    
      
      map->value(ip)->start();
    }
  }
  
}

void MainWindow::slotStop()
{
  while(!map->isEmpty())
  {
    stopped = false;
    map->last()->enable = false;
    while(!stopped) QApplication::processEvents();
    map->remove(map->lastKey());
  }
  
  map->~QMap();

}

void MainWindow::slotLog()
{

}

void MainWindow::slotStarted()
{
  
  ui->bnStart->setEnabled(false);
  ui->bnStop->setEnabled(true);
  
  myStream *ms = new myStream("", 0);
  ms = static_cast<myStream*>(sender());
  
  log(m_Success, QString("Stream %1 started").arg(map->key(ms)));
  
}

void MainWindow::slotStopped()
{

  ui->bnStart->setEnabled(true);
  ui->bnStop->setEnabled(false);
  
  myStream *ms = new myStream("", 0);
  ms = static_cast<myStream*>(sender());
  
  log(m_Err, QString("Stream %1 stopped").arg(map->key(ms)));

  stopped = true;  
}
