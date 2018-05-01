/********************************************************************************
** Form generated from reading UI file 'Dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *opration;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *input;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *output;
    QHBoxLayout *horizontalLayout;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;

    void setupUi(QWidget *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(263, 152);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 244, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
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
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        opration = new QComboBox(layoutWidget);
        opration->addItem(QString());
        opration->addItem(QString());
        opration->addItem(QString());
        opration->addItem(QString());
        opration->setObjectName(QStringLiteral("opration"));

        horizontalLayout_2->addWidget(opration);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        input = new QComboBox(layoutWidget);
        input->addItem(QString());
        input->addItem(QString());
        input->addItem(QString());
        input->addItem(QString());
        input->addItem(QString());
        input->setObjectName(QStringLiteral("input"));

        horizontalLayout_3->addWidget(input);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        output = new QComboBox(layoutWidget);
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
        ok = new QPushButton(layoutWidget);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout->addWidget(ok);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel = new QPushButton(layoutWidget);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QWidget *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog", "Operation:", nullptr));
        opration->setItemText(0, QApplication::translate("Dialog", "+", nullptr));
        opration->setItemText(1, QApplication::translate("Dialog", "-", nullptr));
        opration->setItemText(2, QApplication::translate("Dialog", "*", nullptr));
        opration->setItemText(3, QApplication::translate("Dialog", "/", nullptr));

        label_2->setText(QApplication::translate("Dialog", "Input type:", nullptr));
        input->setItemText(0, QApplication::translate("Dialog", "double", nullptr));
        input->setItemText(1, QApplication::translate("Dialog", "integer", nullptr));
        input->setItemText(2, QApplication::translate("Dialog", "real", nullptr));
        input->setItemText(3, QApplication::translate("Dialog", "float", nullptr));
        input->setItemText(4, QApplication::translate("Dialog", "constant", nullptr));

        label_4->setText(QApplication::translate("Dialog", "Output type:", nullptr));
        output->setItemText(0, QApplication::translate("Dialog", "double", nullptr));
        output->setItemText(1, QApplication::translate("Dialog", "integer", nullptr));
        output->setItemText(2, QApplication::translate("Dialog", "float", nullptr));
        output->setItemText(3, QApplication::translate("Dialog", "real", nullptr));
        output->setItemText(4, QApplication::translate("Dialog", "constant", nullptr));

        ok->setText(QApplication::translate("Dialog", "OK", nullptr));
        cancel->setText(QApplication::translate("Dialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
