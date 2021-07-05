#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_texture(0), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0f); //размер ребра
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0, 0.0, -5.0);

    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);
    m_program.setUniformValue("qt_Texture0", 0);

    m_arrayBuffer.bind();

    int offset = 0;

    int vertLoc = m_program.attributeLocation("qt_Vertex");
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = m_program.attributeLocation("qt_MultiTexCoord0");
    m_program.enableAttributeArray(texLoc);
    m_program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Widget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
        close();

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))
        close();

    if (!m_program.link())
        close();
}

void Widget::initCube(float width)
{
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;
    //выстраивание граней QVector3D(x, y, z)
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0, 0.0), QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for (int i = 0; i < 24; i += 4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    //заполнение буфферизации array | index
    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

