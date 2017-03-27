/********************************************************************************
** Form generated from reading UI file 'userlogon.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLOGON_H
#define UI_USERLOGON_H

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

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QLineEdit *editHostDB;
    QHBoxLayout *horizontalLayout;
    QLabel *label_13;
    QLineEdit *editUserDb;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_15;
    QLineEdit *editPassDB;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *bnConnect;
    QPushButton *bnCancel;
    QTextEdit *textEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(275, 154);
        Dialog->setMinimumSize(QSize(275, 154));
        Dialog->setMaximumSize(QSize(275, 154));
        QIcon icon;
        icon.addFile(QStringLiteral(":/connection_state/Common/Icons/16x16freeapplicationicons/ico/Database.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(45, 0));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_8);

        editHostDB = new QLineEdit(groupBox);
        editHostDB->setObjectName(QStringLiteral("editHostDB"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editHostDB->sizePolicy().hasHeightForWidth());
        editHostDB->setSizePolicy(sizePolicy1);
        editHostDB->setFont(font);

        horizontalLayout_13->addWidget(editHostDB);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setMinimumSize(QSize(45, 0));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_13);

        editUserDb = new QLineEdit(groupBox);
        editUserDb->setObjectName(QStringLiteral("editUserDb"));
        sizePolicy1.setHeightForWidth(editUserDb->sizePolicy().hasHeightForWidth());
        editUserDb->setSizePolicy(sizePolicy1);
        editUserDb->setMinimumSize(QSize(110, 0));
        editUserDb->setFont(font);

        horizontalLayout->addWidget(editUserDb);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setMinimumSize(QSize(45, 0));
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_15);

        editPassDB = new QLineEdit(groupBox);
        editPassDB->setObjectName(QStringLiteral("editPassDB"));
        sizePolicy1.setHeightForWidth(editPassDB->sizePolicy().hasHeightForWidth());
        editPassDB->setSizePolicy(sizePolicy1);
        editPassDB->setFont(font);
        editPassDB->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(editPassDB);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        bnConnect = new QPushButton(Dialog);
        bnConnect->setObjectName(QStringLiteral("bnConnect"));

        horizontalLayout_3->addWidget(bnConnect);

        bnCancel = new QPushButton(Dialog);
        bnCancel->setObjectName(QStringLiteral("bnCancel"));

        horizontalLayout_3->addWidget(bnCancel);


        verticalLayout->addLayout(horizontalLayout_3);

        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        textEdit->setMinimumSize(QSize(0, 1));
        textEdit->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(textEdit);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "System logon", 0));
        groupBox->setTitle(QString());
        label_8->setText(QApplication::translate("Dialog", "Host", 0));
        editHostDB->setText(QApplication::translate("Dialog", "169.254.1.1", 0));
        label_13->setText(QApplication::translate("Dialog", "User", 0));
        editUserDb->setText(QApplication::translate("Dialog", "postgres", 0));
        label_15->setText(QApplication::translate("Dialog", "Pass", 0));
        editPassDB->setText(QApplication::translate("Dialog", "123", 0));
        bnConnect->setText(QApplication::translate("Dialog", "Connect", 0));
        bnCancel->setText(QApplication::translate("Dialog", "Cancel", 0));
    } // retranslateUi
    
    void resizeDialog(QDialog *Dialog, int height)
    {
      Dialog->setMaximumSize(QSize(275, 16777215));
      Dialog->resize(275, height);
    }
};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLOGON_H
