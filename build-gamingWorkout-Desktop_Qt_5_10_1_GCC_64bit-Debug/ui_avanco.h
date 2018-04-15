/********************************************************************************
** Form generated from reading UI file 'avanco.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVANCO_H
#define UI_AVANCO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_avanco
{
public:

    void setupUi(QWidget *avanco)
    {
        if (avanco->objectName().isEmpty())
            avanco->setObjectName(QStringLiteral("avanco"));
        avanco->resize(400, 300);

        retranslateUi(avanco);

        QMetaObject::connectSlotsByName(avanco);
    } // setupUi

    void retranslateUi(QWidget *avanco)
    {
        avanco->setWindowTitle(QApplication::translate("avanco", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class avanco: public Ui_avanco {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVANCO_H
