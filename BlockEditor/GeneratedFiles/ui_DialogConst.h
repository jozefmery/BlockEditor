/********************************************************************************
** Form generated from reading UI file 'DialogConst.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONST_H
#define UI_DIALOGCONST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogConst
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *value;
    QHBoxLayout *horizontalLayout_4;
    QLabel *outputText;
    QComboBox *output;
    QHBoxLayout *horizontalLayout;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;

    void setupUi(QWidget *DialogConst)
    {
        if (DialogConst->objectName().isEmpty())
            DialogConst->setObjectName(QStringLiteral("DialogConst"));
        DialogConst->resize(264, 117);
        widget = new QWidget(DialogConst);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 244, 96));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(95, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        value = new QLineEdit(widget);
        value->setObjectName(QStringLiteral("value"));
        value->setEnabled(true);

        horizontalLayout_2->addWidget(value);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        outputText = new QLabel(widget);
        outputText->setObjectName(QStringLiteral("outputText"));

        horizontalLayout_4->addWidget(outputText);

        output = new QComboBox(widget);
        output->addItem(QString());
        output->addItem(QString());
        output->addItem(QString());
        output->addItem(QString());
        output->addItem(QString());
        output->setObjectName(QStringLiteral("output"));

        horizontalLayout_4->addWidget(output);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ok = new QPushButton(widget);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout->addWidget(ok);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel = new QPushButton(widget);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(DialogConst);

        QMetaObject::connectSlotsByName(DialogConst);
    } // setupUi

    void retranslateUi(QWidget *DialogConst)
    {
        DialogConst->setWindowTitle(QApplication::translate("DialogConst", "DialogConst", nullptr));
        label->setText(QApplication::translate("DialogConst", "Value:", nullptr));
        value->setText(QApplication::translate("DialogConst", "0", nullptr));
        outputText->setText(QApplication::translate("DialogConst", "Output type:", nullptr));
        output->setItemText(0, QApplication::translate("DialogConst", "double", nullptr));
        output->setItemText(1, QApplication::translate("DialogConst", "integer", nullptr));
        output->setItemText(2, QApplication::translate("DialogConst", "float", nullptr));
        output->setItemText(3, QApplication::translate("DialogConst", "real", nullptr));
        output->setItemText(4, QApplication::translate("DialogConst", "constant", nullptr));

        ok->setText(QApplication::translate("DialogConst", "OK", nullptr));
        cancel->setText(QApplication::translate("DialogConst", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogConst: public Ui_DialogConst {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONST_H
