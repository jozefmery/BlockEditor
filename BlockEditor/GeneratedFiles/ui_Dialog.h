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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *oPorts;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *opration;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *iPorts;

    void setupUi(QWidget *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(242, 161);
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 80, 221, 24));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        oPorts = new QComboBox(layoutWidget);
        oPorts->addItem(QString());
        oPorts->addItem(QString());
        oPorts->setObjectName(QStringLiteral("oPorts"));

        horizontalLayout_5->addWidget(oPorts);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 120, 221, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ok = new QPushButton(layoutWidget1);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout->addWidget(ok);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel = new QPushButton(layoutWidget1);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 20, 221, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        opration = new QComboBox(layoutWidget2);
        opration->addItem(QString());
        opration->addItem(QString());
        opration->addItem(QString());
        opration->addItem(QString());
        opration->setObjectName(QStringLiteral("opration"));

        horizontalLayout_2->addWidget(opration);

        layoutWidget3 = new QWidget(Dialog);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 50, 221, 24));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        iPorts = new QComboBox(layoutWidget3);
        iPorts->addItem(QString());
        iPorts->addItem(QString());
        iPorts->setObjectName(QStringLiteral("iPorts"));

        horizontalLayout_4->addWidget(iPorts);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QWidget *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Output ports:", nullptr));
        oPorts->setItemText(0, QApplication::translate("Dialog", "1", nullptr));
        oPorts->setItemText(1, QApplication::translate("Dialog", "2", nullptr));

        ok->setText(QApplication::translate("Dialog", "OK", nullptr));
        cancel->setText(QApplication::translate("Dialog", "Cancel", nullptr));
        label->setText(QApplication::translate("Dialog", "Operation:", nullptr));
        opration->setItemText(0, QApplication::translate("Dialog", "+", nullptr));
        opration->setItemText(1, QApplication::translate("Dialog", "-", nullptr));
        opration->setItemText(2, QApplication::translate("Dialog", "*", nullptr));
        opration->setItemText(3, QApplication::translate("Dialog", "/", nullptr));

        label_3->setText(QApplication::translate("Dialog", "Input ports:", nullptr));
        iPorts->setItemText(0, QApplication::translate("Dialog", "1", nullptr));
        iPorts->setItemText(1, QApplication::translate("Dialog", "2", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
