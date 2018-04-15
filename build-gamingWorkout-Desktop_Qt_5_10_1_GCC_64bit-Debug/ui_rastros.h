/********************************************************************************
** Form generated from reading UI file 'rastros.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RASTROS_H
#define UI_RASTROS_H

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

class Ui_rastros
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *sair;
    QPushButton *new_game;
    QSpacerItem *horizontalSpacer_4;
    QLabel *mensagem;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *comboBox_2;
    QFrame *line;
    QComboBox *comboBox;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *rastros)
    {
        if (rastros->objectName().isEmpty())
            rastros->setObjectName(QStringLiteral("rastros"));
        rastros->resize(677, 429);
        verticalLayout = new QVBoxLayout(rastros);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sair = new QPushButton(rastros);
        sair->setObjectName(QStringLiteral("sair"));

        horizontalLayout->addWidget(sair);

        new_game = new QPushButton(rastros);
        new_game->setObjectName(QStringLiteral("new_game"));

        horizontalLayout->addWidget(new_game);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        mensagem = new QLabel(rastros);
        mensagem->setObjectName(QStringLiteral("mensagem"));

        horizontalLayout->addWidget(mensagem);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(rastros);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox_2 = new QComboBox(rastros);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        line = new QFrame(rastros);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        comboBox = new QComboBox(rastros);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        frame = new QFrame(rastros);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 66, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 3);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 66, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 3);
        verticalLayout_2->setStretch(2, 1);

        verticalLayout->addWidget(frame);

        verticalLayout->setStretch(1, 1);

        retranslateUi(rastros);

        QMetaObject::connectSlotsByName(rastros);
    } // setupUi

    void retranslateUi(QWidget *rastros)
    {
        rastros->setWindowTitle(QApplication::translate("rastros", "Form", nullptr));
        sair->setText(QApplication::translate("rastros", "Sair", nullptr));
        new_game->setText(QApplication::translate("rastros", "New Game", nullptr));
        mensagem->setText(QString());
        label->setText(QApplication::translate("rastros", "First Player", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("rastros", "Human", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("rastros", "Bot", nullptr));

        comboBox->setItemText(0, QApplication::translate("rastros", "random", nullptr));
        comboBox->setItemText(1, QApplication::translate("rastros", "easy", nullptr));
        comboBox->setItemText(2, QApplication::translate("rastros", "medium", nullptr));
        comboBox->setItemText(3, QApplication::translate("rastros", "hard", nullptr));

    } // retranslateUi

};

namespace Ui {
    class rastros: public Ui_rastros {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RASTROS_H
