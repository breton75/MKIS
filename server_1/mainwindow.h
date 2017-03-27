#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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
    
  public slots:
    virtual void SendMessage();
    virtual void disconnectFromServer();
    
    void StartServer();
    void StopServer();
    
    void SaveSettings();
    
    /*  DB  */
    void slotConnectToDB();
    void slotDisconnectDB();
    void slotExecSQL();
    void slotShowSimbols();
    
  private slots:
    void on_pushButton_clicked();
    
  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
