/********************************************************************************
** Form generated from reading UI file 'sv_planHG6116.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_PLANHG6116_H
#define SV_PLANHG6116_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SvPlanDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layoutID;
    QLabel *lblID;
    QLineEdit *editID;
    QHBoxLayout *layoutPlanName;
    QLabel *lblPlanName;
    QLineEdit *editPlanName;
    QHBoxLayout *layoutImgPath;
    QLabel *lblImgPath;
    QLineEdit *editImgPath;
    QPushButton *bnImgPath;
    QVBoxLayout *layoutDescription;
    QLabel *lblDescription;
    QTextEdit *textDescription;
    QHBoxLayout *layoutButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnSave;
    QPushButton *bnCancel;
    
    enum ShowMode { smNew = 0, smEdit = 1 };
    
    void setupUi(QDialog *SvPlanDialog = 0,
                 QString planName = "",
                 QString planImgPath = "",
                 QString description = "",
                 int id = -1,
                 int showMode = smNew)
    {
      if (SvPlanDialog->objectName().isEmpty())
           SvPlanDialog->setObjectName(QStringLiteral("SvPlanDialog"));
       SvPlanDialog->resize(370, 248);
       verticalLayout_2 = new QVBoxLayout(SvPlanDialog);
       verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
       groupBox = new QGroupBox(SvPlanDialog);
       groupBox->setObjectName(QStringLiteral("groupBox"));
       QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
       sizePolicy.setHorizontalStretch(0);
       sizePolicy.setVerticalStretch(0);
       sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
       groupBox->setSizePolicy(sizePolicy);
       verticalLayout = new QVBoxLayout(groupBox);
       verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
       layoutID = new QHBoxLayout();
       layoutID->setObjectName(QStringLiteral("layoutID"));
       lblID = new QLabel(groupBox);
       lblID->setObjectName(QStringLiteral("lblID"));
       QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
       sizePolicy1.setHorizontalStretch(0);
       sizePolicy1.setVerticalStretch(0);
       sizePolicy1.setHeightForWidth(lblID->sizePolicy().hasHeightForWidth());
       lblID->setSizePolicy(sizePolicy1);
       lblID->setMinimumSize(QSize(75, 0));
       lblID->setMaximumSize(QSize(75, 16777215));
       lblID->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

       layoutID->addWidget(lblID);

       editID = new QLineEdit(groupBox);
       editID->setObjectName(QStringLiteral("editID"));
       editID->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
       editID->setReadOnly(true);

       layoutID->addWidget(editID);


       verticalLayout->addLayout(layoutID);

       layoutPlanName = new QHBoxLayout();
       layoutPlanName->setObjectName(QStringLiteral("layoutPlanName"));
       lblPlanName = new QLabel(groupBox);
       lblPlanName->setObjectName(QStringLiteral("lblPlanName"));
       sizePolicy1.setHeightForWidth(lblPlanName->sizePolicy().hasHeightForWidth());
       lblPlanName->setSizePolicy(sizePolicy1);
       lblPlanName->setMinimumSize(QSize(75, 0));
       lblPlanName->setMaximumSize(QSize(75, 16777215));
       lblPlanName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

       layoutPlanName->addWidget(lblPlanName);

       editPlanName = new QLineEdit(groupBox);
       editPlanName->setObjectName(QStringLiteral("editPlanName"));

       layoutPlanName->addWidget(editPlanName);


       verticalLayout->addLayout(layoutPlanName);

       layoutImgPath = new QHBoxLayout();
       layoutImgPath->setObjectName(QStringLiteral("layoutImgPath"));
       lblImgPath = new QLabel(groupBox);
       lblImgPath->setObjectName(QStringLiteral("lblImgPath"));
       sizePolicy1.setHeightForWidth(lblImgPath->sizePolicy().hasHeightForWidth());
       lblImgPath->setSizePolicy(sizePolicy1);
       lblImgPath->setMinimumSize(QSize(75, 0));
       lblImgPath->setMaximumSize(QSize(75, 16777215));
       lblImgPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

       layoutImgPath->addWidget(lblImgPath);

       editImgPath = new QLineEdit(groupBox);
       editImgPath->setObjectName(QStringLiteral("editImgPath"));

       layoutImgPath->addWidget(editImgPath);

       bnImgPath = new QPushButton(groupBox);
       bnImgPath->setObjectName(QStringLiteral("bnImgPath"));
       QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
       sizePolicy2.setHorizontalStretch(0);
       sizePolicy2.setVerticalStretch(0);
       sizePolicy2.setHeightForWidth(bnImgPath->sizePolicy().hasHeightForWidth());
       bnImgPath->setSizePolicy(sizePolicy2);
       bnImgPath->setMinimumSize(QSize(23, 0));
       bnImgPath->setMaximumSize(QSize(23, 16777215));

       layoutImgPath->addWidget(bnImgPath);


       verticalLayout->addLayout(layoutImgPath);

       layoutDescription = new QVBoxLayout();
       layoutDescription->setObjectName(QStringLiteral("layoutDescription"));
       lblDescription = new QLabel(groupBox);
       lblDescription->setObjectName(QStringLiteral("lblDescription"));
       sizePolicy1.setHeightForWidth(lblDescription->sizePolicy().hasHeightForWidth());
       lblDescription->setSizePolicy(sizePolicy1);
       lblDescription->setMinimumSize(QSize(55, 0));
       lblDescription->setMaximumSize(QSize(55, 16777215));
       lblDescription->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

       layoutDescription->addWidget(lblDescription);

       textDescription = new QTextEdit(groupBox);
       textDescription->setObjectName(QStringLiteral("textDescription"));

       layoutDescription->addWidget(textDescription);


       verticalLayout->addLayout(layoutDescription);


       verticalLayout_2->addWidget(groupBox);

       layoutButtons = new QHBoxLayout();
       layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
       horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

       layoutButtons->addItem(horizontalSpacer);

       bnSave = new QPushButton(SvPlanDialog);
       bnSave->setObjectName(QStringLiteral("bnSave"));
       sizePolicy2.setHeightForWidth(bnSave->sizePolicy().hasHeightForWidth());
       bnSave->setSizePolicy(sizePolicy2);
       bnSave->setMaximumSize(QSize(80, 16777215));
       bnSave->setDefault(true);

       layoutButtons->addWidget(bnSave);

       bnCancel = new QPushButton(SvPlanDialog);
       bnCancel->setObjectName(QStringLiteral("bnCancel"));
       sizePolicy2.setHeightForWidth(bnCancel->sizePolicy().hasHeightForWidth());
       bnCancel->setSizePolicy(sizePolicy2);
       bnCancel->setMaximumSize(QSize(80, 16777215));

       layoutButtons->addWidget(bnCancel);


       verticalLayout_2->addLayout(layoutButtons);

       QWidget::setTabOrder(editPlanName, editImgPath);
       QWidget::setTabOrder(editImgPath, bnImgPath);
       QWidget::setTabOrder(bnImgPath, bnSave);
       QWidget::setTabOrder(bnSave, bnCancel);
       QWidget::setTabOrder(bnCancel, editID);
       QWidget::setTabOrder(editID, textDescription);
        
        editPlanName->setText(planName);
        editImgPath->setText(planImgPath);
        textDescription->setText(description);

        retranslateUi(SvPlanDialog, showMode, planName);

        QMetaObject::connectSlotsByName(SvPlanDialog);
    } // setupUi

    void retranslateUi(QDialog *SvPlanDialog, int showMode, QString planName)
    {
      QString title;
      title = QApplication::translate("SvPlanDialog", "Brand - ", 0);
      if(showMode = smNew)
        title = title + QApplication::translate("SvPlanDialog", "New", 0);
      else title = title + planName;
      SvPlanDialog->setWindowTitle(title);

        groupBox->setTitle(QString());
        lblID->setText(QApplication::translate("SvPlanDialog", "ID", 0));
        lblPlanName->setText(QApplication::translate("SvPlanDialog", "Plan name", 0));
        lblImgPath->setText(QApplication::translate("SvPlanDialog", "Image file", 0));
        bnImgPath->setText(QApplication::translate("SvPlanDialog", "...", 0));
        lblDescription->setText(QApplication::translate("SvPlanDialog", "Description", 0));
        bnSave->setText(QApplication::translate("SvPlanDialog", "Save", 0));
        bnCancel->setText(QApplication::translate("SvPlanDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SvPlanDialog: public Ui_SvPlanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_PLANHG6116_H
