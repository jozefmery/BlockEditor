#include "MainWindow.h"
#include "BlockEditor.h"

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

	controlActions[0] = new QAction(this);
	controlActions[1] = new QAction(this);
	controlActions[2] = new QAction(this);


	controlActions[0]->setIcon(QIcon(":/Resources/play.png"));
	controlActions[1]->setIcon(QIcon(":/Resources/pause.png"));
	controlActions[2]->setIcon(QIcon(":/Resources/stop.png"));

	ui.controlToolBar->addAction(controlActions[0]);
	ui.controlToolBar->addAction(controlActions[1]);
	ui.controlToolBar->addAction(controlActions[2]);

	ui.controlToolBar->setIconSize(QSize(Scaler::scaleX(35), Scaler::scaleY(35)));

	resize(Scaler::scaleX(1024), Scaler::scaleY(768));

	connect(controlActions[0], &QAction::triggered, this, &MainWindow::start);
	connect(controlActions[1], &QAction::triggered, this, &MainWindow::pause);
	connect(controlActions[2], &QAction::triggered, this, &MainWindow::stop);

}

void MainWindow::start() {
	
}

void MainWindow::pause() {

}

void MainWindow::stop() {

}