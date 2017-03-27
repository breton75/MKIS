/********************************************************************************
** Form generated from reading UI file 'sv_zoneslistlJ6540.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_ZONESLISTLJ6540_H
#define SV_ZONESLISTLJ6540_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SvZonesListDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *vlay;
    QHBoxLayout *layoutButtons;
    QPushButton *bnNewZone;
    QPushButton *bnEditZone;
    QPushButton *bnDeleteZone;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnSelect;
    QPushButton *bnClose;

    void setupUi(QDialog *SvZonesListDialog)
    {
        if (SvZonesListDialog->objectName().isEmpty())
            SvZonesListDialog->setObjectName(QStringLiteral("SvZonesListDialog"));
        SvZonesListDialog->resize(750, 652);
        verticalLayout = new QVBoxLayout(SvZonesListDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(SvZonesListDialog);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        vlay = new QVBoxLayout();
        vlay->setObjectName(QStringLiteral("vlay"));

        verticalLayout_3->addLayout(vlay);


        verticalLayout->addWidget(widget);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
        bnNewZone = new QPushButton(SvZonesListDialog);
        bnNewZone->setObjectName(QStringLiteral("bnNewZone"));

        layoutButtons->addWidget(bnNewZone);

        bnEditZone = new QPushButton(SvZonesListDialog);
        bnEditZone->setObjectName(QStringLiteral("bnEditZone"));

        layoutButtons->addWidget(bnEditZone);

        bnDeleteZone = new QPushButton(SvZonesListDialog);
        bnDeleteZone->setObjectName(QStringLiteral("bnDeleteZone"));

        layoutButtons->addWidget(bnDeleteZone);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutButtons->addItem(horizontalSpacer);

        bnSelect = new QPushButton(SvZonesListDialog);
        bnSelect->setObjectName(QStringLiteral("bnSelect"));

        layoutButtons->addWidget(bnSelect);

        bnClose = new QPushButton(SvZonesListDialog);
        bnClose->setObjectName(QStringLiteral("bnClose"));

        layoutButtons->addWidget(bnClose);


        verticalLayout->addLayout(layoutButtons);


        retranslateUi(SvZonesListDialog);

        QMetaObject::connectSlotsByName(SvZonesListDialog);
    } // setupUi

    void retranslateUi(QDialog *SvZonesListDialog)
    {
        SvZonesListDialog->setWindowTitle(QApplication::translate("SvZonesListDialog", "Dialog", 0));
        bnNewZone->setText(QApplication::translate("SvZonesListDialog", "New", 0));
        bnEditZone->setText(QApplication::translate("SvZonesListDialog", "Edit", 0));
        bnDeleteZone->setText(QApplication::translate("SvZonesListDialog", "Delete", 0));
        bnSelect->setText(QApplication::translate("SvZonesListDialog", "Select", 0));
        bnClose->setText(QApplication::translate("SvZonesListDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class SvZonesListDialog: public Ui_SvZonesListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_ZONESLISTLJ6540_H
