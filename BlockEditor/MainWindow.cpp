#include "MainWindow.h"
#include "BlockEditor.h"

BlockEditor* blockEditor;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setUpChildren();
}

inline void MainWindow::setUpChildren() {

	blockEditor = new BlockEditor;
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

	setFixedSize(Scaler::scaleX(1024), Scaler::scaleY(768));

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

