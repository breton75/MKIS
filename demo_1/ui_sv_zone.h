/********************************************************************************
** Form generated from reading UI file 'sv_zoneSg6412.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_ZONESG6412_H
#define SV_ZONESG6412_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SvZoneDialog
{
public:
    QAction *actionAddNode;
    QAction *actionAddDevice;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QToolButton *bnAddNode;
    QSpacerItem *spacer_1;
    QToolButton *bnZoomIn;
    QToolButton *bnZoomOut;
    QSpacerItem *spacer_2;
    QToolButton *bnExpandTree;
    QSpacerItem *spacer_3;
    QToolButton *bnAddDevice;
    QToolButton *bnDeleteDevice;
    QSpacerItem *spacer_4;
    QLabel *lblPlanName;
    QSpacerItem *spacer_5;
    QHBoxLayout *hlayMain;
    QHBoxLayout *layoutButtons;
    QSpacerItem *spacer_6;
    QPushButton *bnApply;
    QPushButton *bnSaveClose;
    QPushButton *bnCancel;

    void setupUi(QDialog *SvZoneDialog, QString planName)
    {
      if (SvZoneDialog->objectName().isEmpty())
          SvZoneDialog->setObjectName(QStringLiteral("SvZoneDialog"));
      SvZoneDialog->setWindowModality(Qt::WindowModal);
      SvZoneDialog->resize(883, 648);
      QIcon icon;
      icon.addFile(QStringLiteral(":/tree32/icons/Shield_16.ico"), QSize(), QIcon::Normal, QIcon::Off);
      SvZoneDialog->setWindowIcon(icon);
      actionAddNode = new QAction(SvZoneDialog);
      actionAddNode->setObjectName(QStringLiteral("actionAddNode"));
      QIcon icon1;
      icon1.addFile(QStringLiteral(":/editors/icons/Plus2.ico"), QSize(), QIcon::Normal, QIcon::Off);
      actionAddNode->setIcon(icon1);
      actionAddDevice = new QAction(SvZoneDialog);
      actionAddDevice->setObjectName(QStringLiteral("actionAddDevice"));
      QIcon icon2;
      icon2.addFile(QStringLiteral(":/editors/icons/cpu_add_16.ico"), QSize(), QIcon::Normal, QIcon::Off);
      actionAddDevice->setIcon(icon2);
      verticalLayout_2 = new QVBoxLayout(SvZoneDialog);
      verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
      widget = new QWidget(SvZoneDialog);
      widget->setObjectName(QStringLiteral("widget"));
      QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
      widget->setSizePolicy(sizePolicy);
      verticalLayout = new QVBoxLayout(widget);
      verticalLayout->setSpacing(6);
      verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
      verticalLayout->setContentsMargins(2, 2, 2, 2);
      frame = new QFrame(widget);
      frame->setObjectName(QStringLiteral("frame"));
      QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
      frame->setSizePolicy(sizePolicy1);
      frame->setMinimumSize(QSize(0, 33));
      frame->setMaximumSize(QSize(16777215, 36));
      frame->setFrameShape(QFrame::Box);
      frame->setFrameShadow(QFrame::Raised);
      horizontalLayout = new QHBoxLayout(frame);
      horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
      horizontalLayout->setContentsMargins(-1, 2, -1, 2);
      bnAddNode = new QToolButton(frame);
      bnAddNode->setObjectName(QStringLiteral("bnAddNode"));
      bnAddNode->setMinimumSize(QSize(26, 26));
      bnAddNode->setMaximumSize(QSize(26, 26));
      QIcon icon3;
      icon3.addFile(QStringLiteral(":/tree32/icons/Plus2.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnAddNode->setIcon(icon3);

      horizontalLayout->addWidget(bnAddNode);

      spacer_1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      horizontalLayout->addItem(spacer_1);

      bnZoomIn = new QToolButton(frame);
      bnZoomIn->setObjectName(QStringLiteral("bnZoomIn"));
      bnZoomIn->setMinimumSize(QSize(26, 26));
      bnZoomIn->setMaximumSize(QSize(26, 26));
      QIcon icon4;
      icon4.addFile(QStringLiteral(":/icons/Zoom in.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnZoomIn->setIcon(icon4);

      horizontalLayout->addWidget(bnZoomIn);

      bnZoomOut = new QToolButton(frame);
      bnZoomOut->setObjectName(QStringLiteral("bnZoomOut"));
      bnZoomOut->setMinimumSize(QSize(26, 26));
      bnZoomOut->setMaximumSize(QSize(26, 26));
      QIcon icon5;
      icon5.addFile(QStringLiteral(":/icons/Zoom out.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnZoomOut->setIcon(icon5);

      horizontalLayout->addWidget(bnZoomOut);

      spacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      horizontalLayout->addItem(spacer_2);

      bnExpandTree = new QToolButton(frame);
      bnExpandTree->setObjectName(QStringLiteral("bnExpandTree"));
      bnExpandTree->setMinimumSize(QSize(26, 26));
      bnExpandTree->setMaximumSize(QSize(26, 26));
      QIcon icon6;
      icon6.addFile(QStringLiteral(":/icons/node-tree.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnExpandTree->setIcon(icon6);

      horizontalLayout->addWidget(bnExpandTree);

      spacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      horizontalLayout->addItem(spacer_3);

      bnAddDevice = new QToolButton(frame);
      bnAddDevice->setObjectName(QStringLiteral("bnAddDevice"));
      bnAddDevice->setMinimumSize(QSize(26, 26));
      QIcon icon7;
      icon7.addFile(QStringLiteral(":/icons/add_device.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnAddDevice->setIcon(icon7);

      horizontalLayout->addWidget(bnAddDevice);

      bnDeleteDevice = new QToolButton(frame);
      bnDeleteDevice->setObjectName(QStringLiteral("bnDeleteDevice"));
      bnDeleteDevice->setMinimumSize(QSize(26, 26));
      QIcon icon8;
      icon8.addFile(QStringLiteral(":/icons/delete_device.ico"), QSize(), QIcon::Normal, QIcon::Off);
      bnDeleteDevice->setIcon(icon8);

      horizontalLayout->addWidget(bnDeleteDevice);

      spacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      horizontalLayout->addItem(spacer_4);

      lblPlanName = new QLabel(frame);
      lblPlanName->setObjectName(QStringLiteral("lblPlanName"));
      QPalette palette;
      QBrush brush(QColor(255, 0, 0, 255));
      brush.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
      palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
      QBrush brush1(QColor(120, 120, 120, 255));
      brush1.setStyle(Qt::SolidPattern);
      palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
      lblPlanName->setPalette(palette);
      QFont font;
      font.setFamily(QStringLiteral("Arial"));
      font.setPointSize(10);
      font.setBold(true);
      font.setWeight(75);
      lblPlanName->setFont(font);
      lblPlanName->setFrameShadow(QFrame::Plain);
      lblPlanName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      horizontalLayout->addWidget(lblPlanName);

      spacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      horizontalLayout->addItem(spacer_5);


      verticalLayout->addWidget(frame);

      hlayMain = new QHBoxLayout();
      hlayMain->setSpacing(2);
      hlayMain->setObjectName(QStringLiteral("hlayMain"));

      verticalLayout->addLayout(hlayMain);


      verticalLayout_2->addWidget(widget);

      layoutButtons = new QHBoxLayout();
      layoutButtons->setSpacing(6);
      layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
      spacer_6 = new QSpacerItem(148, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

      layoutButtons->addItem(spacer_6);

      bnApply = new QPushButton(SvZoneDialog);
      bnApply->setObjectName(QStringLiteral("bnApply"));

      layoutButtons->addWidget(bnApply);

      bnSaveClose = new QPushButton(SvZoneDialog);
      bnSaveClose->setObjectName(QStringLiteral("bnSaveClose"));

      layoutButtons->addWidget(bnSaveClose);

      bnCancel = new QPushButton(SvZoneDialog);
      bnCancel->setObjectName(QStringLiteral("bnCancel"));

      layoutButtons->addWidget(bnCancel);


      verticalLayout_2->addLayout(layoutButtons);


        retranslateUi(SvZoneDialog, planName);

        QMetaObject::connectSlotsByName(SvZoneDialog);
    } // setupUi

    void retranslateUi(QDialog *SvZoneDialog, QString planName)
    {
      SvZoneDialog->setWindowTitle(QApplication::translate("SvZoneDialog", "\320\227\320\276\320\275\320\260 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\320\270: ", 0));
      actionAddNode->setText(QApplication::translate("SvZoneDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\320\267\320\265\320\273", 0));
      actionAddDevice->setText(QApplication::translate("SvZoneDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0));
#ifndef QT_NO_TOOLTIP
      actionAddDevice->setToolTip(QApplication::translate("SvZoneDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", 0));
#endif // QT_NO_TOOLTIP
      bnAddNode->setText(QApplication::translate("SvZoneDialog", "...", 0));
      bnZoomIn->setText(QApplication::translate("SvZoneDialog", "...", 0));
      bnZoomOut->setText(QApplication::translate("SvZoneDialog", "...", 0));
      bnExpandTree->setText(QApplication::translate("SvZoneDialog", "...", 0));
      bnAddDevice->setText(QApplication::translate("SvZoneDialog", "...", 0));
      bnDeleteDevice->setText(QApplication::translate("SvZoneDialog", "...", 0));
      QString s = "\320\237\320\273\320\260\320\275 \321\201\321\205\320\265\320\274\320\260: " + planName;
      lblPlanName->setText(QApplication::translate("SvZoneDialog", s.toStdString().c_str(), 0));
      bnApply->setText(QApplication::translate("SvZoneDialog", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", 0));
      bnSaveClose->setText(QApplication::translate("SvZoneDialog", "\320\236K", 0));
      bnCancel->setText(QApplication::translate("SvZoneDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SvZoneDialog: public Ui_SvZoneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_ZONESG6412_H
