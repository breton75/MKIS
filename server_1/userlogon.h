#ifndef USERLOGON_H
#define USERLOGON_H

#include <QDialog>
#include <QSqlError>
#include <QTextEdit>

namespace Ui {
  class Dialog;
}

class UserLogon : public QDialog
{
    Q_OBJECT
    
  public:
    explicit UserLogon(QWidget *parent = 0);
    ~UserLogon();
    
    QTextEdit* get_log();
    
  public slots:
    virtual void slotConnectToDB();
    void slotCloseApp();
    
  private:
    Ui::Dialog *ui;
};

#endif // USERLOGON_H
