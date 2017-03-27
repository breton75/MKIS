#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "panel_tcp.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

Panel_tcp pan;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_7_clicked();
    void on_radioButton_8_clicked();
    void on_radioButton_9_clicked();
    void on_radioButton_10_clicked();
    void on_radioButton_11_clicked();
    void on_radioButton_12_clicked();
    void on_radioButton_13_clicked();
    void on_radioButton_14_clicked();
    void on_radioButton_15_clicked();
    void on_radioButton_16_clicked();
    void on_radioButton_17_clicked();
    void on_radioButton_18_clicked();
    void on_radioButton_19_clicked();
    void on_radioButton_20_clicked();
    void on_radioButton_21_clicked();
    void on_radioButton_22_clicked();
    void on_radioButton_23_clicked();
    void on_radioButton_24_clicked();
    void on_radioButton_25_clicked();
    void on_radioButton_26_clicked();
    void on_radioButton_27_clicked();
    void on_radioButton_28_clicked();
    void on_radioButton_29_clicked();
    void on_radioButton_30_clicked();
    void on_radioButton_31_clicked();
    void on_radioButton_32_clicked();


    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
