#ifndef SV_SCUD_H
#define SV_SCUD_H

#include "./COMMON/sv_tcpserverclient.h"
#include "./COMMON/sv_pgdb.h"

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

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
  class SvSCUD;
}

class AwaitingKey;

class SvSCUD : public QDialog
{
    Q_OBJECT
    
  public:
    enum ShowMode
    { smNew = 0,
      smEdit };
    
    explicit SvSCUD(QWidget *parent,
                    int showMode = smNew,
                    int id = -1);
    
    ~SvSCUD();
    
    int t_id;
    int t_key = 0;
    QString t_device_name = "";
    int t_employee_id = -1;
    QString t_employee_name = "";
    QString t_employee_patronymic = "";
    QString t_employee_surename = "";
    QString t_employee_position = "";
    QString t_zone_name = "";
    
    int showMode;
    
    void accept() Q_DECL_OVERRIDE;
    
  private:
    Ui::SvSCUD *ui;
    
    SvTcpClient* tcp_client = 0;
    AwaitingKey* awaitingKey;
    
  private slots:
    void slotGetKey();
    void on_AWAITING_closed();
    
    void on_bnSelectEmployee_clicked();
    void on_bnNewEmployee_clicked();
    void on_EMPLOYEE_UI_closed();
    void on_EMPLOYEESLIST_UI_closed();
    
    void slotSelectDevice(); 
    void on_DEVICELIST_UI_closed();
    
    void on_bnSelectZone_clicked();
    void on_ZONELIST_UI_closed();
    void on_bnNewZone_clicked();
    void on_NEW_ZONE_UI_closed();
    
    
};

class AwaitingKey: public QDialog
{
    Q_OBJECT
    
  public:
    explicit AwaitingKey(QWidget *parent, QString ip = "");
    
    ~AwaitingKey();
    
    void accept() Q_DECL_OVERRIDE;
    void reject() Q_DECL_OVERRIDE;
    
    int t_scud_number;
    int t_key;
    QDateTime t_date_time;
    int t_weekday;
    
  private:
    SvTcpServer* tcp_server = 0;
        
};

#endif // SV_SCUD_H
