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
#include <QtWidgets/QTabWidget>
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
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QMenu *menuFILE;
    QMenu *menuRecent;
    QMenu *menuHELP;
    QToolBar *controlToolBar;
    QToolBar *fileToolBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(934, 756);
        MainWindowClass->setStyleSheet(QLatin1String("QWidget, QDialog{\n"
"	\n"
"	color: rgb(244, 244, 244);\n"
"	background: rgb(66,66,66);\n"
"	font-size: 12pt;\n"
"	font-family: Verdana;\n"
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
"QMenuBar::item {\n"
"\n"
"	padding-left: 1.1em;\n"
"	padding-right: 1.1em;\n"
"	padding-top: 0.3em;\n"
"	padding-bottom:  0.3em;\n"
"}\n"
"\n"
"QMenu::separator {\n"
"    height: 0.1em;\n"
"    background: rgb(112,112,112);\n"
"    margin-left: 1em;\n"
"    margin-right: 3em;\n"
"	margin-top: 0.5em;\n"
"	margin-bottom: 0.5em;\n"
"}\n"
"\n"
"QMenu {\n"
"	background: rgb(50, 50, 50);\n"
"	min-width: 70ex;\n"
"}\n"
"\n"
"QMenu::item:selected{\n"
"	background: rgb(112, 112, 112);\n"
"}\n"
"\n"
"QTabWidget::pane { \n"
"   \n"
"	 border: 0.1em solid white;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
" \n"
"    border: 0.1em solid white;\n"
"	min-width: 25ex;\n"
"    min-height: 3ex;\n"
"    padding: 0.4em;\n"
"	border-top-l"
                        "eft-radius: 0.3em;\n"
"    border-top-right-radius: 0.3em;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: rgb(112, 112, 112);\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"    margin-left: -4px;\n"
"    margin-right:  -4px;\n"
"	border-bottom-width: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected{\n"
"    margin-top: 0.2em;\n"
"}\n"
"\n"
"QTabBar::tab:first:selected {\n"
"    margin-left: 0;\n"
"}\n"
"\n"
"QTabBar::tab:last:selected {\n"
"    margin-right: 0; \n"
"}\n"
"\n"
"QTabBar::tab:only-one {\n"
"    margin: 0;\n"
"}\n"
"\n"
"QTabBar::close-button:hover{\n"
"	image: url(\":/Resources/close.png\");\n"
"}\n"
"\n"
"QTabBar::close-button{\n"
"	image: url(\":/Resources/close_off.png\");\n"
"}\n"
"\n"
"QToolBar{\n"
"	\n"
"	border: 0px;\n"
"}\n"
"\n"
"\n"
""));
        MainWindowClass->setIconSize(QSize(40, 40));
        MainWindowClass->setToolButtonStyle(Qt::ToolButtonIconOnly);
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
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/Resources/close.png"), QSize(), QIcon::Normal, QIcon::On);
        actionClose->setIcon(icon3);
        actionClose_all = new QAction(MainWindowClass);
        actionClose_all->setObjectName(QStringLiteral("actionClose_all"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionExit->setShortcutVisibleInContextMenu(true);
        actionStart = new QAction(MainWindowClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon4);
        actionPause = new QAction(MainWindowClass);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon5);
        actionStop = new QAction(MainWindowClass);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon6);
        actionClear = new QAction(MainWindowClass);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Resources/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon7);
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Resources/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon8);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 934, 31));
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(12);
        menuBar->setFont(font);
        menuBar->setStyleSheet(QStringLiteral(""));
        menuFILE = new QMenu(menuBar);
        menuFILE->setObjectName(QStringLiteral("menuFILE"));
        menuFILE->setFont(font);
        menuFILE->setContextMenuPolicy(Qt::DefaultContextMenu);
        menuFILE->setStyleSheet(QStringLiteral(""));
        menuRecent = new QMenu(menuFILE);
        menuRecent->setObjectName(QStringLiteral("menuRecent"));
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
        fileToolBar->setStyleSheet(QStringLiteral(""));
        fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
        fileToolBar->setFloatable(false);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, fileToolBar);

        menuBar->addAction(menuFILE->menuAction());
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
        menuHELP->addAction(actionAbout);
        controlToolBar->addAction(actionStart);
        controlToolBar->addAction(actionPause);
        controlToolBar->addAction(actionStop);
        fileToolBar->addAction(actionNew);
        fileToolBar->addAction(actionOpen);
        fileToolBar->addAction(actionSave);
        fileToolBar->addAction(actionClose);

        retranslateUi(MainWindowClass);

        tabWidget->setCurrentIndex(1);


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
        actionAbout->setText(QApplication::translate("MainWindowClass", "About", nullptr));
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("MainWindowClass", "F1", nullptr));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindowClass", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindowClass", "Tab 2", nullptr));
        menuFILE->setTitle(QApplication::translate("MainWindowClass", "FILE", nullptr));
        menuRecent->setTitle(QApplication::translate("MainWindowClass", "Recent", nullptr));
        menuHELP->setTitle(QApplication::translate("MainWindowClass", "HELP", nullptr));
        fileToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
