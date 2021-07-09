#include "widget.h"

Widget::Widget(QWidget *parent)
    : QGLWidget(parent)
{
    const unsigned int SCR_W = 800;
    const unsigned int SCR_H = 600;
    setWindowTitle("QT");
    setGeometry(400, 200, SCR_W, SCR_H);
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent* mo)
{
    mPos = mo->pos();
}

void Widget::mouseMoveEvent(QMouseEvent* mo)
{
    double M_PI = 3.14;
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    updateGL();
}

void Widget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 1, 5);
}

void Widget::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -2);

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    //drawCube(0.5);
    //drawPyramid();
    drawPrisma();
    //drawParall();
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
        //-0.25, -0.5, 0.5,   0.25, -0.5, 0.5,    0.5, -0.5, 0,   0.25, -0.5, -0.5,   -0.25, -0.5, -0.5,  -0.5, -0.5, 0,
        //-0.25, 0.5, 0.5,   0.25, 0.5, 0.5,    0.5, 0.5, 0,   0.25, 0.5, -0.5,   -0.25, 0.5, -0.5,  -0.5, 0.5, 0

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
        //, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        //1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0

         0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
         1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
         0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
         1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
         1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,
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
//        1, -0.5, 0.25,   -1, -0.5, 0.25,     -1, 0.5, 0.25,    1, 0.5, 0.25,
//        1, -0.5, 0.25,   1, -0.5, -0.25,      1, 0.5, -0.25,    1, 0.5, 0.25,
//        -1, -0.5, 0.25,  -1, -0.5, -0.25,     -1, 0.5, -0.25,   -1, 0.5, 0.25,
//        -1, -0.5, 0.25,  1, -0.5, 0.25,       1, -0.5, -0.25,   -1, -0.5, -0.25,
//        -1, 0.5, 0.25,   1, 0.5, 0.25,        1, 0.5, -0.25,    -1, 0.5, -0.25,
//        1, -0.5, -0.25,   -1, -0.5, -0.25,     -1, 0.5, -0.25,    1, 0.5, -0.25,
        0.75, -0.5, 0.5,   -0.75, -0.5, 0.5,  -0.75, 0.5, 0.5,   0.75, 0.5, 0.5,
        0.75, -0.5, -0.5,   -0.75, -0.5, -0.5,  -0.75, 0.5, -0.5,   0.75, 0.5, -0.5,
        0.75, -0.5, 0.5,    0.75, 0.5, 0.5,     0.75, 0.5, -0.5,    0.75, -0.5, -0.5,
        -0.75, -0.5, 0.5,    -0.75, 0.5, 0.5,     -0.75, 0.5, -0.5,    -0.75, -0.5, -0.5,
        0.75, -0.5, 0.5,    -0.75, -0.5, 0.5,   -0.75, -0.5, -0.5,     0.75, -0.5,  -0.5,
        0.75, 0.5, 0.5,    -0.75, 0.5, 0.5,   -0.75, 0.5, -0.5,     0.75, 0.5,  -0.5
    };

    float color_arr[] =
    {
        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
        0, 1, 0,    0, 1, 0,    0, 1, 0,    0, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
        1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_parall);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    //(4 * 6)
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
        1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0,    1, 0.5, 0
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    //(4 * 6)
    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


