#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QPushButton;
class GLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void show_start();
    void show_stop();

private:
    QLineEdit *bindAddrInput;
    QPushButton *startBtn, *stopBtn;
    GLWidget *monitor;
};

#endif // MAINWINDOW_H
