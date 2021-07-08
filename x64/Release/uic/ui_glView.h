/********************************************************************************
** Form generated from reading UI file 'glView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLVIEW_H
#define UI_GLVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glViewClass
{
public:

    void setupUi(QWidget *glViewClass)
    {
        if (glViewClass->objectName().isEmpty())
            glViewClass->setObjectName(QString::fromUtf8("glViewClass"));
        glViewClass->resize(600, 400);

        retranslateUi(glViewClass);

        QMetaObject::connectSlotsByName(glViewClass);
    } // setupUi

    void retranslateUi(QWidget *glViewClass)
    {
        glViewClass->setWindowTitle(QCoreApplication::translate("glViewClass", "glView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class glViewClass: public Ui_glViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLVIEW_H
