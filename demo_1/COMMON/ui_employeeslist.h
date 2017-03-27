/********************************************************************************
** Form generated from reading UI file 'sv_classeslistV11712.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_EMPLOYEESLISTV11712_H
#define SV_EMPLOYEESLISTV11712_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SvEmployeesListDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableView  *tblEmployeesList;
    QHBoxLayout *layoutButtons;
    QPushButton *bnNewEmployee;
    QPushButton *bnEditEmployee;
    QPushButton *bnDeleteEmployee;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnSelect;
    QPushButton *bnClose;

    void setupUi(QDialog *SvEmployeesListDialog)
    {
        if (SvEmployeesListDialog->objectName().isEmpty())
            SvEmployeesListDialog->setObjectName(QStringLiteral("SvEmployeesListDialog"));
        SvEmployeesListDialog->resize(661, 377);
        verticalLayout = new QVBoxLayout(SvEmployeesListDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tblEmployeesList = new QTableView(SvEmployeesListDialog);
        tblEmployeesList->setObjectName(QStringLiteral("tblEmployeesList"));

        verticalLayout->addWidget(tblEmployeesList);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
        bnNewEmployee = new QPushButton(SvEmployeesListDialog);
        bnNewEmployee->setObjectName(QStringLiteral("bnNewEmployee"));

        layoutButtons->addWidget(bnNewEmployee);

        bnEditEmployee = new QPushButton(SvEmployeesListDialog);
        bnEditEmployee->setObjectName(QStringLiteral("bnEditEmployee"));

        layoutButtons->addWidget(bnEditEmployee);

        bnDeleteEmployee = new QPushButton(SvEmployeesListDialog);
        bnDeleteEmployee->setObjectName(QStringLiteral("bnDeleteEmployee"));

        layoutButtons->addWidget(bnDeleteEmployee);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutButtons->addItem(horizontalSpacer);

        bnSelect = new QPushButton(SvEmployeesListDialog);
        bnSelect->setObjectName(QStringLiteral("bnSelect"));

        layoutButtons->addWidget(bnSelect);

        bnClose = new QPushButton(SvEmployeesListDialog);
        bnClose->setObjectName(QStringLiteral("bnClose"));

        layoutButtons->addWidget(bnClose);


        verticalLayout->addLayout(layoutButtons);


        retranslateUi(SvEmployeesListDialog);

        QMetaObject::connectSlotsByName(SvEmployeesListDialog);
    } // setupUi

    void retranslateUi(QDialog *SvEmployeesListDialog)
    {
        SvEmployeesListDialog->setWindowTitle(QApplication::translate("SvEmployeesListDialog", "Dialog", 0));
        bnNewEmployee->setText(QApplication::translate("SvEmployeesListDialog", "New", 0));
        bnEditEmployee->setText(QApplication::translate("SvEmployeesListDialog", "Edit", 0));
        bnDeleteEmployee->setText(QApplication::translate("SvEmployeesListDialog", "Delete", 0));
        bnSelect->setText(QApplication::translate("SvEmployeesListDialog", "Select", 0));
        bnClose->setText(QApplication::translate("SvEmployeesListDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class SvEmployeesListDialog: public Ui_SvEmployeesListDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_EMPLOYEESLISTV11712_H
