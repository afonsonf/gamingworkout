/********************************************************************************
** Form generated from reading UI file 'semaforo.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEMAFORO_H
#define UI_SEMAFORO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Semaforo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *sair;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *mensagem;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox_2;
    QFrame *line_2;
    QComboBox *comboBox;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Semaforo)
    {
        if (Semaforo->objectName().isEmpty())
            Semaforo->setObjectName(QStringLiteral("Semaforo"));
        Semaforo->resize(735, 367);
        verticalLayout = new QVBoxLayout(Semaforo);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sair = new QPushButton(Semaforo);
        sair->setObjectName(QStringLiteral("sair"));

        horizontalLayout->addWidget(sair);

        pushButton_2 = new QPushButton(Semaforo);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        mensagem = new QLabel(Semaforo);
        mensagem->setObjectName(QStringLiteral("mensagem"));

        horizontalLayout->addWidget(mensagem);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(Semaforo);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox_2 = new QComboBox(Semaforo);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        line_2 = new QFrame(Semaforo);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        comboBox = new QComboBox(Semaforo);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        frame = new QFrame(Semaforo);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        horizontalLayout_3->addLayout(gridLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 4);
        horizontalLayout_3->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 4);
        verticalLayout_2->setStretch(2, 2);

        verticalLayout->addWidget(frame);

        verticalLayout->setStretch(1, 1);

        retranslateUi(Semaforo);

        QMetaObject::connectSlotsByName(Semaforo);
    } // setupUi

    void retranslateUi(QWidget *Semaforo)
    {
        Semaforo->setWindowTitle(QApplication::translate("Semaforo", "Form", nullptr));
        sair->setText(QApplication::translate("Semaforo", "Sair", nullptr));
        pushButton_2->setText(QApplication::translate("Semaforo", "New Game", nullptr));
        mensagem->setText(QString());
        label->setText(QApplication::translate("Semaforo", "First Player:", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("Semaforo", "human", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("Semaforo", "bot", nullptr));

        comboBox->setItemText(0, QApplication::translate("Semaforo", "easy", nullptr));
        comboBox->setItemText(1, QApplication::translate("Semaforo", "medium", nullptr));
        comboBox->setItemText(2, QApplication::translate("Semaforo", "hard", nullptr));
        comboBox->setItemText(3, QApplication::translate("Semaforo", "random", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Semaforo: public Ui_Semaforo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEMAFORO_H
