#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "socketreader.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class QOpenGLTexture;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget();
    ~GLWidget();
    void startTranslation(const QString &address, quint16 port);
    void stopTranslation();

signals:
    void stopListen();

private slots:
    void setLevels(Azimuth azmt);
    void drawImage();

protected:
    void paintGL();
    void initializeGL();
private:
    QImage *imageMap;
    QOpenGLTexture *texture;
    QTimer timer;
};


#endif // GLWIDGET_H
