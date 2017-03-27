#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSqlQueryModel>
#include <QTableView>

namespace Ui {
  class MainWindow;
}

int setDeviceListTable(QSqlQueryModel* queryModel, QTableView* table);

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    QTextEdit* get_log();
    
    void AfterShow();
    
  private slots:
    void on_bnNewDevice_clicked();
    void on_DEV_UI_closed();
    
    void on_pushButton_2_clicked();
    
    void on_bnEditDevice_clicked();
    
    void on_bnConfigure_clicked();
    void on_ARCH_UI_closed();
    
  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
