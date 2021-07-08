#ifndef WIDGET_H
#define WIDGET_H
#pragma once

#include <QtWidgets/QOpenGLWidget>
#include <QTimer>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <QMouseEvent>
#include <QtOpenGL/QGLWidget>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GlU32.lib")

class Widget : public QGLWidget
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
    void drawPrisma();
    void drawParall();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
