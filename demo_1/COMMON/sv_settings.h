#ifndef SVSETTINGS_H
#define SVSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QSize>
#include <QPoint>

class SvSettings : public QObject
{
    Q_OBJECT
  public:
    explicit SvSettings(QString fileName = "",
                        QObject *parent = 0,
                        QSettings::Format format = QSettings::IniFormat,
                        QString organizationName = "",
                        QString organizationDomain = "",
                        QString setAppName = "");
    
    ~SvSettings();
    
    QSettings *appSettings = 0;
    
    virtual void writeValue(QString GroupName, QString ValueName, int Value);
    virtual void writeValue(QString GroupName, QString ValueName, QString Value);
    virtual void writeValue(QString GroupName, QString ValueName, QSize Value);
    virtual void writeValue(QString GroupName, QString ValueName, QPoint Value);
    
//    int readValue(QString GroupName, QString ValueName);
    QVariant readValue(QString GroupName, QString ValueName, QVariant DefaultValue);
    
    QTextCodec* codec;
    
  signals:
    
  public slots:
   
    
};

#endif // SVSETTINGS_H
