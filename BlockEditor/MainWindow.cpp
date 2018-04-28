#include "MainWindow.h"
#include "BlockEditor.h"
#include <QDebug>

#include <QDebug>

BlockEditor* blockEditor;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(1024, 768);
	setUpChildren();
}

inline void MainWindow::setUpChildren() {

	blockEditor = new BlockEditor;
	blockEditor->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(blockEditor, SIGNAL(customContextMenuRequested(QPoint)), blockEditor, SLOT(showContextMenu(QPoint)));
	setCentralWidget(blockEditor);

	ui.controlToolBar->addAction(ui.actionStart);
	ui.controlToolBar->addAction(ui.actionPause);
	ui.controlToolBar->addAction(ui.actionStop);

	ui.fileToolBar->addAction(ui.actionNew);
	ui.fileToolBar->addAction(ui.actionOpen);
	ui.fileToolBar->addAction(ui.actionSave);

	ui.controlToolBar->setIconSize(QSize(Scaler::scaleX(35), Scaler::scaleY(35)));
	ui.fileToolBar->setIconSize(QSize(Scaler::scaleX(35), Scaler::scaleY(35)));

	resize(Scaler::scaleX(1024), Scaler::scaleY(768));

	connect(ui.actionStart, &QAction::triggered, this, &MainWindow::start);
	connect(ui.actionPause, &QAction::triggered, this, &MainWindow::pause);
	connect(ui.actionStop, &QAction::triggered, this, &MainWindow::stop);

	ui.menuFILE->setMinimumWidth(Scaler::scaleX(250));
	ui.menuRecent->setMinimumWidth(Scaler::scaleX(250));
}

void MainWindow::start() {
	
	qDebug() << "asd";
}

void MainWindow::pause() {

}

void MainWindow::stop() {

}