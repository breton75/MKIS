#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QThread>

#include "../demo_1/COMMON/sv_tcpserverclient.h"

/** эта структура соответствует структуре, 
 *  используемой в прошивке контроллера **/
struct GotKeyStruct
{
  uchar scud_number;
  uchar key_byte1;
  uchar key_byte2;
  uchar key_byte3;
  uchar sec;
  uchar min;
  uchar hour;
  uchar day;
  uchar month;
  uchar weekday;
  uchar year;
};

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AfterShow();
    
    QTextEdit* get_log();
    
    SvTcpServer* tcp_server = 0;
//    QSqlQuery* query;
    
  private:
    Ui::MainWindow *ui;
    
    int t_key;
    int t_scud_number;
    int t_code;
    QDateTime t_date_time;
    bool debug = false;
    
    
  private slots:
    void slotStart();
    void slotStop();
    void slotGotMessage();
    void slotClose();
//    void slotMakeLog();
    
    void on_bnTest_clicked();
    
  signals:
    void sigDBUpdated();
};

#endif // MAINWINDOW_H
