/********************************************************************************
** Form generated from reading UI file 'rastros.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RASTROS_H
#define UI_RASTROS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rastros
{
public:

    void setupUi(QWidget *rastros)
    {
        if (rastros->objectName().isEmpty())
            rastros->setObjectName(QStringLiteral("rastros"));
        rastros->resize(400, 300);

        retranslateUi(rastros);

        QMetaObject::connectSlotsByName(rastros);
    } // setupUi

    void retranslateUi(QWidget *rastros)
    {
        rastros->setWindowTitle(QApplication::translate("rastros", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rastros: public Ui_rastros {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RASTROS_H
