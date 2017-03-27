/********************************************************************************
** Form generated from reading UI file 'sv_rls2bit2filesettingsOJ1244.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_RLS2BIT2FILESETTINGSOJ1244_H
#define SV_RLS2BIT2FILESETTINGSOJ1244_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QComboBox>

QT_BEGIN_NAMESPACE

class Ui_SvRls2bit2FileSettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *gbMain;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *layoutDeviceName;
    QLabel *lblDeviceName;
    QLineEdit *editDeviceName;
    QHBoxLayout *layoutPort;
    QLabel *lblPort;
    QSpinBox *sbPort;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *layoutRotationSpeed;
    QLabel *lblRotationSpeed;
    QSpinBox *sbRotationSpeed;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *layoutSaveDirectory;
    QLabel *lblSaveDirectory;
    QLineEdit *editSaveDirectory;
    QPushButton *bnSelectSaveDirectory;
    QHBoxLayout *layoutFileDuration;
    QLabel *lblFileDuration;
    QTimeEdit *teFileDuration;
    QSpacerItem *spacerFileDuration;
    QHBoxLayout *layoutTotalDuration;
    QLabel *lblTotaDuration;
    QTimeEdit *teTotalDuration;
    QCheckBox *checkBoxTotalDuration;
    QSpacerItem *spacerTotalDuration;
    QGroupBox *gbFileName;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *layoutFileNameFormat;
    QLabel *lblFileNameFormat;
    QLineEdit *editFileNameFormat;
    QHBoxLayout *layoutDateTimeFormat;
    QLabel *lblDateTimeFormat;
    QLineEdit *editDateTimeFormat;
    QHBoxLayout *layoutUserName;
    QLabel *lblUserName;
    QLineEdit *editUserName;
    QHBoxLayout *layoutPassword;
    QLabel *lblPassword;
    QLineEdit *editPassword;
    QHBoxLayout *layoutDeviceTag;
    QLabel *lblDeviceTag;
    QLineEdit *editDeviceTag;
    QSpacerItem *vSpacer_2;
    QHBoxLayout *layoutButtons;
    QSpacerItem *spacerButtons;
    QPushButton *bnOk;
    QPushButton *bnCancel;
    
    QHBoxLayout *layoutArchServer;
    QComboBox *cbArchServer;
    QLabel *lblArchServer;

    void setupUi(QDialog *SvRls2bit2FileSettingsDialog)
    {
        if (SvRls2bit2FileSettingsDialog->objectName().isEmpty())
            SvRls2bit2FileSettingsDialog->setObjectName(QStringLiteral("SvRls2bit2FileSettingsDialog"));
        SvRls2bit2FileSettingsDialog->resize(451, 427);
        verticalLayout = new QVBoxLayout(SvRls2bit2FileSettingsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gbMain = new QGroupBox(SvRls2bit2FileSettingsDialog);
        gbMain->setObjectName(QStringLiteral("gbMain"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbMain->sizePolicy().hasHeightForWidth());
        gbMain->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(gbMain);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        layoutDeviceName = new QHBoxLayout();
        layoutDeviceName->setObjectName(QStringLiteral("layoutDeviceName"));
        lblDeviceName = new QLabel(gbMain);
        lblDeviceName->setObjectName(QStringLiteral("lblDeviceName"));
        lblDeviceName->setMinimumSize(QSize(99, 0));
        lblDeviceName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutDeviceName->addWidget(lblDeviceName);

        editDeviceName = new QLineEdit(gbMain);
        editDeviceName->setObjectName(QStringLiteral("editDeviceName"));
        editDeviceName->setEnabled(false);

        layoutDeviceName->addWidget(editDeviceName);


        verticalLayout_3->addLayout(layoutDeviceName);

        layoutPort = new QHBoxLayout();
        layoutPort->setObjectName(QStringLiteral("layoutPort"));
        lblPort = new QLabel(gbMain);
        lblPort->setObjectName(QStringLiteral("lblPort"));
        lblPort->setMinimumSize(QSize(99, 0));
        lblPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutPort->addWidget(lblPort);

        sbPort = new QSpinBox(gbMain);
        sbPort->setObjectName(QStringLiteral("sbPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sbPort->sizePolicy().hasHeightForWidth());
        sbPort->setSizePolicy(sizePolicy1);
        sbPort->setMinimumSize(QSize(90, 0));
        sbPort->setMinimum(0);
        sbPort->setMaximum(65535);
        sbPort->setValue(8000);

        layoutPort->addWidget(sbPort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutPort->addItem(horizontalSpacer);
        verticalLayout_3->addLayout(layoutPort);
        
        /***************************************************/
        layoutArchServer = new QHBoxLayout();
        layoutArchServer->setObjectName(QStringLiteral("layoutArchServer"));
        lblArchServer = new QLabel(gbMain);
        lblArchServer->setObjectName(QStringLiteral("lblArchServer"));
        QSizePolicy asSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        asSizePolicy.setHeightForWidth(lblArchServer->sizePolicy().hasHeightForWidth());
        lblArchServer->setSizePolicy(sizePolicy);
        lblArchServer->setMinimumSize(QSize(90, 0));
        lblArchServer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutArchServer->addWidget(lblArchServer);

        cbArchServer = new QComboBox(gbMain);
        cbArchServer->setObjectName(QStringLiteral("cbArchServer"));
        cbArchServer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layoutArchServer->addWidget(cbArchServer);
        verticalLayout_3->addLayout(layoutArchServer);
        
        /*********************************************************/

        layoutRotationSpeed = new QHBoxLayout();
        layoutRotationSpeed->setObjectName(QStringLiteral("layoutRotationSpeed"));
        lblRotationSpeed = new QLabel(gbMain);
        lblRotationSpeed->setObjectName(QStringLiteral("lblRotationSpeed"));
        lblRotationSpeed->setMinimumSize(QSize(99, 0));
        lblRotationSpeed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutRotationSpeed->addWidget(lblRotationSpeed);

        sbRotationSpeed = new QSpinBox(gbMain);
        sbRotationSpeed->setObjectName(QStringLiteral("sbRotationSpeed"));
        sizePolicy1.setHeightForWidth(sbRotationSpeed->sizePolicy().hasHeightForWidth());
        sbRotationSpeed->setSizePolicy(sizePolicy1);
        sbRotationSpeed->setMinimumSize(QSize(90, 0));
        sbRotationSpeed->setMinimum(1);
        sbRotationSpeed->setMaximum(8);
        sbRotationSpeed->setValue(6);

        layoutRotationSpeed->addWidget(sbRotationSpeed);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutRotationSpeed->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(layoutRotationSpeed);

        layoutSaveDirectory = new QHBoxLayout();
        layoutSaveDirectory->setObjectName(QStringLiteral("layoutSaveDirectory"));
        lblSaveDirectory = new QLabel(gbMain);
        lblSaveDirectory->setObjectName(QStringLiteral("lblSaveDirectory"));
        lblSaveDirectory->setMinimumSize(QSize(99, 0));
        lblSaveDirectory->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutSaveDirectory->addWidget(lblSaveDirectory);

        editSaveDirectory = new QLineEdit(gbMain);
        editSaveDirectory->setObjectName(QStringLiteral("editSaveDirectory"));

        layoutSaveDirectory->addWidget(editSaveDirectory);

        bnSelectSaveDirectory = new QPushButton(gbMain);
        bnSelectSaveDirectory->setObjectName(QStringLiteral("bnSelectSaveDirectory"));
        sizePolicy1.setHeightForWidth(bnSelectSaveDirectory->sizePolicy().hasHeightForWidth());
        bnSelectSaveDirectory->setSizePolicy(sizePolicy1);
        bnSelectSaveDirectory->setMaximumSize(QSize(24, 24));

        layoutSaveDirectory->addWidget(bnSelectSaveDirectory);


        verticalLayout_3->addLayout(layoutSaveDirectory);

        layoutFileDuration = new QHBoxLayout();
        layoutFileDuration->setObjectName(QStringLiteral("layoutFileDuration"));
        lblFileDuration = new QLabel(gbMain);
        lblFileDuration->setObjectName(QStringLiteral("lblFileDuration"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblFileDuration->sizePolicy().hasHeightForWidth());
        lblFileDuration->setSizePolicy(sizePolicy2);
        lblFileDuration->setMinimumSize(QSize(99, 0));
        lblFileDuration->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutFileDuration->addWidget(lblFileDuration);

        teFileDuration = new QTimeEdit(gbMain);
        teFileDuration->setObjectName(QStringLiteral("teFileDuration"));
        teFileDuration->setMinimumSize(QSize(90, 0));
        teFileDuration->setMaximumSize(QSize(90, 16777215));

        layoutFileDuration->addWidget(teFileDuration);

        spacerFileDuration = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutFileDuration->addItem(spacerFileDuration);


        verticalLayout_3->addLayout(layoutFileDuration);

        layoutTotalDuration = new QHBoxLayout();
        layoutTotalDuration->setObjectName(QStringLiteral("layoutTotalDuration"));
        lblTotaDuration = new QLabel(gbMain);
        lblTotaDuration->setObjectName(QStringLiteral("lblTotaDuration"));
        lblTotaDuration->setEnabled(false);
        sizePolicy2.setHeightForWidth(lblTotaDuration->sizePolicy().hasHeightForWidth());
        lblTotaDuration->setSizePolicy(sizePolicy2);
        lblTotaDuration->setMinimumSize(QSize(99, 0));
        lblTotaDuration->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutTotalDuration->addWidget(lblTotaDuration);

        teTotalDuration = new QTimeEdit(gbMain);
        teTotalDuration->setObjectName(QStringLiteral("teTotalDuration"));
        teTotalDuration->setEnabled(false);
        teTotalDuration->setMinimumSize(QSize(90, 0));
        teTotalDuration->setMaximumSize(QSize(90, 16777215));

        layoutTotalDuration->addWidget(teTotalDuration);

        checkBoxTotalDuration = new QCheckBox(gbMain);
        checkBoxTotalDuration->setObjectName(QStringLiteral("checkBoxTotalDuration"));

        layoutTotalDuration->addWidget(checkBoxTotalDuration);

        spacerTotalDuration = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutTotalDuration->addItem(spacerTotalDuration);


        verticalLayout_3->addLayout(layoutTotalDuration);

        gbFileName = new QGroupBox(gbMain);
        gbFileName->setObjectName(QStringLiteral("gbFileName"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        gbFileName->setFont(font);
        gbFileName->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(gbFileName);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        layoutFileNameFormat = new QHBoxLayout();
        layoutFileNameFormat->setObjectName(QStringLiteral("layoutFileNameFormat"));
        lblFileNameFormat = new QLabel(gbFileName);
        lblFileNameFormat->setObjectName(QStringLiteral("lblFileNameFormat"));
        lblFileNameFormat->setMinimumSize(QSize(90, 0));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        lblFileNameFormat->setFont(font1);
        lblFileNameFormat->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutFileNameFormat->addWidget(lblFileNameFormat);

        editFileNameFormat = new QLineEdit(gbFileName);
        editFileNameFormat->setObjectName(QStringLiteral("editFileNameFormat"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(editFileNameFormat->sizePolicy().hasHeightForWidth());
        editFileNameFormat->setSizePolicy(sizePolicy3);
        editFileNameFormat->setFont(font1);

        layoutFileNameFormat->addWidget(editFileNameFormat);


        verticalLayout_2->addLayout(layoutFileNameFormat);

        layoutDateTimeFormat = new QHBoxLayout();
        layoutDateTimeFormat->setObjectName(QStringLiteral("layoutDateTimeFormat"));
        lblDateTimeFormat = new QLabel(gbFileName);
        lblDateTimeFormat->setObjectName(QStringLiteral("lblDateTimeFormat"));
        lblDateTimeFormat->setMinimumSize(QSize(90, 0));
        lblDateTimeFormat->setFont(font1);
        lblDateTimeFormat->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutDateTimeFormat->addWidget(lblDateTimeFormat);

        editDateTimeFormat = new QLineEdit(gbFileName);
        editDateTimeFormat->setObjectName(QStringLiteral("editDateTimeFormat"));
        sizePolicy3.setHeightForWidth(editDateTimeFormat->sizePolicy().hasHeightForWidth());
        editDateTimeFormat->setSizePolicy(sizePolicy3);
        editDateTimeFormat->setFont(font1);

        layoutDateTimeFormat->addWidget(editDateTimeFormat);


        verticalLayout_2->addLayout(layoutDateTimeFormat);

        layoutUserName = new QHBoxLayout();
        layoutUserName->setObjectName(QStringLiteral("layoutUserName"));
        lblUserName = new QLabel(gbFileName);
        lblUserName->setObjectName(QStringLiteral("lblUserName"));
        lblUserName->setMinimumSize(QSize(90, 0));
        lblUserName->setFont(font1);
        lblUserName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutUserName->addWidget(lblUserName);

        editUserName = new QLineEdit(gbFileName);
        editUserName->setObjectName(QStringLiteral("editUserName"));
        sizePolicy3.setHeightForWidth(editUserName->sizePolicy().hasHeightForWidth());
        editUserName->setSizePolicy(sizePolicy3);
        editUserName->setFont(font1);

        layoutUserName->addWidget(editUserName);


        verticalLayout_2->addLayout(layoutUserName);

        layoutPassword = new QHBoxLayout();
        layoutPassword->setObjectName(QStringLiteral("layoutPassword"));
        lblPassword = new QLabel(gbFileName);
        lblPassword->setObjectName(QStringLiteral("lblPassword"));
        lblPassword->setMinimumSize(QSize(90, 0));
        lblPassword->setFont(font1);
        lblPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutPassword->addWidget(lblPassword);

        editPassword = new QLineEdit(gbFileName);
        editPassword->setObjectName(QStringLiteral("editPassword"));
        sizePolicy3.setHeightForWidth(editPassword->sizePolicy().hasHeightForWidth());
        editPassword->setSizePolicy(sizePolicy3);
        editPassword->setFont(font1);

        layoutPassword->addWidget(editPassword);


        verticalLayout_2->addLayout(layoutPassword);

        layoutDeviceTag = new QHBoxLayout();
        layoutDeviceTag->setObjectName(QStringLiteral("layoutDeviceTag"));
        lblDeviceTag = new QLabel(gbFileName);
        lblDeviceTag->setObjectName(QStringLiteral("lblDeviceTag"));
        lblDeviceTag->setMinimumSize(QSize(90, 0));
        lblDeviceTag->setFont(font1);
        lblDeviceTag->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        layoutDeviceTag->addWidget(lblDeviceTag);

        editDeviceTag = new QLineEdit(gbFileName);
        editDeviceTag->setObjectName(QStringLiteral("editDeviceTag"));
        sizePolicy3.setHeightForWidth(editDeviceTag->sizePolicy().hasHeightForWidth());
        editDeviceTag->setSizePolicy(sizePolicy3);
        editDeviceTag->setFont(font1);

        layoutDeviceTag->addWidget(editDeviceTag);


        verticalLayout_2->addLayout(layoutDeviceTag);

        vSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(vSpacer_2);


        verticalLayout_3->addWidget(gbFileName);


        verticalLayout->addWidget(gbMain);

        layoutButtons = new QHBoxLayout();
        layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
        spacerButtons = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layoutButtons->addItem(spacerButtons);

        bnOk = new QPushButton(SvRls2bit2FileSettingsDialog);
        bnOk->setObjectName(QStringLiteral("bnOk"));

        layoutButtons->addWidget(bnOk);

        bnCancel = new QPushButton(SvRls2bit2FileSettingsDialog);
        bnCancel->setObjectName(QStringLiteral("bnCancel"));

        layoutButtons->addWidget(bnCancel);


        verticalLayout->addLayout(layoutButtons);

        QWidget::setTabOrder(editDeviceName, editSaveDirectory);
        QWidget::setTabOrder(editSaveDirectory, bnSelectSaveDirectory);
        QWidget::setTabOrder(bnSelectSaveDirectory, teFileDuration);
        QWidget::setTabOrder(teFileDuration, teTotalDuration);
        QWidget::setTabOrder(teTotalDuration, checkBoxTotalDuration);
        QWidget::setTabOrder(checkBoxTotalDuration, editFileNameFormat);
        QWidget::setTabOrder(editFileNameFormat, editDateTimeFormat);
        QWidget::setTabOrder(editDateTimeFormat, editUserName);
        QWidget::setTabOrder(editUserName, editPassword);
        QWidget::setTabOrder(editPassword, editDeviceTag);
        QWidget::setTabOrder(editDeviceTag, bnOk);
        QWidget::setTabOrder(bnOk, bnCancel);

        retranslateUi(SvRls2bit2FileSettingsDialog);

        QMetaObject::connectSlotsByName(SvRls2bit2FileSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SvRls2bit2FileSettingsDialog)
    {
        SvRls2bit2FileSettingsDialog->setWindowTitle(QApplication::translate("SvRls2bit2FileSettingsDialog", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\260\321\200\321\205\320\270\320\262\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \320\240\320\233\320\241", 0));
        gbMain->setTitle(QString());
        lblDeviceName->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Device name", 0));
        lblPort->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Port", 0));
        lblArchServer->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Сервер архивации", 0));
        lblRotationSpeed->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Rotation speed", 0));
        lblSaveDirectory->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Save files to", 0));
        bnSelectSaveDirectory->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "...", 0));
        lblFileDuration->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "File duration", 0));
        teFileDuration->setDisplayFormat(QApplication::translate("SvRls2bit2FileSettingsDialog", "HH:mm:ss", 0));
        lblTotaDuration->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Total duration", 0));
        teTotalDuration->setDisplayFormat(QApplication::translate("SvRls2bit2FileSettingsDialog", "HH:mm:ss", 0));
        checkBoxTotalDuration->setText(QString());
        gbFileName->setTitle(QApplication::translate("SvRls2bit2FileSettingsDialog", "File name", 0));
        lblFileNameFormat->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "File name format", 0));
        lblDateTimeFormat->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Date/Time format", 0));
        editDateTimeFormat->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "ddMMyy_hhmmss", 0));
        lblUserName->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "User name", 0));
        lblPassword->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Password", 0));
        lblDeviceTag->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Device tag", 0));
        bnOk->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "OK", 0));
        bnCancel->setText(QApplication::translate("SvRls2bit2FileSettingsDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SvRls2bit2FileSettingsDialog: public Ui_SvRls2bit2FileSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_RLS2BIT2FILESETTINGSOJ1244_H
