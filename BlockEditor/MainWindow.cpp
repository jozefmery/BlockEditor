#include "MainWindow.h"
#include "BlockEditor.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <cassert>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(1024, 768);

	setUpChildren();
}

inline void MainWindow::setUpChildren() {
	
	editorTabs = new QTabWidget(this);
	setCentralWidget(editorTabs);

	editorTabs->setTabsClosable(true);
	editorTabs->setMovable(true);

	ui.controlToolBar->addAction(ui.actionStart);
	ui.controlToolBar->addAction(ui.actionPause);
	ui.controlToolBar->addAction(ui.actionStop);

	ui.fileToolBar->addAction(ui.actionNew);
	ui.fileToolBar->addAction(ui.actionOpen);
	ui.fileToolBar->addAction(ui.actionSave);

	ui.controlToolBar->setIconSize(QSize(Scaler::scaleX(35), Scaler::scaleY(35)));
	ui.fileToolBar->setIconSize(QSize(Scaler::scaleX(35), Scaler::scaleY(35)));

	//resize(Scaler::scaleX(1024), Scaler::scaleY(768));

	connect(ui.actionStart, &QAction::triggered, this, &MainWindow::start);
	connect(ui.actionPause, &QAction::triggered, this, &MainWindow::pause);
	connect(ui.actionStop, &QAction::triggered, this, &MainWindow::stop);
	connect(ui.actionNew, &QAction::triggered, this, &MainWindow::createNewFile);
	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openFile);

	ui.menuFILE->setMinimumWidth(Scaler::scaleX(250));
	ui.menuRecent->setMinimumWidth(Scaler::scaleX(250));
}

void MainWindow::start() {
	
	
}

void MainWindow::pause() {

}

void MainWindow::stop() {

}

void MainWindow::createNewFile() {

	
	
}

void MainWindow::openFile() {
	
	auto path = QFileDialog::getOpenFileName(this, "Open Scheme", "", "Scheme file (*.scheme);;All Files (*.*)");
	createNewTab(path);
}

void MainWindow::createNewTab(QString& path) {

	BlockEditor* blockEditor = new BlockEditor;
	blockEditor->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(blockEditor, SIGNAL(customContextMenuRequested(QPoint)), blockEditor, SLOT(showContextMenu(QPoint)));

    QRegularExpression re("(?:.*/)*(.*)\\..*");
	auto match = re.match(path);

	assert(match.hasMatch());

	const auto tab_name = match.captured(1);

	editorTabs->addTab(blockEditor, tab_name);

}

 