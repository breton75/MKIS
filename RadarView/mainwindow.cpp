#include "mainwindow.h"
#include "glwidget.h"
#include "socketreader.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


const QString defaultPort("35600");

MainWindow::MainWindow()
{
    monitor = new GLWidget;

    startBtn = new QPushButton("Старт");
    startBtn->setDefault(true);
    connect(startBtn, SIGNAL(clicked(bool)), SLOT(show_start()));

    stopBtn = new QPushButton("Стоп");
    stopBtn->setDisabled(true);
    connect(stopBtn, SIGNAL(clicked(bool)), SLOT(show_stop()));

    bindAddrInput = new QLineEdit;
    bindAddrInput->setMaxLength(21);
    bindAddrInput->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    bindAddrInput->setText(SocketReader::getLocalIp().append(":").append(defaultPort));

    QVBoxLayout *toolsL = new QVBoxLayout;
    toolsL->addStretch();
    toolsL->addWidget(new QLabel("IP-адрес:Порт"));
    toolsL->addWidget(bindAddrInput);
    toolsL->addWidget(startBtn, 0, Qt::AlignRight | Qt::AlignBottom);
    toolsL->addWidget(stopBtn, 0, Qt::AlignRight | Qt::AlignBottom);

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *hBoxL = new QHBoxLayout;

    hBoxL->addWidget(monitor);
    hBoxL->addLayout(toolsL);

    centralWidget->setLayout(hBoxL);
    setCentralWidget(centralWidget);

    startBtn->setFocus();
}

MainWindow::~MainWindow()
{
    delete startBtn;
    delete stopBtn;
    delete bindAddrInput;
}

void MainWindow::show_start()
{
    bindAddrInput->setDisabled(true);
    startBtn->setDisabled(true);
    stopBtn->setFocus();
    stopBtn->setEnabled(true);

    QStringList socketAddr = bindAddrInput->text().split(':');
    monitor->startTranslation(socketAddr.at(0), socketAddr.at(1).toInt());
}

void MainWindow::show_stop()
{
    bindAddrInput->setEnabled(true);
    startBtn->setEnabled(true);
    stopBtn->setDisabled(true);
    startBtn->setFocus();

    monitor->stopTranslation();
}
