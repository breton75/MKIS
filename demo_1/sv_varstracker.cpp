#include "sv_varstracker.h"
#include "./COMMON/sv_settings.h"

SvVarsTracker::SvVarsTracker(QObject *parent, int interval)
{
  this->setParent(parent);
  this->interval = interval;
  this->doTrack = true;
//  this->run();

}

SvVarsTracker::~SvVarsTracker()
{
  doTrack = false;
  while (!this->isFinished()) QApplication::processEvents();
  this->deleteLater();
}

void SvVarsTracker::run()
{
  SvSettings* vv_sett;
  SvSettings* var_sett;
  QString s;
  
  while (doTrack)
  {
    s = QApplication::applicationDirPath() + "/ini/vars_values.ini";
    vv_sett = new SvSettings(s);
    
    QStringList lst = vv_sett->appSettings->childGroups();
    for(int i = 0; i < lst.count(); i++)
    {
      s = vv_sett->readValue(lst.at(i), "var_value", "").toString();

      QString var_name = s.section('%', 1, 1);
      qreal current_value = s.section('%', 2, 2).toFloat();
      
      s = QApplication::applicationDirPath() + "/ini/vars.ini";
      var_sett = new SvSettings(s);
      
      QStringList lst2 = var_sett->appSettings->childGroups();
      for(int i = 0; i < lst2.count(); i++)
      {
        s = var_sett->readValue(lst.at(i), "var", "").toString();
        if(var_name == s.section('%', 1, 1))
        {
//          QString device_name = s.section('%', 2, 2);
//          qDebug() << "fdfd";
          qreal min = s.section('%', 3, 3).toFloat();
          qreal max = s.section('%', 4, 4).toFloat();
//          QString alarm_type = s.section('%', 5, 5);
          if((current_value < min) | (current_value > max))
            emit alarm(var_name, current_value);
          
        }
      }

    }
    
    emit progressed();
    
    msleep(interval);
  } 
}
