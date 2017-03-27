#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QList>
#include <QMessageBox>

#include "../demo_1/COMMON/sv_tcpserverclient.h"
#include "../demo_1/sv_rls2bittofile.h"

#pragma pack(push, 1)
struct GotCmdStruct
{
//  char cmd[10];
    time_t begin_date_dime;
    time_t end_date_dime;    
   quint16 port;
   int device_id;

  
};
#pragma pack(pop)


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    QTextEdit* get_log();

  private:
    Ui::MainWindow *ui;
    
    SvRlsDataToFile* rls2file = 0;
    QList<int>devIdList; 
    
    int rotation_speed = 6;
    
    int last_id = -1;
    int current_device_id = -1;
    QString current_device_name = "";
    QDateTime begin_time;
    QString  file_name;
    bool debug = false;
    
    SvRls2bitFile2Udp* rls2udp;
    SvTcpServer* tcp_server = NULL;
    quint16 archDataPort;
    
  private slots:
    void slotStart();
    void slotStop();
    void slotNewFile(/*QDateTime dt, QString filename*/);
    void slotFileFinished();
    void slotClose();
    void slotFinished();
    void slotGotMessage();

    /* transaltion */
    void slotNoRecords();      
    void slotNewFileTraslation();
    void slotWrongFileTraslation();
    void slotTranslationFinished();
    
    void on_bnSettings_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_RLS2BIT_2F_SETTINGS_UI_closed();
    
  signals:
    void sigDBUpdated();
};

#endif // MAINWINDOW_H
