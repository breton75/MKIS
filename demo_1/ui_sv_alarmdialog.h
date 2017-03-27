/********************************************************************************
** Form generated from reading UI file 'sv_alarmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SV_ALARMDIALOG_H
#define UI_SV_ALARMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SvAlarmDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *bnIgnore;
    QSpacerItem *spacer_1;
    QToolBox *toolBox;
    QWidget *pageZone;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *vlayZone;
    QWidget *pageDetails;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *vlayDetails;

    void setupUi(QDialog *SvAlarmDialog)
    {
        if (SvAlarmDialog->objectName().isEmpty())
            SvAlarmDialog->setObjectName(QStringLiteral("SvAlarmDialog"));
        SvAlarmDialog->resize(854, 633);
        verticalLayout = new QVBoxLayout(SvAlarmDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(SvAlarmDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(0, 24));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        bnIgnore = new QPushButton(frame);
        bnIgnore->setObjectName(QStringLiteral("bnIgnore"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/alarms/icons/bullet_red.png"), QSize(), QIcon::Normal, QIcon::Off);
        bnIgnore->setIcon(icon);

        horizontalLayout->addWidget(bnIgnore);

        spacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer_1);


        verticalLayout->addWidget(frame);

        toolBox = new QToolBox(SvAlarmDialog);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        toolBox->setFont(font);
        toolBox->setFrameShape(QFrame::Panel);
        toolBox->setFrameShadow(QFrame::Sunken);
        pageZone = new QWidget();
        pageZone->setObjectName(QStringLiteral("pageZone"));
        pageZone->setGeometry(QRect(0, 0, 834, 517));
        verticalLayout_3 = new QVBoxLayout(pageZone);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        vlayZone = new QVBoxLayout();
        vlayZone->setSpacing(2);
        vlayZone->setObjectName(QStringLiteral("vlayZone"));

        verticalLayout_3->addLayout(vlayZone);

        QIcon icon1;
        icon1.addFile(QStringLiteral(":/tree32/icons/layers_1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(pageZone, icon1, QString::fromUtf8("\320\227\320\276\320\275\320\260 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\320\270"));
        pageDetails = new QWidget();
        pageDetails->setObjectName(QStringLiteral("pageDetails"));
        pageDetails->setGeometry(QRect(0, 0, 98, 28));
        verticalLayout_5 = new QVBoxLayout(pageDetails);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        vlayDetails = new QVBoxLayout();
        vlayDetails->setObjectName(QStringLiteral("vlayDetails"));

        verticalLayout_5->addLayout(vlayDetails);

        QIcon icon2;
        icon2.addFile(QStringLiteral(":/tree32/icons/Eye.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        toolBox->addItem(pageDetails, icon2, QString::fromUtf8("\320\224\320\265\321\202\320\260\320\273\321\214\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217"));

        verticalLayout->addWidget(toolBox);


        retranslateUi(SvAlarmDialog);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SvAlarmDialog);
    } // setupUi

    void retranslateUi(QDialog *SvAlarmDialog)
    {
        SvAlarmDialog->setWindowTitle(QApplication::translate("SvAlarmDialog", "Dialog", 0));
        bnIgnore->setText(QApplication::translate("SvAlarmDialog", "\320\230\320\263\320\275\320\276\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0));
        toolBox->setItemText(toolBox->indexOf(pageZone), QApplication::translate("SvAlarmDialog", "\320\227\320\276\320\275\320\260 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\320\270", 0));
        toolBox->setItemText(toolBox->indexOf(pageDetails), QApplication::translate("SvAlarmDialog", "\320\224\320\265\321\202\320\260\320\273\321\214\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class SvAlarmDialog: public Ui_SvAlarmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SV_ALARMDIALOG_H
