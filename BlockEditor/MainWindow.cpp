#include "MainWindow.h"
#include "BlockEditor.h"

#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>

constexpr int NOT_FOUND = -1;
Computation* computation;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setUpChildren();
}

inline void MainWindow::setUpChildren() {
	
	computation = nullptr;

	editorTabs = new QTabWidget(this);
	setCentralWidget(editorTabs);

	editorTabs->setTabsClosable(true);
	editorTabs->setMovable(true);

	connect(ui.actionStart, &QAction::triggered, this, &MainWindow::start);
	connect(ui.actionPause, &QAction::triggered, this, &MainWindow::pause);
	connect(ui.actionStop, &QAction::triggered, this, &MainWindow::stop);
	connect(ui.actionNew, &QAction::triggered, this, &MainWindow::createNewFile);
	connect(ui.actionOpen, &QAction::triggered, this, &MainWindow::openFileBrowse);
	connect(ui.actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
	connect(ui.actionClear, &QAction::triggered, this, &MainWindow::clearHistory);
	connect(ui.actionClose, &QAction::triggered, this, &MainWindow::closeCurrent);
	connect(editorTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
	connect(ui.actionClose_all, &QAction::triggered, this, &MainWindow::closeAll);
	connect(ui.actionExit, &QAction::triggered, this, &MainWindow::exitApp);

	auto rect = QApplication::desktop()->availableGeometry();

	resize(static_cast<int>(rect.width() * 0.7), static_cast<int>(rect.height() * 0.7));

	this->setIconSize(QSize(50 * (rect.width() / 1920), 50 * (rect.width() / 1920)));
}

void MainWindow::start() {
	
	if (editorTabs->currentIndex() == -1) { return; }

	BlockEditor* currentView = dynamic_cast<BlockEditor*>(editorTabs->currentWidget());

	if (computation == nullptr && currentView->getActualBlock()) {
		currentView->getResultBlock()->getInputs()[0]->setValue(NULL);
		currentView->getResultBlock()->getInputs()[0]->setName(nullptr);
		currentView->getResultBlock()->getInputs()[0]->setHasVal(false);

		QTextCursor cursor(currentView->getResultBlock()->getOperationText()->document());
		cursor.setPosition(0);
		cursor.select(QTextCursor::WordUnderCursor);
		cursor.beginEditBlock();
		cursor.insertText("RESULT");
		cursor.endEditBlock();
		cursor.removeSelectedText();

		for (Block* block: currentView->getBlocks()) {
			if (block->getBlockType() == BLOCK) {
				for (Block::BlockIO* input : block->getInputs()) {
					input->setValue(NULL);
					input->setHasVal(false);
				}
				for (Block::BlockIO* output : block->getOutputs()) {
					output->setValue(NULL);
					output->setHasVal(false);
				}
			}
		}

		computation = new Computation(currentView);
		computation->start();
	} else if (currentView->getActualBlock() == nullptr) {
		QMessageBox messageBox;
		messageBox.setText("Set start position!");
		messageBox.exec();
	} else if (computation != nullptr) {
		QMessageBox messageBox;
		messageBox.setText("Computation in progress!");
		messageBox.exec();
	}
}

void MainWindow::pause() {
	
}

void MainWindow::stop() {
	
}

void MainWindow::createNewFile() {

	EditorFile file;
	files.push_back(file);
	createNewTab(file.getDisplayPath());
}

void MainWindow::clearHistory() {
	
	auto actions = ui.menuRecent->actions();

	for(size_t i = 1; i < actions.size(); i++) {
		
		ui.menuRecent->removeAction(actions[i]);
	}
}


void MainWindow::openFileBrowse() {
	
	auto path = QFileDialog::getOpenFileName(this, "Open Scheme", "", "Scheme file (*.scheme);;All Files (*.*)");

	// got canceled
	if(path == ""){
		
		return;
	}

	openFile(path, true);
}

void MainWindow::createNewTab(const QString& name) {

	BlockEditor* blockEditor = new BlockEditor;
	blockEditor->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(blockEditor, SIGNAL(customContextMenuRequested(QPoint)), blockEditor, SLOT(showContextMenu(QPoint)));

	editorTabs->addTab(blockEditor, name);

}

void MainWindow::showAbout() {


	QMessageBox::information(this, "About", "Simple block scheme editor application written for ICP project.\n"
											"Authors:\n"
											"Denis Dovicic - xdovic01@stud.fit.vutbr.cz\n"
											"Jozef Mery    - xmeryj00@stud.fit.vutbr.cz");	
}

int MainWindow::getFileIndex(const QString fullPath) {
	

	for(size_t i = 0; i < files.size(); i++) {
		
		if(files[i].getFullPath() == fullPath) {
			
			return static_cast<int>(i);
		}

	}

	return NOT_FOUND;
}

void MainWindow::openFile(const QString path, const bool addToRecent)
{
	int idx = getFileIndex(path);

	if (idx == NOT_FOUND) {

		// open file
		EditorFile file(path);

		createNewTab(file.getDisplayPath());

		files.push_back(file);
		editorTabs->setCurrentIndex(static_cast<int>(files.size() - 1));

		// add to recent
		if(addToRecent) {
			
			auto action = new QAction();

			action->setText(path);

			auto actions = ui.menuRecent->actions();

			// no history
			if(actions.size() == 1)	{
				
				ui.menuRecent->addAction(action);

			} else {
				// insert to beggining
				ui.menuRecent->insertAction(actions.at(1), action);

			}

			connect(action, &QAction::triggered, this, [action, this] { this->openFile(action->text(), false); });
		}
	} else {

		// focus on file
		editorTabs->setCurrentIndex(idx);
	}
}

void MainWindow::closeFile(const int idx) {

	/*
	int idx = editorTabs->currentIndex();

	// no file open
	if (idx == -1) { return; }
	 */

	editorTabs->removeTab(idx);
	files.erase(files.begin() + idx);
}

void MainWindow::closeCurrent() {

	int idx = editorTabs->currentIndex();

	// no file open
	if (idx == -1) { return; }
	
	closeFile(idx);
}

void MainWindow::closeAll() {

	while(editorTabs->count() > 0) {
		
		closeFile(0);
	}
		
}

void MainWindow::exitApp() {

	closeAll();
	QApplication::quit();

}
