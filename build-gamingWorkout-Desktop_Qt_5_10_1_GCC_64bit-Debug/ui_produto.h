/********************************************************************************
** Form generated from reading UI file 'produto.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUTO_H
#define UI_PRODUTO_H

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

class Ui_produto
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *sair_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_7;
    QLabel *mensagem_2;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label;
    QComboBox *comboBox_2;
    QFrame *line_3;
    QComboBox *comboBox;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *produto)
    {
        if (produto->objectName().isEmpty())
            produto->setObjectName(QStringLiteral("produto"));
        produto->resize(874, 553);
        verticalLayout = new QVBoxLayout(produto);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sair_2 = new QPushButton(produto);
        sair_2->setObjectName(QStringLiteral("sair_2"));

        horizontalLayout_2->addWidget(sair_2);

        pushButton_2 = new QPushButton(produto);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        mensagem_2 = new QLabel(produto);
        mensagem_2->setObjectName(QStringLiteral("mensagem_2"));

        horizontalLayout_2->addWidget(mensagem_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        label = new QLabel(produto);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBox_2 = new QComboBox(produto);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_2->addWidget(comboBox_2);

        line_3 = new QFrame(produto);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_3);

        comboBox = new QComboBox(produto);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(produto);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

        horizontalLayout_4->addLayout(gridLayout_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 4);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 4);
        verticalLayout_3->setStretch(2, 2);

        verticalLayout->addWidget(frame);


        retranslateUi(produto);

        QMetaObject::connectSlotsByName(produto);
    } // setupUi

    void retranslateUi(QWidget *produto)
    {
        produto->setWindowTitle(QApplication::translate("produto", "Form", nullptr));
        sair_2->setText(QApplication::translate("produto", "Sair", nullptr));
        pushButton_2->setText(QApplication::translate("produto", "New Game", nullptr));
        mensagem_2->setText(QString());
        label->setText(QApplication::translate("produto", "First Player:", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("produto", "human", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("produto", "bot", nullptr));

        comboBox->setItemText(0, QApplication::translate("produto", "easy", nullptr));
        comboBox->setItemText(1, QApplication::translate("produto", "medium", nullptr));
        comboBox->setItemText(2, QApplication::translate("produto", "hard", nullptr));
        comboBox->setItemText(3, QApplication::translate("produto", "random", nullptr));

    } // retranslateUi

};

namespace Ui {
    class produto: public Ui_produto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUTO_H
