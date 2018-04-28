/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionRecent;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionSave_all;
    QAction *actionClose;
    QAction *actionClose_all;
    QAction *actionExit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFILE;
    QMenu *menuEDIT;
    QToolBar *controlToolBar;
    QToolBar *fileToolBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 400);
        MainWindowClass->setStyleSheet(QLatin1String("color: #FFFFFF;\n"
"background: rgb(66,66,66);\n"
"font-size: 11p;"));
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionRecent = new QAction(MainWindowClass);
        actionRecent->setObjectName(QStringLiteral("actionRecent"));
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(MainWindowClass);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_all = new QAction(MainWindowClass);
        actionSave_all->setObjectName(QStringLiteral("actionSave_all"));
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose_all = new QAction(MainWindowClass);
        actionClose_all->setObjectName(QStringLiteral("actionClose_all"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        QFont font;
        font.setPointSize(11);
        menuBar->setFont(font);
        menuBar->setStyleSheet(QStringLiteral(""));
        menuFILE = new QMenu(menuBar);
        menuFILE->setObjectName(QStringLiteral("menuFILE"));
        menuFILE->setFont(font);
        menuFILE->setStyleSheet(QStringLiteral(""));
        menuEDIT = new QMenu(menuBar);
        menuEDIT->setObjectName(QStringLiteral("menuEDIT"));
        MainWindowClass->setMenuBar(menuBar);
        controlToolBar = new QToolBar(MainWindowClass);
        controlToolBar->setObjectName(QStringLiteral("controlToolBar"));
        controlToolBar->setStyleSheet(QStringLiteral(""));
        controlToolBar->setAllowedAreas(Qt::TopToolBarArea);
        controlToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, controlToolBar);
        fileToolBar = new QToolBar(MainWindowClass);
        fileToolBar->setObjectName(QStringLiteral("fileToolBar"));
        fileToolBar->setStyleSheet(QStringLiteral(""));
        fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
        fileToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, fileToolBar);

        menuBar->addAction(menuFILE->menuAction());
        menuBar->addAction(menuEDIT->menuAction());
        menuFILE->addAction(actionNew);
        menuFILE->addAction(actionOpen);
        menuFILE->addAction(actionRecent);
        menuFILE->addSeparator();
        menuFILE->addAction(actionSave);
        menuFILE->addAction(actionSave_as);
        menuFILE->addAction(actionSave_all);
        menuFILE->addSeparator();
        menuFILE->addAction(actionClose);
        menuFILE->addAction(actionClose_all);
        menuFILE->addAction(actionExit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        actionNew->setText(QApplication::translate("MainWindowClass", "New", nullptr));
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", nullptr));
        actionRecent->setText(QApplication::translate("MainWindowClass", "Recent", nullptr));
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", nullptr));
        actionSave_as->setText(QApplication::translate("MainWindowClass", "Save as", nullptr));
        actionSave_all->setText(QApplication::translate("MainWindowClass", "Save all", nullptr));
        actionClose->setText(QApplication::translate("MainWindowClass", "Close", nullptr));
        actionClose_all->setText(QApplication::translate("MainWindowClass", "Close all", nullptr));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", nullptr));
        menuFILE->setTitle(QApplication::translate("MainWindowClass", "FILE", nullptr));
        menuEDIT->setTitle(QApplication::translate("MainWindowClass", "EDIT", nullptr));
        fileToolBar->setWindowTitle(QApplication::translate("MainWindowClass", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
