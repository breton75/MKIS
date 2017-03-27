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
#include "../demo_1/COMMON/sv_ffmpeg2file.h"

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
    
    SvFFmpeg2File* ff2file = 0;
    QList<int>devIdList;
    
//    QSqlQuery* query;
    
  private:
    Ui::MainWindow *ui;

    QDateTime t_date_time;
    int last_id = -1;
    int current_device_id = -1;
    QString current_device_name = "";
    QDateTime begin_time;
    QString  file_name;
    bool debug = false;
    
  private slots:
    void slotStart();
    void slotStop();
    void slotNewFile(/*QDateTime dt, QString filename*/);
    void slotFileFinished();
    void slotClose();
    void slotFinished();
    void on_FF2F_SETTINGS_UI_closed();
    
    
//    void on_bnTest_clicked();
    
    void on_bnSettings_clicked();
    void on_comboBox_currentIndexChanged(int index);
    
  signals:
    void sigDBUpdated();
};

#endif // MAINWINDOW_H
