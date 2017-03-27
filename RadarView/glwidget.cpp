#include "glwidget.h"
#include <QOpenGLTexture>
#include <cmath>
#if defined(Q_OS_WIN)
#include <qmath.h>
#endif

const quint32 azimuths(4096);		// количество азимутов
const quint16 countPoint(4096);		// количество точек в азимуте
const QRgb colors[] = {
    qRgb(0, 0, 0),
    qRgb(39, 39, 39),
    qRgb(75, 75, 75),
    qRgb(111, 111, 111),
    qRgb(145, 145, 145),
    qRgb(183, 183, 183),
    qRgb(219, 219, 219),
    qRgb(255, 255, 255)
};

GLdouble TexCoord[azimuths][4][2];		// координаты текстуры
GLdouble VertexCoord[azimuths][4][2];	// координаты вершин
void calculateCoord();

GLWidget::GLWidget() :
    texture(0)
{
    calculateCoord();
    imageMap = new QImage(azimuths, countPoint, QImage::Format_RGB888);
    connect(&timer, SIGNAL(timeout()), SLOT(drawImage()));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(620, 620);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    delete imageMap;
    delete texture;
    doneCurrent();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    texture = new QOpenGLTexture(*imageMap);
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint length = height() <= width() ? height() : width();
    glViewport(width()  / 2 - length / 2,
               height() / 2 - length / 2,
               length, length);


    texture->bind();

    for (quint32 i = 0; i < azimuths; ++i)
    {
        glBegin(GL_POLYGON);

        // левый нижний угол сектора
        glTexCoord2d(TexCoord[i][0][0], TexCoord[i][0][1]);
        glVertex2d(VertexCoord[i][0][0], VertexCoord[i][0][1]);

        // левый верхний
        glTexCoord2d(TexCoord[i][1][0], TexCoord[i][1][1]);
        glVertex2d(VertexCoord[i][1][0], VertexCoord[i][1][1]);

        // правый верхний
        glTexCoord2d(TexCoord[i][2][0], TexCoord[i][2][1]);
        glVertex2d(VertexCoord[i][2][0], VertexCoord[i][2][1]);

        // правый нижний
        glTexCoord2d(TexCoord[i][3][0], TexCoord[i][3][1]);
        glVertex2d(VertexCoord[i][3][0], VertexCoord[i][3][1]);

        glEnd();
    }
}

void GLWidget::drawImage()
{
    makeCurrent();
    texture->destroy();
    texture->setData(*imageMap);
    doneCurrent();
    paintGL();
    update();
}

void GLWidget::startTranslation(const QString &address, quint16 port)
{
    SocketReader *sock = new SocketReader(address, port,
                                          azimuths, countPoint);

    connect(sock, SIGNAL(finished()), sock, SLOT(deleteLater()));
    connect(sock, SIGNAL(azimuthUpdated(Azimuth)), SLOT(setLevels(Azimuth)), Qt::QueuedConnection);
    connect(this, SIGNAL(stopListen()), sock, SLOT(stopWork()));

    sock->start();
    timer.start(60);
}

void GLWidget::stopTranslation()
{
    emit stopListen();
    if (timer.isActive())
        timer.stop();
}

void GLWidget::setLevels(Azimuth azmt)
{
    for (int i = 0; i < countPoint; ++i) {
        imageMap->setPixel(azmt.num, i, colors[(int)azmt.levels.at(i)]);
    }
}

void calculateCoord()
{
    for (quint32 i = 0; i < azimuths; ++i)
    {
        // левый нижний угол
        TexCoord[i][0][0]    = 1.0 / azimuths * i;
        TexCoord[i][0][1]    = 0.0;
        VertexCoord[i][0][0] = 0.0;
        VertexCoord[i][0][1] = 0.0;

        // левый верхний
        TexCoord[i][1][0]    = 1.0 / azimuths * i;
        TexCoord[i][1][1]    = 1.0;
        VertexCoord[i][1][0] = sin(i * 2 * M_PI / azimuths);
        VertexCoord[i][1][1] = cos(i * 2 * M_PI / azimuths);

        // правый верхний
        TexCoord[i][2][0]    = 1.0 / azimuths * (i + 1);
        TexCoord[i][2][1]    = 1.0;
        VertexCoord[i][2][0] = sin((i + 1) * 2 * M_PI / azimuths);
        VertexCoord[i][2][1] = cos((i + 1) * 2 * M_PI / azimuths);

        // правый нижний
        TexCoord[i][3][0]    = 1.0 / azimuths * (i + 1);
        TexCoord[i][3][1]    = 0.0;
        VertexCoord[i][3][0] = 0.0;
        VertexCoord[i][3][1] = 0.0;
    }
}
