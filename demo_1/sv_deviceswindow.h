#ifndef SVDEVICESWINDOW_H
#define SVDEVICESWINDOW_H

#include "mainwindow.h"

#include <QDebug>
#include <QObject>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QTableView>
#include <QApplication>
#include <QStringList>
#include <QList>
#include <QStandardItem>
#include <QTextCodec>
#include <QFrame>
#include <QToolButton>
#include <QGraphicsEffect>

#define DEVICES_SUBWINDOW_NAME "subw_devices"


class SvDevicesWindow : public QWidget //  QMdiSubWindow
{
  Q_OBJECT
    
  public:
    explicit SvDevicesWindow(QMdiArea* parent,
                             QString title);
    ~SvDevicesWindow();
    
    QStandardItemModel* model = new QStandardItemModel();
    
    QTableView* table;
    
    QToolButton* bnAddDevice;
    QToolButton* bnEditDevice;
    QToolButton* bnDeleteDevice;
    
  private slots:
    void on_bnEditDevice_clicked();
    void doubleClicked(QModelIndex mi);
    
};

#endif // SVDEVICESWINDOW_H
