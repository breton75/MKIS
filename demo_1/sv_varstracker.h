#ifndef SVVARSTRACKER_H
#define SVVARSTRACKER_H

#include <QThread>
#include <QTimer>
#include <QApplication>
#include <QDebug>

class SvVarsTracker : public QThread
{
  Q_OBJECT
  
  public:
    explicit SvVarsTracker(QObject* parent,
                           int interval);
    ~SvVarsTracker();
    
    void stop() { doTrack = false; }
    
  private:
    int interval;
    bool doTrack;
    void run();
    
  signals:
    void progressed();
    void alarm(QString var_name, qreal value);
};

#endif // SVVARSTRACKER_H
