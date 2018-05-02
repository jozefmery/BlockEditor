#include "MainWindow.h"
#include "BlockEditor.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <cassert>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setUpChildren();
}

inline void MainWindow::setUpChildren() {
	
	editorTabs = new QTabWidget(this);
	setCentralWidget(editorTabs);

	editorTabs->setTabsClosable(true);
	editorTabs->setMovable(true);

	connect(ui.actionStart, &QAction::triggered, this, &MainWindow::start);
	connect(ui.actionPause, &QAction::triggered, this, &MainWindow::pause);
	connect(ui.actionStop, &QAction::triggered, this, &MainWindow::stop);
	connect(ui.actionNew, &QAction::triggered, this, &MainWindow::createNewFile);
	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openFile);
	connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
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

	if(path != ""){

		createNewTab(path);
	}
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

void MainWindow::showAbout() {


	QMessageBox::information(this, "About", "Simple block scheme editor application written for ICP project.\n"
											"Authors:\n"
											"Denis Dovicic - xdovic01@stud.fit.vutbr.cz\n"
											"Jozef Mery    - xmeryj00@stud.fit.vutbr.cz");	
}

 