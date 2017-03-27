#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
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
    
  QTextEdit* get_log(); 
    
  public slots:
    void slotStart();
    void slotStop();
    void slotLog();
    void slotStarted();
    void slotStopped();
    
  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
