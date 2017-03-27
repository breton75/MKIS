#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{
    if(ui->radioButton->isChecked())  pan.conectTCP(true, 1);
    else pan.conectTCP(false, 1);

}

void MainWindow::on_radioButton_2_clicked()
{
    if(ui->radioButton_2->isChecked())  pan.conectTCP(true, 2);
    else pan.conectTCP(false, 2);
}

void MainWindow::on_radioButton_3_clicked()
{
    if(ui->radioButton_3->isChecked())  pan.conectTCP(true, 3);
    else pan.conectTCP(false, 3);
}

void MainWindow::on_radioButton_4_clicked()
{
    if(ui->radioButton_4->isChecked())  pan.conectTCP(true, 4);
    else pan.conectTCP(false, 4);
}

void MainWindow::on_radioButton_5_clicked()
{
    if(ui->radioButton_5->isChecked())  pan.conectTCP(true, 5);
    else pan.conectTCP(false, 5);
}

void MainWindow::on_radioButton_6_clicked()
{
    if(ui->radioButton_6->isChecked())  pan.conectTCP(true, 6);
    else pan.conectTCP(false, 6);
}
void MainWindow::on_radioButton_7_clicked()
{
    if(ui->radioButton_7->isChecked())  pan.conectTCP(true, 7);
    else pan.conectTCP(false, 7);
}
void MainWindow::on_radioButton_8_clicked()
{
    if(ui->radioButton_8->isChecked())  pan.conectTCP(true, 8);
    else pan.conectTCP(false, 8);
}
void MainWindow::on_radioButton_9_clicked()
{
    if(ui->radioButton_9->isChecked())  pan.conectTCP(true, 9);
    else pan.conectTCP(false, 9);
}
void MainWindow::on_radioButton_10_clicked()
{
    if(ui->radioButton_10->isChecked())  pan.conectTCP(true, 10);
    else pan.conectTCP(false, 10);
}
void MainWindow::on_radioButton_11_clicked()
{
    if(ui->radioButton_11->isChecked())  pan.conectTCP(true, 11);
    else pan.conectTCP(false, 11);
}
void MainWindow::on_radioButton_12_clicked()
{
    if(ui->radioButton_12->isChecked())  pan.conectTCP(true, 12);
    else pan.conectTCP(false, 12);
}
void MainWindow::on_radioButton_13_clicked()
{
    if(ui->radioButton_13->isChecked())  pan.conectTCP(true, 13);
    else pan.conectTCP(false, 13);
}
void MainWindow::on_radioButton_14_clicked()
{
    if(ui->radioButton_14->isChecked())  pan.conectTCP(true, 14);
    else pan.conectTCP(false, 14);
}
void MainWindow::on_radioButton_15_clicked()
{
    if(ui->radioButton_15->isChecked())  pan.conectTCP(true, 15);
    else pan.conectTCP(false, 15);
}
void MainWindow::on_radioButton_16_clicked()
{
    if(ui->radioButton_16->isChecked())  pan.conectTCP(true, 16);
    else pan.conectTCP(false, 16);
}
void MainWindow::on_radioButton_17_clicked()
{
    if(ui->radioButton_17->isChecked())  pan.conectTCP(true, 17);
    else pan.conectTCP(false, 17);
}
void MainWindow::on_radioButton_18_clicked()
{
    if(ui->radioButton_18->isChecked())  pan.conectTCP(true, 18);
    else pan.conectTCP(false, 18);
}
void MainWindow::on_radioButton_19_clicked()
{
    if(ui->radioButton_19->isChecked())  pan.conectTCP(true, 19);
    else pan.conectTCP(false, 19);
}
void MainWindow::on_radioButton_20_clicked()
{
    if(ui->radioButton_20->isChecked())  pan.conectTCP(true,20);
    else pan.conectTCP(false, 20);
}
void MainWindow::on_radioButton_21_clicked()
{
    if(ui->radioButton_21->isChecked())  pan.conectTCP(true,21);
    else pan.conectTCP(false, 21);
}
void MainWindow::on_radioButton_22_clicked()
{
    if(ui->radioButton_22->isChecked())  pan.conectTCP(true,22);
    else pan.conectTCP(false, 22);
}
void MainWindow::on_radioButton_23_clicked()
{
    if(ui->radioButton_23->isChecked())  pan.conectTCP(true,23);
    else pan.conectTCP(false, 23);
}
void MainWindow::on_radioButton_24_clicked()
{
    if(ui->radioButton_24->isChecked())  pan.conectTCP(true,24);
    else pan.conectTCP(false, 24);
}
void MainWindow::on_radioButton_25_clicked()
{
    if(ui->radioButton_25->isChecked())  pan.conectTCP(true,25);
    else pan.conectTCP(false, 25);
}
void MainWindow::on_radioButton_26_clicked()
{
    if(ui->radioButton_26->isChecked())  pan.conectTCP(true,26);
    else pan.conectTCP(false, 26);
}
void MainWindow::on_radioButton_27_clicked()
{
    if(ui->radioButton_27->isChecked())  pan.conectTCP(true,27);
    else pan.conectTCP(false, 27);
}
void MainWindow::on_radioButton_28_clicked()
{
    if(ui->radioButton_28->isChecked())  pan.conectTCP(true,28);
    else pan.conectTCP(false, 28);
}
void MainWindow::on_radioButton_29_clicked()
{
    if(ui->radioButton_29->isChecked())  pan.conectTCP(true,29);
    else pan.conectTCP(false, 29);
}
void MainWindow::on_radioButton_30_clicked()
{
    if(ui->radioButton_30->isChecked())  pan.conectTCP(true,30);
    else pan.conectTCP(false, 30);
}
void MainWindow::on_radioButton_31_clicked()
{
    if(ui->radioButton_31->isChecked())  pan.conectTCP(true,31);
    else pan.conectTCP(false, 31);
}
void MainWindow::on_radioButton_32_clicked()
{
    if(ui->radioButton_32->isChecked())  pan.conectTCP(true,32);
    else pan.conectTCP(false, 32);
}

void MainWindow::on_checkBox_clicked()
{

}
