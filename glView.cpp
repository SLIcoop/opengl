#include "glView.h"

glView::glView(QWidget *parent)
    : QGLWidget(parent)
{
    const unsigned int SCR_W = 800;
    const unsigned int SCR_H = 600;
    setWindowTitle("QT");
    setGeometry(400, 200, SCR_W, SCR_H);
}

void glView::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 3);
}


void glView::paintGL()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -2);
 
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    //drawCube(0.5);
    drawPyramid();
}


void glView::mousePressEvent(QMouseEvent* mo)
{
    mPos = mo->pos();
}

void glView::mouseMoveEvent(QMouseEvent* mo)
{
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    updateGL();
}

void glView::drawPyramid()
{
    //x, y, z по системе координат
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
        1, 0, 0,    1, 0, 0,    1, 0, 0,
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
    //18 граней(3 * 6)
    glDrawArrays(GL_TRIANGLES, 0, 18);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

//ѕостроение куба
//void glView::drawCube(float a)
//{
//    float ver_cub[] = 
//    {
//        -a, -a, a,      a, -a, a,       a, a, a,        -a, a, a, // передн€€
//        a, -a, -a,      -a, -a, -a,     -a, a, -a,       a, a, -a, // задн€€
//        -a, -a, -a,     -a, -a, a,      -a, a, a,        -a, a, -a, // лева€
//        a, -a, a,      a, -a, -a,       a, a, -a,        a, a, a, // права€ 
//        -a, -a, a,      a, -a, a,       a, -a, -a,        -a, -a, -a, // нижн€€
//        -a, a, a,      a, a, a,         a, a, -a,        -a, a, -a, // верхн€€
//    };
//
//    float color_arr[] =
//    {
//        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
//        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
//        1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
//        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
//        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
//        1, 0.5, 0,5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
//    };
//    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
//    glEnableClientState(GL_VERTEX_ARRAY);
//
//    glColorPointer(3, GL_FLOAT, 0, &color_arr);
//    glEnableClientState(GL_COLOR_ARRAY);
//    //грани куба 24 (3 * 8)
//    glDrawArrays(GL_QUADS, 0, 24);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_COLOR_ARRAY);
//}