#pragma once

#include <QtWidgets/QWidget>
#include "ui_glView.h"
#include <QtOpenGL>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GlU32.lib")

class glView : public QGLWidget
{
    Q_OBJECT

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void drawPyramid();

public:
    glView(QWidget *parent = Q_NULLPTR);

private:
    Ui::glViewClass ui;
};
