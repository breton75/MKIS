/********************************************************************************
** Form generated from reading UI file 'sv_new_zoneoTE884.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_NEW_ZONEOTE884_H
#define SV_NEW_ZONEOTE884_H

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

class Ui_SvNewZoneDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *layoutID;
    QLabel *lblID;
    QLineEdit *editID;
    QHBoxLayout *layoutZoneName;
    QLabel *lblZoneName;
    QLineEdit *editZoneName;
    QHBoxLayout *layoutParentZone;
    QLabel *lblParentZoneName;
    QLineEdit *editParentZoneName;
    QPushButton *bnSelectParentZone;
    QGroupBox *gbChildable;
    QHBoxLayout *horizontalLayout;
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

    void setupUi(QDialog *SvNewZoneDialog)
    {
        if (SvNewZoneDialog->objectName().isEmpty())
            SvNewZoneDialog->setObjectName(QStringLiteral("SvNewZoneDialog"));
        SvNewZoneDialog->resize(370, 312);
        verticalLayout_2 = new QVBoxLayout(SvNewZoneDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(SvNewZoneDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
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


        verticalLayout_3->addLayout(layoutID);

        layoutZoneName = new QHBoxLayout();
        layoutZoneName->setObjectName(QStringLiteral("layoutZoneName"));
        lblZoneName = new QLabel(groupBox);
        lblZoneName->setObjectName(QStringLiteral("lblZoneName"));
        sizePolicy1.setHeightForWidth(lblZoneName->sizePolicy().hasHeightForWidth());
        lblZoneName->setSizePolicy(sizePolicy1);
        lblZoneName->setMinimumSize(QSize(75, 0));
        lblZoneName->setMaximumSize(QSize(75, 16777215));
        lblZoneName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutZoneName->addWidget(lblZoneName);

        editZoneName = new QLineEdit(groupBox);
        editZoneName->setObjectName(QStringLiteral("editZoneName"));

        layoutZoneName->addWidget(editZoneName);


        verticalLayout_3->addLayout(layoutZoneName);

        layoutParentZone = new QHBoxLayout();
        layoutParentZone->setSpacing(6);
        layoutParentZone->setObjectName(QStringLiteral("layoutParentZone"));
        lblParentZoneName = new QLabel(groupBox);
        lblParentZoneName->setObjectName(QStringLiteral("lblParentZoneName"));
        lblParentZoneName->setMinimumSize(QSize(75, 0));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        lblParentZoneName->setFont(font);
        lblParentZoneName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutParentZone->addWidget(lblParentZoneName);

        editParentZoneName = new QLineEdit(groupBox);
        editParentZoneName->setObjectName(QStringLiteral("editParentZoneName"));
        editParentZoneName->setFont(font);
        editParentZoneName->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
        editParentZoneName->setReadOnly(true);

        layoutParentZone->addWidget(editParentZoneName);

        bnSelectParentZone = new QPushButton(groupBox);
        bnSelectParentZone->setObjectName(QStringLiteral("bnSelectParentZone"));
        bnSelectParentZone->setMaximumSize(QSize(26, 16777215));
        bnSelectParentZone->setFont(font);

        layoutParentZone->addWidget(bnSelectParentZone);


        verticalLayout_3->addLayout(layoutParentZone);

        gbChildable = new QGroupBox(groupBox);
        gbChildable->setObjectName(QStringLiteral("gbChildable"));
        gbChildable->setCheckable(true);
        gbChildable->setChecked(false);
        horizontalLayout = new QHBoxLayout(gbChildable);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblImgPath = new QLabel(gbChildable);
        lblImgPath->setObjectName(QStringLiteral("lblImgPath"));
        lblImgPath->setEnabled(false);
        sizePolicy1.setHeightForWidth(lblImgPath->sizePolicy().hasHeightForWidth());
        lblImgPath->setSizePolicy(sizePolicy1);
        lblImgPath->setMinimumSize(QSize(65, 0));
        lblImgPath->setMaximumSize(QSize(65, 16777215));
        lblImgPath->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lblImgPath);

        editImgPath = new QLineEdit(gbChildable);
        editImgPath->setObjectName(QStringLiteral("editImgPath"));
        editImgPath->setEnabled(false);

        horizontalLayout->addWidget(editImgPath);

        bnImgPath = new QPushButton(gbChildable);
        bnImgPath->setObjectName(QStringLiteral("bnImgPath"));
        bnImgPath->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(bnImgPath->sizePolicy().hasHeightForWidth());
        bnImgPath->setSizePolicy(sizePolicy2);
        bnImgPath->setMinimumSize(QSize(23, 0));
        bnImgPath->setMaximumSize(QSize(23, 16777215));
        bnImgPath->setCheckable(false);

        horizontalLayout->addWidget(bnImgPath);


        verticalLayout_3->addWidget(gbChildable);

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


        verticalLayout_3->addLayout(layoutDescription);


        verticalLayout_2->addWidget(groupBox);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutButtons->addItem(horizontalSpacer);

        bnSave = new QPushButton(SvNewZoneDialog);
        bnSave->setObjectName(QStringLiteral("bnSave"));
        sizePolicy2.setHeightForWidth(bnSave->sizePolicy().hasHeightForWidth());
        bnSave->setSizePolicy(sizePolicy2);
        bnSave->setMaximumSize(QSize(80, 16777215));
        bnSave->setDefault(true);

        layoutButtons->addWidget(bnSave);

        bnCancel = new QPushButton(SvNewZoneDialog);
        bnCancel->setObjectName(QStringLiteral("bnCancel"));
        sizePolicy2.setHeightForWidth(bnCancel->sizePolicy().hasHeightForWidth());
        bnCancel->setSizePolicy(sizePolicy2);
        bnCancel->setMaximumSize(QSize(80, 16777215));

        layoutButtons->addWidget(bnCancel);


        verticalLayout_2->addLayout(layoutButtons);

        QWidget::setTabOrder(editZoneName, bnSave);
        QWidget::setTabOrder(bnSave, bnCancel);
        QWidget::setTabOrder(bnCancel, editID);
        QWidget::setTabOrder(editID, textDescription);

        retranslateUi(SvNewZoneDialog);

        QMetaObject::connectSlotsByName(SvNewZoneDialog);
    } // setupUi

    void retranslateUi(QDialog *SvNewZoneDialog)
    {
        SvNewZoneDialog->setWindowTitle(QApplication::translate("SvNewZoneDialog", "\320\235\320\276\320\262\320\260\321\217 \320\267\320\276\320\275\320\260 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\320\270", 0));
        groupBox->setTitle(QString());
        lblID->setText(QApplication::translate("SvNewZoneDialog", "ID", 0));
        lblZoneName->setText(QApplication::translate("SvNewZoneDialog", "\320\230\320\274\321\217 \320\267\320\276\320\275\321\213", 0));
        lblParentZoneName->setText(QApplication::translate("SvNewZoneDialog", "\320\222\321\205\320\276\320\264\320\270\321\202 \320\262 \320\267\320\276\320\275\321\203", 0));
        bnSelectParentZone->setText(QApplication::translate("SvNewZoneDialog", "...", 0));
        gbChildable->setTitle(QApplication::translate("SvNewZoneDialog", "\320\227\320\276\320\275\320\260 \320\274\320\276\320\266\320\265\321\202 \320\270\320\274\320\265\321\202\321\214 \320\264\320\276\321\207\320\265\321\200\320\275\320\270\320\265 \320\267\320\276\320\275\321\213", 0));
        lblImgPath->setText(QApplication::translate("SvNewZoneDialog", "\320\237\320\273\320\260\320\275/\320\241\321\205\320\265\320\274\320\260", 0));
        bnImgPath->setText(QApplication::translate("SvNewZoneDialog", "...", 0));
        lblDescription->setText(QApplication::translate("SvNewZoneDialog", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0));
        bnSave->setText(QApplication::translate("SvNewZoneDialog", "Save", 0));
        bnCancel->setText(QApplication::translate("SvNewZoneDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui_nz {
    class SvNewZoneDialog: public Ui_SvNewZoneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_NEW_ZONEOTE884_H
