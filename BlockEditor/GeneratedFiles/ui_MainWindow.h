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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionSave_all;
    QAction *actionClose;
    QAction *actionClose_all;
    QAction *actionExit;
    QAction *actionStart;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionClear;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menuFILE;
    QMenu *menuRecent;
    QMenu *menuEDIT;
    QMenu *menuVIEW;
    QMenu *menuSCHEME;
    QMenu *menuSETTINGS;
    QMenu *menuHELP;
    QToolBar *controlToolBar;
    QToolBar *fileToolBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(592, 395);
        MainWindowClass->setStyleSheet(QLatin1String("QWidget{\n"
"	\n"
"	color: #FFFFFF;\n"
"	background: rgb(66,66,66);\n"
"	font-size: 11p;\n"
"}\n"
"\n"
"QToolBar {\n"
"	\n"
"	border: 0px;\n"
"	font-size: 11p;\n"
"\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"\n"
"	background: rgb(112, 112, 112);\n"
"}\n"
"\n"
"QMenuBar::item:pressed {\n"
"	background: rgb(50, 50, 50);\n"
"}\n"
"\n"
"QMenuBar {\n"
"\n"
"	padding-left: 5px;\n"
"	padding-right: 5px;\n"
"	margin-top: 5px;\n"
"	margin-bottom: 5px;\n"
"\n"
"}\n"
"\n"
"QMenu::separator {\n"
"    height: 1px;\n"
"    background: rgb(112,112,112);\n"
"    margin-left: 5px;\n"
"    margin-right: 20px;\n"
"}\n"
"\n"
"QMenu {\n"
"	background: rgb(50, 50, 50);\n"
"}\n"
"\n"
"QMenu::item:selected{\n"
"	background: rgb(112, 112, 112);\n"
"}"));
        MainWindowClass->setTabShape(QTabWidget::Rounded);
        actionNew = new QAction(MainWindowClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/new_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionNew->setShortcutVisibleInContextMenu(true);
        actionOpen = new QAction(MainWindowClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/open_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionOpen->setShortcutVisibleInContextMenu(true);
        actionSave = new QAction(MainWindowClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave->setShortcutVisibleInContextMenu(true);
        actionSave_as = new QAction(MainWindowClass);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setShortcutVisibleInContextMenu(true);
        actionSave_all = new QAction(MainWindowClass);
        actionSave_all->setObjectName(QStringLiteral("actionSave_all"));
        actionSave_all->setShortcutVisibleInContextMenu(true);
        actionClose = new QAction(MainWindowClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose_all = new QAction(MainWindowClass);
        actionClose_all->setObjectName(QStringLiteral("actionClose_all"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setShortcutVisibleInContextMenu(true);
        actionStart = new QAction(MainWindowClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon3);
        actionPause = new QAction(MainWindowClass);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon4);
        actionStop = new QAction(MainWindowClass);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon5);
        actionClear = new QAction(MainWindowClass);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Resources/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon6);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 592, 26));
        QFont font;
        font.setPointSize(11);
        menuBar->setFont(font);
        menuBar->setStyleSheet(QStringLiteral(""));
        menuFILE = new QMenu(menuBar);
        menuFILE->setObjectName(QStringLiteral("menuFILE"));
        menuFILE->setFont(font);
        menuFILE->setContextMenuPolicy(Qt::DefaultContextMenu);
        menuFILE->setStyleSheet(QStringLiteral(""));
        menuRecent = new QMenu(menuFILE);
        menuRecent->setObjectName(QStringLiteral("menuRecent"));
        menuEDIT = new QMenu(menuBar);
        menuEDIT->setObjectName(QStringLiteral("menuEDIT"));
        menuVIEW = new QMenu(menuBar);
        menuVIEW->setObjectName(QStringLiteral("menuVIEW"));
        menuSCHEME = new QMenu(menuBar);
        menuSCHEME->setObjectName(QStringLiteral("menuSCHEME"));
        menuSETTINGS = new QMenu(menuBar);
        menuSETTINGS->setObjectName(QStringLiteral("menuSETTINGS"));
        menuHELP = new QMenu(menuBar);
        menuHELP->setObjectName(QStringLiteral("menuHELP"));
        MainWindowClass->setMenuBar(menuBar);
        controlToolBar = new QToolBar(MainWindowClass);
        controlToolBar->setObjectName(QStringLiteral("controlToolBar"));
        controlToolBar->setStyleSheet(QStringLiteral(""));
        controlToolBar->setAllowedAreas(Qt::TopToolBarArea);
        controlToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, controlToolBar);
        fileToolBar = new QToolBar(MainWindowClass);
        fileToolBar->setObjectName(QStringLiteral("fileToolBar"));
        fileToolBar->setStyleSheet(QStringLiteral("border: 0px;"));
        fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
        fileToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, fileToolBar);

        menuBar->addAction(menuFILE->menuAction());
        menuBar->addAction(menuEDIT->menuAction());
        menuBar->addAction(menuVIEW->menuAction());
        menuBar->addAction(menuSCHEME->menuAction());
        menuBar->addAction(menuSETTINGS->menuAction());
        menuBar->addAction(menuHELP->menuAction());
        menuFILE->addAction(actionNew);
        menuFILE->addAction(actionOpen);
        menuFILE->addAction(menuRecent->menuAction());
        menuFILE->addSeparator();
        menuFILE->addAction(actionSave);
        menuFILE->addAction(actionSave_as);
        menuFILE->addAction(actionSave_all);
        menuFILE->addSeparator();
        menuFILE->addAction(actionClose);
        menuFILE->addAction(actionClose_all);
        menuFILE->addAction(actionExit);
        menuRecent->addAction(actionClear);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "BlockEditor", nullptr));
        actionNew->setText(QApplication::translate("MainWindowClass", "New", nullptr));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindowClass", "Create new scheme", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindowClass", "Open", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindowClass", "Open an existing scheme", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindowClass", "Save", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindowClass", "Save current document", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_as->setText(QApplication::translate("MainWindowClass", "Save as...", nullptr));
        actionSave_as->setIconText(QApplication::translate("MainWindowClass", "Save as...", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave_as->setToolTip(QApplication::translate("MainWindowClass", "Choose how to save", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_as->setShortcut(QApplication::translate("MainWindowClass", "Alt+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_all->setText(QApplication::translate("MainWindowClass", "Save all", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSave_all->setToolTip(QApplication::translate("MainWindowClass", "Save all open documents", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_all->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionClose->setText(QApplication::translate("MainWindowClass", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindowClass", "Close current document", nullptr));
#endif // QT_NO_TOOLTIP
        actionClose_all->setText(QApplication::translate("MainWindowClass", "Close all", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClose_all->setToolTip(QApplication::translate("MainWindowClass", "Close all open documents", nullptr));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", nullptr));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindowClass", "Exit the application", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionStart->setText(QApplication::translate("MainWindowClass", "Start Execution", nullptr));
#ifndef QT_NO_TOOLTIP
        actionStart->setToolTip(QApplication::translate("MainWindowClass", "Start execution of the selected scheme.", nullptr));
#endif // QT_NO_TOOLTIP
        actionPause->setText(QApplication::translate("MainWindowClass", "Pause Execution", nullptr));
        actionStop->setText(QApplication::translate("MainWindowClass", "Stop Execution", nullptr));
        actionClear->setText(QApplication::translate("MainWindowClass", "Clear", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("MainWindowClass", "Clear recent files", nullptr));
#endif // QT_NO_TOOLTIP
        menuFILE->setTitle(QApplication::translate("MainWindowClass", "FILE", nullptr));
        menuRecent->setTitle(QApplication::translate("MainWindowClass", "Recent", nullptr));
        menuEDIT->setTitle(QApplication::translate("MainWindowClass", "EDIT", nullptr));
        menuVIEW->setTitle(QApplication::translate("MainWindowClass", "VIEW", nullptr));
        menuSCHEME->setTitle(QApplication::translate("MainWindowClass", "SCHEME", nullptr));
        menuSETTINGS->setTitle(QApplication::translate("MainWindowClass", "SETTINGS", nullptr));
        menuHELP->setTitle(QApplication::translate("MainWindowClass", "HELP", nullptr));
        fileToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
