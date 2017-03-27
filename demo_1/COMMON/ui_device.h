/********************************************************************************
** Form generated from reading UI file 'sv_deviceyO7120.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SV_DEVICE_H
#define SV_DEVICE_H

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

class Ui_SvDevice
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *gbGeneral;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *layoutID;
    QLabel *lblID;
    QLineEdit *editID;
    QHBoxLayout *layoutDevName;
    QLabel *lblDevName;
    QLineEdit *editDevName;
    QHBoxLayout *layoutIPPort;
    QLabel *lblIP;
    QLineEdit *editIP;
    QLabel *lblPort;
    QLineEdit *editPort;
    QHBoxLayout *layoutIPPort_2;
    QLabel *lblUserName;
    QLineEdit *editUserName;
    QLabel *lblPassword;
    QLineEdit *editPassword;
    QGroupBox *gbModel;
    QVBoxLayout *layoutModel;
    QHBoxLayout *layoutModelName;
    QLabel *lblModelName;
    QLineEdit *editModelName;
    QHBoxLayout *layoutClass;
    QLabel *lblClass;
    QLineEdit *editClass;
    QHBoxLayout *layoutBrand;
    QLabel *lblBrand;
    QLineEdit *editBrand;
    QHBoxLayout *layoutDriver;
    QLabel *lblDriver;
    QLineEdit *editDriver;
    QHBoxLayout *layoutModelButtons;
    QSpacerItem *hSpacerModelButtons;
    QPushButton *bnNewModel;
    QPushButton *bnSelectModel;
    QGroupBox *gbLocation;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *layoutZone;
    QLabel *lblZoneName;
    QLineEdit *editZoneName;
    QPushButton *bnSelectZone;
    QPushButton *bnNewZone;
    QHBoxLayout *layoutPosition;
    QLabel *lblPosition;
    QLineEdit *editPositionX;
    QLabel *lblPositionY;
    QLineEdit *editPositionY;
    QPushButton *bnSelectPosition;
    QSpacerItem *spacerLoaction;
    QVBoxLayout *layoutDescription;
    QLabel *lblDescription;
    QTextEdit *textDescription;
    QHBoxLayout *layoutButtons;
    QSpacerItem *hSpacerButtons;
    QPushButton *bnSave;
    QPushButton *bnCancel;

    enum ShowMode { smNew = 0, smEdit = 1 };
    
    void setupUi(QDialog *SvDevice,
                 QString deviceName,
                 QString ip,
                 int port,
                 QString modelName,
                 QString clssName,
                 QString brandName,
                 QString libPath,
                 QString description,
                 QString zoneName,
                 float locationX,
                 float locationY,
//                 int locationZ,
                 int id,
                 int showMode)
    {
      if (SvDevice->objectName().isEmpty())
          SvDevice->setObjectName(QStringLiteral("SvDevice"));
      SvDevice->resize(403, 577);
      verticalLayout_2 = new QVBoxLayout(SvDevice);
      verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
      groupBox = new QGroupBox(SvDevice);
      groupBox->setObjectName(QStringLiteral("groupBox"));
      QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
      groupBox->setSizePolicy(sizePolicy);
      verticalLayout_4 = new QVBoxLayout(groupBox);
      verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
      gbGeneral = new QGroupBox(groupBox);
      gbGeneral->setObjectName(QStringLiteral("gbGeneral"));
      QFont font;
      font.setBold(true);
      font.setWeight(75);
      gbGeneral->setFont(font);
      verticalLayout = new QVBoxLayout(gbGeneral);
      verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
      layoutID = new QHBoxLayout();
      layoutID->setObjectName(QStringLiteral("layoutID"));
      lblID = new QLabel(gbGeneral);
      lblID->setObjectName(QStringLiteral("lblID"));
      QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
      sizePolicy1.setHorizontalStretch(0);
      sizePolicy1.setVerticalStretch(0);
      sizePolicy1.setHeightForWidth(lblID->sizePolicy().hasHeightForWidth());
      lblID->setSizePolicy(sizePolicy1);
      lblID->setMinimumSize(QSize(75, 0));
      lblID->setMaximumSize(QSize(55, 16777215));
      QFont font1;
      font1.setBold(false);
      font1.setWeight(50);
      lblID->setFont(font1);
      lblID->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutID->addWidget(lblID);

      editID = new QLineEdit(gbGeneral);
      editID->setObjectName(QStringLiteral("editID"));
      QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
      sizePolicy2.setHorizontalStretch(0);
      sizePolicy2.setVerticalStretch(0);
      sizePolicy2.setHeightForWidth(editID->sizePolicy().hasHeightForWidth());
      editID->setSizePolicy(sizePolicy2);
      editID->setFont(font1);
      editID->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editID->setReadOnly(true);

      layoutID->addWidget(editID);


      verticalLayout->addLayout(layoutID);

      layoutDevName = new QHBoxLayout();
      layoutDevName->setObjectName(QStringLiteral("layoutDevName"));
      lblDevName = new QLabel(gbGeneral);
      lblDevName->setObjectName(QStringLiteral("lblDevName"));
      sizePolicy1.setHeightForWidth(lblDevName->sizePolicy().hasHeightForWidth());
      lblDevName->setSizePolicy(sizePolicy1);
      lblDevName->setMinimumSize(QSize(75, 0));
      lblDevName->setMaximumSize(QSize(55, 16777215));
      lblDevName->setFont(font1);
      lblDevName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutDevName->addWidget(lblDevName);

      editDevName = new QLineEdit(gbGeneral);
      editDevName->setObjectName(QStringLiteral("editDevName"));
      editDevName->setFont(font1);

      layoutDevName->addWidget(editDevName);


      verticalLayout->addLayout(layoutDevName);

      layoutIPPort = new QHBoxLayout();
      layoutIPPort->setObjectName(QStringLiteral("layoutIPPort"));
      lblIP = new QLabel(gbGeneral);
      lblIP->setObjectName(QStringLiteral("lblIP"));
      sizePolicy1.setHeightForWidth(lblIP->sizePolicy().hasHeightForWidth());
      lblIP->setSizePolicy(sizePolicy1);
      lblIP->setMinimumSize(QSize(75, 0));
      lblIP->setMaximumSize(QSize(55, 16777215));
      lblIP->setFont(font1);
      lblIP->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutIPPort->addWidget(lblIP);

      editIP = new QLineEdit(gbGeneral);
      editIP->setObjectName(QStringLiteral("editIP"));
      editIP->setMinimumSize(QSize(100, 0));
      editIP->setMaximumSize(QSize(16777215, 16777215));
      editIP->setFont(font1);

      layoutIPPort->addWidget(editIP);

      lblPort = new QLabel(gbGeneral);
      lblPort->setObjectName(QStringLiteral("lblPort"));
      sizePolicy1.setHeightForWidth(lblPort->sizePolicy().hasHeightForWidth());
      lblPort->setSizePolicy(sizePolicy1);
      lblPort->setMinimumSize(QSize(50, 0));
      lblPort->setFont(font1);
      lblPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutIPPort->addWidget(lblPort);

      editPort = new QLineEdit(gbGeneral);
      editPort->setObjectName(QStringLiteral("editPort"));
      QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
      sizePolicy3.setHorizontalStretch(0);
      sizePolicy3.setVerticalStretch(0);
      sizePolicy3.setHeightForWidth(editPort->sizePolicy().hasHeightForWidth());
      editPort->setSizePolicy(sizePolicy3);
      editPort->setMinimumSize(QSize(100, 0));
      editPort->setMaximumSize(QSize(16777215, 16777215));
      editPort->setFont(font1);

      layoutIPPort->addWidget(editPort);


      verticalLayout->addLayout(layoutIPPort);

      layoutIPPort_2 = new QHBoxLayout();
      layoutIPPort_2->setObjectName(QStringLiteral("layoutIPPort_2"));
      lblUserName = new QLabel(gbGeneral);
      lblUserName->setObjectName(QStringLiteral("lblUserName"));
      sizePolicy1.setHeightForWidth(lblUserName->sizePolicy().hasHeightForWidth());
      lblUserName->setSizePolicy(sizePolicy1);
      lblUserName->setMinimumSize(QSize(75, 0));
      lblUserName->setMaximumSize(QSize(55, 16777215));
      lblUserName->setFont(font1);
      lblUserName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutIPPort_2->addWidget(lblUserName);

      editUserName = new QLineEdit(gbGeneral);
      editUserName->setObjectName(QStringLiteral("editUserName"));
      editUserName->setMinimumSize(QSize(100, 0));
      editUserName->setMaximumSize(QSize(16777215, 16777215));
      editUserName->setFont(font1);

      layoutIPPort_2->addWidget(editUserName);

      lblPassword = new QLabel(gbGeneral);
      lblPassword->setObjectName(QStringLiteral("lblPassword"));
      sizePolicy1.setHeightForWidth(lblPassword->sizePolicy().hasHeightForWidth());
      lblPassword->setSizePolicy(sizePolicy1);
      lblPassword->setMinimumSize(QSize(50, 0));
      lblPassword->setMaximumSize(QSize(50, 16777215));
      lblPassword->setFont(font1);
      lblPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutIPPort_2->addWidget(lblPassword);

      editPassword = new QLineEdit(gbGeneral);
      editPassword->setObjectName(QStringLiteral("editPassword"));
      sizePolicy3.setHeightForWidth(editPassword->sizePolicy().hasHeightForWidth());
      editPassword->setSizePolicy(sizePolicy3);
      editPassword->setMinimumSize(QSize(100, 0));
      editPassword->setMaximumSize(QSize(16777215, 16777215));
      editPassword->setFont(font1);

      layoutIPPort_2->addWidget(editPassword);


      verticalLayout->addLayout(layoutIPPort_2);


      verticalLayout_4->addWidget(gbGeneral);

      gbModel = new QGroupBox(groupBox);
      gbModel->setObjectName(QStringLiteral("gbModel"));
      QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
      sizePolicy4.setHorizontalStretch(0);
      sizePolicy4.setVerticalStretch(0);
      sizePolicy4.setHeightForWidth(gbModel->sizePolicy().hasHeightForWidth());
      gbModel->setSizePolicy(sizePolicy4);
      gbModel->setFont(font);
      gbModel->setFlat(false);
      layoutModel = new QVBoxLayout(gbModel);
      layoutModel->setObjectName(QStringLiteral("layoutModel"));
      layoutModelName = new QHBoxLayout();
      layoutModelName->setObjectName(QStringLiteral("layoutModelName"));
      lblModelName = new QLabel(gbModel);
      lblModelName->setObjectName(QStringLiteral("lblModelName"));
      sizePolicy1.setHeightForWidth(lblModelName->sizePolicy().hasHeightForWidth());
      lblModelName->setSizePolicy(sizePolicy1);
      lblModelName->setMinimumSize(QSize(65, 0));
      lblModelName->setMaximumSize(QSize(65, 16777215));
      lblModelName->setFont(font1);
      lblModelName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutModelName->addWidget(lblModelName);

      editModelName = new QLineEdit(gbModel);
      editModelName->setObjectName(QStringLiteral("editModelName"));
      editModelName->setFont(font1);
      editModelName->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editModelName->setReadOnly(true);

      layoutModelName->addWidget(editModelName);


      layoutModel->addLayout(layoutModelName);

      layoutClass = new QHBoxLayout();
      layoutClass->setObjectName(QStringLiteral("layoutClass"));
      lblClass = new QLabel(gbModel);
      lblClass->setObjectName(QStringLiteral("lblClass"));
      sizePolicy1.setHeightForWidth(lblClass->sizePolicy().hasHeightForWidth());
      lblClass->setSizePolicy(sizePolicy1);
      lblClass->setMinimumSize(QSize(65, 0));
      lblClass->setMaximumSize(QSize(65, 16777215));
      lblClass->setFont(font1);
      lblClass->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutClass->addWidget(lblClass);

      editClass = new QLineEdit(gbModel);
      editClass->setObjectName(QStringLiteral("editClass"));
      editClass->setFont(font1);
      editClass->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editClass->setReadOnly(true);

      layoutClass->addWidget(editClass);


      layoutModel->addLayout(layoutClass);

      layoutBrand = new QHBoxLayout();
      layoutBrand->setObjectName(QStringLiteral("layoutBrand"));
      lblBrand = new QLabel(gbModel);
      lblBrand->setObjectName(QStringLiteral("lblBrand"));
      sizePolicy1.setHeightForWidth(lblBrand->sizePolicy().hasHeightForWidth());
      lblBrand->setSizePolicy(sizePolicy1);
      lblBrand->setMinimumSize(QSize(65, 0));
      lblBrand->setMaximumSize(QSize(65, 16777215));
      lblBrand->setFont(font1);
      lblBrand->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutBrand->addWidget(lblBrand);

      editBrand = new QLineEdit(gbModel);
      editBrand->setObjectName(QStringLiteral("editBrand"));
      editBrand->setFont(font1);
      editBrand->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editBrand->setReadOnly(true);

      layoutBrand->addWidget(editBrand);


      layoutModel->addLayout(layoutBrand);

      layoutDriver = new QHBoxLayout();
      layoutDriver->setObjectName(QStringLiteral("layoutDriver"));
      lblDriver = new QLabel(gbModel);
      lblDriver->setObjectName(QStringLiteral("lblDriver"));
      sizePolicy1.setHeightForWidth(lblDriver->sizePolicy().hasHeightForWidth());
      lblDriver->setSizePolicy(sizePolicy1);
      lblDriver->setMinimumSize(QSize(65, 0));
      lblDriver->setMaximumSize(QSize(65, 16777215));
      lblDriver->setFont(font1);
      lblDriver->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutDriver->addWidget(lblDriver);

      editDriver = new QLineEdit(gbModel);
      editDriver->setObjectName(QStringLiteral("editDriver"));
      editDriver->setFont(font1);
      editDriver->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editDriver->setReadOnly(true);

      layoutDriver->addWidget(editDriver);


      layoutModel->addLayout(layoutDriver);

      layoutModelButtons = new QHBoxLayout();
      layoutModelButtons->setObjectName(QStringLiteral("layoutModelButtons"));
      hSpacerModelButtons = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      layoutModelButtons->addItem(hSpacerModelButtons);

      bnNewModel = new QPushButton(gbModel);
      bnNewModel->setObjectName(QStringLiteral("bnNewModel"));
      sizePolicy3.setHeightForWidth(bnNewModel->sizePolicy().hasHeightForWidth());
      bnNewModel->setSizePolicy(sizePolicy3);
      bnNewModel->setMinimumSize(QSize(23, 23));
      bnNewModel->setMaximumSize(QSize(23, 23));
      bnNewModel->setFont(font1);

      layoutModelButtons->addWidget(bnNewModel);

      bnSelectModel = new QPushButton(gbModel);
      bnSelectModel->setObjectName(QStringLiteral("bnSelectModel"));
      bnSelectModel->setFont(font1);

      layoutModelButtons->addWidget(bnSelectModel);


      layoutModel->addLayout(layoutModelButtons);


      verticalLayout_4->addWidget(gbModel);

      gbLocation = new QGroupBox(groupBox);
      gbLocation->setObjectName(QStringLiteral("gbLocation"));
      sizePolicy.setHeightForWidth(gbLocation->sizePolicy().hasHeightForWidth());
      gbLocation->setSizePolicy(sizePolicy);
      gbLocation->setFont(font);
      verticalLayout_3 = new QVBoxLayout(gbLocation);
      verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
      layoutZone = new QHBoxLayout();
      layoutZone->setObjectName(QStringLiteral("layoutZone"));
      lblZoneName = new QLabel(gbLocation);
      lblZoneName->setObjectName(QStringLiteral("lblZoneName"));
      lblZoneName->setMinimumSize(QSize(75, 0));
      lblZoneName->setFont(font1);
      lblZoneName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutZone->addWidget(lblZoneName);

      editZoneName = new QLineEdit(gbLocation);
      editZoneName->setObjectName(QStringLiteral("editZoneName"));
      editZoneName->setFont(font1);
      editZoneName->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editZoneName->setReadOnly(true);

      layoutZone->addWidget(editZoneName);

      bnSelectZone = new QPushButton(gbLocation);
      bnSelectZone->setObjectName(QStringLiteral("bnSelectZone"));
      bnSelectZone->setMaximumSize(QSize(26, 16777215));
      bnSelectZone->setFont(font1);

      layoutZone->addWidget(bnSelectZone);

      bnNewZone = new QPushButton(gbLocation);
      bnNewZone->setObjectName(QStringLiteral("bnNewZone"));
      bnNewZone->setMaximumSize(QSize(26, 16777215));
      bnNewZone->setFont(font1);

      layoutZone->addWidget(bnNewZone);


      verticalLayout_3->addLayout(layoutZone);

      layoutPosition = new QHBoxLayout();
      layoutPosition->setObjectName(QStringLiteral("layoutPosition"));
      lblPosition = new QLabel(gbLocation);
      lblPosition->setObjectName(QStringLiteral("lblPosition"));
      lblPosition->setMinimumSize(QSize(75, 0));
      lblPosition->setFont(font1);
      lblPosition->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutPosition->addWidget(lblPosition);

      editPositionX = new QLineEdit(gbLocation);
      editPositionX->setObjectName(QStringLiteral("editPositionX"));
      sizePolicy4.setHeightForWidth(editPositionX->sizePolicy().hasHeightForWidth());
      editPositionX->setSizePolicy(sizePolicy4);
      editPositionX->setMaximumSize(QSize(16777215, 16777215));
      editPositionX->setFont(font1);
      editPositionX->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editPositionX->setReadOnly(true);

      layoutPosition->addWidget(editPositionX);

      lblPositionY = new QLabel(gbLocation);
      lblPositionY->setObjectName(QStringLiteral("lblPositionY"));
      lblPositionY->setMinimumSize(QSize(25, 0));
      lblPositionY->setFont(font1);
      lblPositionY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

      layoutPosition->addWidget(lblPositionY);

      editPositionY = new QLineEdit(gbLocation);
      editPositionY->setObjectName(QStringLiteral("editPositionY"));
      sizePolicy4.setHeightForWidth(editPositionY->sizePolicy().hasHeightForWidth());
      editPositionY->setSizePolicy(sizePolicy4);
      editPositionY->setMaximumSize(QSize(16777215, 16777215));
      editPositionY->setFont(font1);
      editPositionY->setStyleSheet(QStringLiteral("background-color: rgb(209, 209, 209);"));
      editPositionY->setReadOnly(true);

      layoutPosition->addWidget(editPositionY);

      bnSelectPosition = new QPushButton(gbLocation);
      bnSelectPosition->setObjectName(QStringLiteral("bnSelectPosition"));
      bnSelectPosition->setMaximumSize(QSize(26, 16777215));
      bnSelectPosition->setFont(font1);

      layoutPosition->addWidget(bnSelectPosition);

      spacerLoaction = new QSpacerItem(26, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

      layoutPosition->addItem(spacerLoaction);


      verticalLayout_3->addLayout(layoutPosition);


      verticalLayout_4->addWidget(gbLocation);

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


      verticalLayout_4->addLayout(layoutDescription);


      verticalLayout_2->addWidget(groupBox);

      layoutButtons = new QHBoxLayout();
      layoutButtons->setObjectName(QStringLiteral("layoutButtons"));
      hSpacerButtons = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

      layoutButtons->addItem(hSpacerButtons);

      bnSave = new QPushButton(SvDevice);
      bnSave->setObjectName(QStringLiteral("bnSave"));
      sizePolicy3.setHeightForWidth(bnSave->sizePolicy().hasHeightForWidth());
      bnSave->setSizePolicy(sizePolicy3);
      bnSave->setMaximumSize(QSize(80, 16777215));
      bnSave->setDefault(true);

      layoutButtons->addWidget(bnSave);

      bnCancel = new QPushButton(SvDevice);
      bnCancel->setObjectName(QStringLiteral("bnCancel"));
      sizePolicy3.setHeightForWidth(bnCancel->sizePolicy().hasHeightForWidth());
      bnCancel->setSizePolicy(sizePolicy3);
      bnCancel->setMaximumSize(QSize(80, 16777215));

      layoutButtons->addWidget(bnCancel);


      verticalLayout_2->addLayout(layoutButtons);


      QWidget::setTabOrder(editDevName, editIP);
      QWidget::setTabOrder(editIP, editPort);
      QWidget::setTabOrder(editPort, editUserName);
      QWidget::setTabOrder(editUserName, editPassword);
      QWidget::setTabOrder(editPassword, editModelName);
      QWidget::setTabOrder(editModelName, editClass);
      QWidget::setTabOrder(editClass, editBrand);
      QWidget::setTabOrder(editBrand, editDriver);
      QWidget::setTabOrder(editDriver, bnNewModel);
      QWidget::setTabOrder(bnNewModel, bnSelectModel);
      QWidget::setTabOrder(bnSelectModel, editZoneName);
      QWidget::setTabOrder(editZoneName, bnSelectZone);
      QWidget::setTabOrder(bnSelectZone, bnNewZone);
      QWidget::setTabOrder(bnNewZone, bnSave);
      QWidget::setTabOrder(bnSave, bnCancel);
      QWidget::setTabOrder(bnCancel, textDescription);
      QWidget::setTabOrder(textDescription, editID);
      

      if(id != -1) editID->setText(QString("%1").arg(id));
      editDevName->setText(deviceName);
      editIP->setText(ip);
      editPort->setText(QString("%1").arg(port));
      editModelName->setText(modelName);
      editClass->setText(clssName);
      editBrand->setText(brandName);
      editDriver->setText(libPath);
      editZoneName->setText(zoneName);
      editPositionX->setText(QString("%1").arg(locationX));
      editPositionY->setText(QString("%1").arg(locationY));
//      sbZ->setValue(locationZ);
      textDescription->setText(description);

      retranslateUi(SvDevice, showMode, deviceName);

      QMetaObject::connectSlotsByName(SvDevice);
      
    } // setupUi

    void retranslateUi(QDialog *SvDevice, int showMode, QString devName)
    {
      QString title;
      title = QApplication::translate("SvDevice", "Device - ", 0);
      if(showMode = smNew)
        title = title + QApplication::translate("SvDevice", "New", 0);
      else title = title + devName;
      
      SvDevice->setWindowTitle(title);
      groupBox->setTitle(QString());
      lblID->setText(QApplication::translate("SvDevice", "ID", 0));
      lblDevName->setText(QApplication::translate("SvDevice", "Device name", 0));
      lblIP->setText(QApplication::translate("SvDevice", "IP", 0));
      lblPort->setText(QApplication::translate("SvDevice", "Port", 0));
      gbModel->setTitle(QApplication::translate("SvDevice", "Model", 0));
      lblModelName->setText(QApplication::translate("SvDevice", "Model name", 0));
      lblClass->setText(QApplication::translate("SvDevice", "Device class", 0));
      lblBrand->setText(QApplication::translate("SvDevice", "Brand", 0));
      lblDriver->setText(QApplication::translate("SvDevice", "Driver lib", 0));
      bnNewModel->setText(QApplication::translate("SvDevice", "+", 0));
      bnSelectModel->setText(QApplication::translate("SvDevice", "Select", 0));
      gbLocation->setTitle(QApplication::translate("SvDevice", "Security Zone", 0));
      lblZoneName->setText(QApplication::translate("SvDevice", "Zone name", 0));
      bnSelectZone->setText(QApplication::translate("SvDevice", "...", 0));
      bnNewZone->setText(QApplication::translate("SvDevice", "+", 0));
      lblPosition->setText(QApplication::translate("SvDevice", "Position:  X", 0));
      lblPositionY->setText(QApplication::translate("SvDevice", "Y", 0));
      bnSelectPosition->setText(QApplication::translate("SvDevice", "...", 0));
      lblDescription->setText(QApplication::translate("SvDevice", "Description", 0));
      bnSave->setText(QApplication::translate("SvDevice", "Save", 0));
      bnCancel->setText(QApplication::translate("SvDevice", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SvDeviceDialog: public Ui_SvDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SV_DEVICEYO7120_H
