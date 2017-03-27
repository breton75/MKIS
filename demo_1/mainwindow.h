#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextEdit>
#include <QDateTime>
#include <QSqlError>
#include <QSqlQuery>

#include "sv_varstracker.h"
#include "sv_alarmsTreeView.h"

#include "./COMMON/sv_tcpserverclient.h"

struct GotKeyStruct2
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
    
    SvVarsTracker* vtrk;
    SvAlarmTreeView* alarm_tree;
    
    QStandardItemModel* treeModel = new QStandardItemModel;
    QStandardItem *rootNode = treeModel->invisibleRootItem();
    
    QTextEdit* get_log();
    
  private slots:
//    void on_actionDevices_triggered();
//    void on_DEV_UI_closed();
    
//    void on_actionVariables_triggered();
    
//    void on_actionZones_triggered();
    
//    void on_actionEmployeers_triggered();
    
//    void on_actionPlans_triggered();
    
//    void on_actionAccess_control_triggered();
    
//    void on_actionNewDevice_triggered();
    
//    void on_actionVideoView_triggered();
    
//    void on_actioneditZone_triggered();
//    void on_ZONE_UI_closed();
    
//    void on_actionEditDevice_triggered();
   
//    void on_actionAlarms_triggered();
    
    void on_alarm(QString var, qreal value);
    void slotGotMessage();
    
  private:
    Ui::MainWindow *ui;
    
    SvTcpServer* tcp_server = 0;
    int t_key;
    int t_scud_number;
    int t_code;
    QString t_employee_name;
    QString t_employee_patronymic;
    QString t_surename;
    QString t_device_name;
    QDateTime t_date_time;
    QString t_device_ip;
    
  public slots:
//    void treatDoubleClick(QModelIndex idx);
    
    
};

#endif // MAINWINDOW_H
