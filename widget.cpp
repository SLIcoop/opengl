#include "widget.h"
#include <math.h>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    const unsigned int SCR_W = 800;
    const unsigned int SCR_H = 600;
    setWindowTitle("QT");
    setGeometry(400, 200, SCR_W, SCR_H);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));

    QAction *Cube = new QAction("cube", this);
    menuWindow->addAction(Cube);
    connect(Cube, SIGNAL(triggered()), this,SLOT(pickCube()));

    QAction *Pyramid = new QAction("Pyramid", this);
    menuWindow->addAction(Pyramid);
    connect(Pyramid, SIGNAL(triggered()), this,SLOT(pickPyramid()));

    QAction *Prisma = new QAction("Prisma", this);
    menuWindow->addAction(Prisma);
    connect(Prisma, SIGNAL(triggered()), this,SLOT(pickPrisma()));

    QAction *Parall = new QAction("Parall", this);
    menuWindow->addAction(Parall);
    connect(Parall, SIGNAL(triggered()), this,SLOT(pickParall()));

    QAction *quit = new QAction("quit", this);
    menuWindow->addAction(quit);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
}

Widget::~Widget()
{
}

void Widget::pickCube()
{
    figure = 0;
}

void Widget::pickPyramid()
{
    figure = 1;
}

void Widget::pickPrisma()
{
    figure = 2;
}

void Widget::pickParall()
{
    figure = 3;
}


void Widget::mousePressEvent(QMouseEvent* event)
{
     lastPos = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* event)
{
    GLfloat dx = (GLfloat)(event->x() - lastPos.x()) / width();
    GLfloat dy = (GLfloat)(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton) {
      rotationX += 180 * dy;
      rotationY += 180 * dx;
      update();
    } else if (event->buttons() & Qt::RightButton) {
      rotationX += 180 * dy;
      rotationZ += 180 * dx;
      update();
    }
    lastPos = event->pos();
}

void Widget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_FLAT);

}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)w / h;
    //glFrustum(-3, 3, -3, 3, 1, 5);
    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
}

void Widget::paintGL()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -10.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    switch (figure) {
        case 0: {
        drawCube(0.5);
                update();break;
        }
        case 1: {
        drawPyramid();
                update();break;
        }
        case 2: {
        drawPrisma();
                update();;break;
        }
        case 3: {
        drawParall();
                update();break;
        }
    }
}

void Widget::drawPyramid()
{
    float ver_pyr[] =
    {
        -0.5, -0.5, 0.5,    0.5, -0.5, 0.5,     0, 0.5, 0,
        -0.5, -0.5, -0.5,    0.5, -0.5, -0.5,     0, 0.5, 0,
        -0.5, -0.5, -0.5,    -0.5, -0.5, 0.5,     0, 0.5, 0,
        0.5, -0.5, 0.5,    0.5, -0.5, -0.5,     0, 0.5, 0,
        -0.5, -0.5, 0.5,    -0.5, -0.5, -0.5,     0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,    0.5, -0.5, 0.5,     0.5, -0.5, -0.5,
    };

    float color_arr[] =
    {
        0, 0, 1,    0, 0, 1,    0, 0, 1,
        0, 0, 1,    0, 0, 1,    0, 0, 1,
        0, 1, 0,    0, 1, 0,    0, 1, 0,
        1, 1, 0,    1, 1, 0,    1, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,
        0, 1, 1,    0, 1, 1,    0, 1, 1
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_pyr);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    //(3 * 6)
    glDrawArrays(GL_TRIANGLES, 0, 18);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Widget::drawPrisma()
{
    float ver_prism[] =
    {  
         0.25, -0.5, 0.5,    -0.25, -0.5, 0.5,   -0.25, 0.5, 0.5,    0.25, 0.5, 0.5,
         0.25, -0.5, -0.5,  -0.25, -0.5, -0.5,   -0.25, 0.5, -0.5,   0.25, 0.5, -0.5,
         0.25, -0.5, 0.5,    0.5, -0.5, 0,       0.5,  0.5, 0,       0.25, 0.5, 0.5,
         0.5,  0.5, 0,       0.5, -0.5, 0,       0.25, -0.5, -0.5,   0.25, 0.5, -0.5,
         -0.25, -0.5, 0.5,    -0.5, -0.5, 0,      -0.5,  0.5, 0,       -0.25, 0.5, 0.5,
         -0.5,  0.5, 0,       -0.5, -0.5, 0,       -0.25, -0.5, -0.5,   -0.25, 0.5, -0.5,
         0.25, -0.5, 0.5,      0.5, -0.5, 0,       -0.5, -0.5, 0,      -0.25, -0.5, 0.5,
         0.25, -0.5, -0.5,      0.5, -0.5, 0,       -0.5, -0.5, 0,      -0.25, -0.5, -0.5,
         0.25, 0.5, 0.5,      0.5, 0.5, 0,       -0.5, 0.5, 0,      -0.25, 0.5, 0.5,
         0.25, 0.5, -0.5,      0.5, 0.5, 0,       -0.5, 0.5, 0,      -0.25, 0.5, -0.5,
    };

    float color_arr[] =
    {
         0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
         1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
         0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
         1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
         1, 0.5, 0,5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5,
         1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
         1, 0.5, 1,    1, 0.5, 1,    1, 0.5, 1,    1, 0.5, 1,
         1, 0.5, 1,    1, 0.5, 1,    1, 0.5, 1,    1, 0.5, 1,
         0.5, 1, 1,    0.5, 1, 1,    0.5, 1, 1,    0.5, 1, 1,
         0.5, 1, 1,    0.5, 1, 1,    0.5, 1, 1,    0.5, 1, 1,
    };

    glVertexPointer(3, GL_FLOAT, 0, &ver_prism);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_QUADS, 0, 40);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Widget::drawParall()
{
    float ver_parall[] =
    {
        1, -0.5, 0.25,   -1, -0.5, 0.25,     -1, 0.5, 0.25,    1, 0.5, 0.25,
        1, -0.5, 0.25,   1, -0.5, -0.25,      1, 0.5, -0.25,    1, 0.5, 0.25,
        -1, -0.5, 0.25,  -1, -0.5, -0.25,     -1, 0.5, -0.25,   -1, 0.5, 0.25,
        -1, -0.5, 0.25,  1, -0.5, 0.25,       1, -0.5, -0.25,   -1, -0.5, -0.25,
        -1, 0.5, 0.25,   1, 0.5, 0.25,        1, 0.5, -0.25,    -1, 0.5, -0.25,
        1, -0.5, -0.25,   -1, -0.5, -0.25,     -1, 0.5, -0.25,    1, 0.5, -0.25,
    };

    float color_arr[] =
    {
        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
        1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
        1, 0.5, 0,5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_parall);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    //(3 * 8)
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Widget::drawCube(float a)
{
    float ver_cub[] =
    {
        -a, -a, a,      a, -a, a,       a, a, a,        -a, a, a,
        a, -a, -a,      -a, -a, -a,     -a, a, -a,       a, a, -a,
        -a, -a, -a,     -a, -a, a,      -a, a, a,        -a, a, -a,
        a, -a, a,      a, -a, -a,       a, a, -a,        a, a, a,
        -a, -a, a,      a, -a, a,       a, -a, -a,        -a, -a, -a,
        -a, a, a,      a, a, a,         a, a, -a,        -a, a, -a,
    };

    float color_arr[] =
    {
        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
        1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
        1, 0.5, 0,5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    //(3 * 8)
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


