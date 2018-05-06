/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: MainWindow							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "MainWindow.h"
#include "BlockEditor.h"

#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>
#include <vector>
#include <algorithm>

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
	connect(ui.actionSave, &QAction::triggered, this, &MainWindow::saveCurrent);
	connect(ui.actionSave_as, &QAction::triggered, this, &MainWindow::saveAs);
	connect(ui.actionSave_all, &QAction::triggered, this, &MainWindow::saveAll);
	

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

		for (Line* line: currentView->getLines()) {
			line->setToolTip("Nothing");
		}

		computation = new Computation(currentView);
		connect(computation, SIGNAL(done()), this, SLOT(setResult()));
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

		readXML(file.getFullPath());

	} else {

		// focus on file
		editorTabs->setCurrentIndex(idx);
	}
}

void MainWindow::closeFile(const int idx) {

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

/**
 * Set result of computation to Result Block. 
 */
void MainWindow::setResult() {

	BlockEditor* currentView = dynamic_cast<BlockEditor*>(editorTabs->currentWidget());

	QTextCursor cursor(currentView->getResultBlock()->getOperationText()->document());
	cursor.setPosition(0);
	cursor.select(QTextCursor::WordUnderCursor);
	cursor.beginEditBlock();
	cursor.insertText(QString::number(currentView->getResultBlock()->getInputs()[0]->getValue()));
	cursor.endEditBlock();
	cursor.removeSelectedText();
}

void MainWindow::saveCurrent() {
	
	int idx = editorTabs->currentIndex();

	// no editor open
	if (editorTabs->currentIndex() == -1) { return; }

	save(idx, false);
}

void MainWindow::saveAs() {

	int idx = editorTabs->currentIndex();

	// no editor open
	if (editorTabs->currentIndex() == -1) { return; }

	save(idx, true);
}

void MainWindow::saveAll() {

	qDebug() << editorTabs->count();

	for(int i = 0; i < editorTabs->count(); i++) {
		
		save(i, false);
	}
}

void MainWindow::save(const int idx, bool ask) {
	
	// new file
	if(files[idx].getFullPath() == "" || ask)
	{
		auto path = QFileDialog::getSaveFileName(this, "Save as", "", "Scheme file (*.scheme);;All Files (*.*)");

		if (path == "") return;

		files[idx].setFullPath(path);
		editorTabs->setTabText(idx, files[idx].getDisplayPath());
	}

	writeXML(idx);
}

void MainWindow::writeXML(const int idx) const
{
	QString xml;

	QXmlStreamWriter writer(&xml);
	writer.setAutoFormatting(true);

	writer.writeStartDocument();
	writer.writeStartElement("scheme");

	BlockEditor* editor = dynamic_cast<BlockEditor*>(editorTabs->widget(idx));

	auto writeBlock = [&](Block *b) {

		writer.writeStartElement("block");

		writer.writeAttribute("x", QString::number(b->pos().x()));
		writer.writeAttribute("y", QString::number(b->pos().y()));

		switch (b->getBlockType())
		{
		case CONSTBLOCK:
			writer.writeAttribute("type", "const");
			writer.writeAttribute("output", b->getOutputs()[0]->getName());
			writer.writeAttribute("value", b->getOperationText()->toPlainText());
			if(b->getOutputs()[0]->getLine()) {
				
				auto id = std::find(editor->getBlocks().begin(), editor->getBlocks().end(), b->getOutputs()[0]->getLine()->getInBlock()) - editor->getBlocks().begin();
				writer.writeAttribute("out", QString::number(id));
			}
			else {
				writer.writeAttribute("out", "-1");
			}
			break;
		case BLOCK:
			writer.writeAttribute("type", "op");
			writer.writeAttribute("operation", b->getOperation());
			writer.writeAttribute("input", b->getInputs()[0]->getName());
			writer.writeAttribute("output", b->getOutputs()[0]->getName());
			
			if (b->getOutputs()[0]->getLine()) {

				auto id = std::find(editor->getBlocks().begin(), editor->getBlocks().end(), b->getOutputs()[0]->getLine()->getInBlock()) - editor->getBlocks().begin();
				writer.writeAttribute("out", QString::number(id));
			}
			else{
				writer.writeAttribute("out", "-1");
			}

			if (b->getInputs()[0]->getLine()) {

				auto id = std::find(editor->getBlocks().begin(), editor->getBlocks().end(), b->getInputs()[0]->getLine()->getOutBlock()) - editor->getBlocks().begin();
				writer.writeAttribute("in1", QString::number(id));
			}
			else {
				writer.writeAttribute("in1", "-1");
			}

			if (b->getInputs()[1]->getLine()) {

				auto id = std::find(editor->getBlocks().begin(), editor->getBlocks().end(), b->getInputs()[1]->getLine()->getOutBlock()) - editor->getBlocks().begin();
				writer.writeAttribute("in2", QString::number(id));
			}
			else {
				writer.writeAttribute("in2", "-1");
			}
			break;
		case RESULT:
			writer.writeAttribute("type", "result");
			if (b->getInputs()[0]->getLine()) {

				auto id = std::find(editor->getBlocks().begin(), editor->getBlocks().end(), b->getInputs()[0]->getLine()->getOutBlock()) - editor->getBlocks().begin();
				writer.writeAttribute("in", QString::number(id));
			}
			else {
				writer.writeAttribute("in", "-1");
			}
			break;

		}

		writer.writeEndElement(); // block

	};

	for (int i = 0; i < editor->getBlocks().size(); i++) {

		writeBlock(editor->getBlocks()[i]);
	}

	if(editor->getResultBlock()){
		writeBlock(editor->getResultBlock());
	}
	
	writer.writeEndElement(); // scheme

	writer.writeEndDocument();

	QFile file(files[idx].getFullPath());
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

		QMessageBox::critical(nullptr, "File access error", "Error accessing: " + files[idx].getFullPath() + " for writing!");
		return;
	}

	file.write(xml.toUtf8());

}

void MainWindow::readXML(const QString path) {


	QDomDocument doc;
	QFile file(path);
	BlockEditor* editor = dynamic_cast<BlockEditor*>(editorTabs->widget(editorTabs->currentIndex()));

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

		QMessageBox::critical(nullptr, "File access error", "Error accessing: " + path + " for reading!");
		return;
	}

	QString error;
	int line, column;


	if (!doc.setContent(&file, &error, &line, &column)) {

		QMessageBox::critical(nullptr, "XML read error", error);

		file.close();
		return;
	}
	file.close();

	// print out the element names of all elements that are direct children
	// of the outermost element.
	QDomElement docElem = doc.documentElement();

	if(docElem.tagName() != "scheme") {
		
		QMessageBox::critical(nullptr, "XML", "Unknown element: " + docElem.tagName());
		return;
	}

	if(docElem.attributes().length() > 0) {
		
		QMessageBox::critical(nullptr, "XML", "Invalid attributs for scheme");
		return;
	}

	QDomNode node = docElem.firstChild();
	while (!node.isNull()) {
		QDomElement elem = node.toElement(); // try to convert the node to an element.
		if (!elem.isNull()) {
			
			if(elem.tagName() != "block") {

				QMessageBox::critical(nullptr, "XML", "Unknown element: " + elem.tagName());
				return;

			}

			if(!elem.firstChild().isNull()) {
				
				QMessageBox::critical(nullptr, "XML", "Invalid child elemenet for " + elem.tagName() + ": " + elem.firstChild().toElement().tagName());
				return;

			}

			std::vector<QString> attribs = {"x", "y", "type"};

			auto map = elem.attributes();

			if(map.length() < 3) {
				QMessageBox::critical(nullptr, "XML", "Not enough attributes for block");
				return;

			}
			
			for (int i = 0; i < 3; i++) {

				if(!map.contains(attribs[i])) {
					
					QMessageBox::critical(nullptr, "XML", "Missing attribute for block: " + attribs[i]);
					return;
				}

			}

			bool ok = true;
			int x = map.namedItem("x").toAttr().value().toInt(&ok, 10);

			if (!ok) {

				QMessageBox::critical(nullptr, "XML", "Invalid value for x attribute: " + map.namedItem("x").toAttr().value());
				return;
			}

			int y = map.namedItem("y").toAttr().value().toInt(&ok, 10);

			if (!ok) {

				QMessageBox::critical(nullptr, "XML", "Invalid value for y attribute: " + map.namedItem("x").toAttr().value());
				return;
			}

			QPointF pos = editor->mapToScene(QPoint(x, y));

			QString type = map.namedItem("type").toAttr().value();


			std::vector<QString> unique_attrib;
			std::vector<QString> IOtypes = {"integer", "float", "double", "constant", "real"};

			if (type == "const") {

				unique_attrib = {"output", "value", "out"};

				if (attribs.size() + unique_attrib.size() != map.length()) {

					QMessageBox::critical(nullptr, "XML", "Invalid attributes for const block!");
					return;
				}

				for (size_t i = 0; i < unique_attrib.size(); i++) {

					if (!map.contains(unique_attrib[i])) {

						QMessageBox::critical(nullptr, "XML", "Missing attribute for const block: " + unique_attrib[i]);
						return;
					}

				}

				auto output = map.namedItem("output").toAttr().value();

				if (std::find(IOtypes.begin(), IOtypes.end(), output) == IOtypes.end()) {

					QMessageBox::critical(nullptr, "XML", "Invalid output type: " + output);
					return;

				}

				bool ok = true;
				auto value = map.namedItem("value").toAttr().value().toDouble(&ok);

				if (!ok) {

					QMessageBox::critical(nullptr, "XML", "Invalid value for value attribute: " + map.namedItem("output").toAttr().value());
					return;

				}

				Block* block = new Block(0, 0, editor, value, output);

				editor->getBlocks().push_back(block);
				editor->scene->addItem(block);
				block->setPos(pos);

			}
			else if(type == "op") {
				
				unique_attrib = { "operation", "input", "output" };

				if (attribs.size() + unique_attrib.size() != map.length()) {

					QMessageBox::critical(nullptr, "XML", "Invalid attributes for operator block!");
					return;
				}

				for (size_t i = 0; i < unique_attrib.size(); i++) {

					if (!map.contains(unique_attrib[i])) {

						QMessageBox::critical(nullptr, "XML", "Missing attribute for operator block: " + unique_attrib[i]);
						return;
					}

				}

				auto op = map.namedItem("operation").toAttr().value();
				std::vector<QString> ops = { "+", "-", "/", "*" };

				if (std::find(ops.begin(), ops.end(), op) == ops.end()) {
					
					QMessageBox::critical(nullptr, "XML", "Unknown operation: " + op);
					return;

				}

				auto input = map.namedItem("input").toAttr().value();

				if (std::find(IOtypes.begin(), IOtypes.end(), input) == IOtypes.end()) {

					QMessageBox::critical(nullptr, "XML", "Invalid input type: " + input);
					return;

				}

				auto output = map.namedItem("output").toAttr().value();

				if (std::find(IOtypes.begin(), IOtypes.end(), output) == IOtypes.end()) {

					QMessageBox::critical(nullptr, "XML", "Invalid output type: " + output);
					return;

				}

				Block* block = new Block(0, 0, editor, op, input, output);

				editor->getBlocks().push_back(block);
				editor->scene->addItem(block);
				block->setPos(pos);
			}
			else if (type == "result") {

				if(attribs.size() + unique_attrib.size() != map.length()){
					
					QMessageBox::critical(nullptr, "XML", "Invalid attributes for result block!");
					return;
				}
				
				if(editor->getResultBlock()) {
					
					QMessageBox::critical(nullptr, "XML", "Duplicate result block!");
					return;

				}
				
				Block* block = new Block(0, 0, editor);

				editor->setResultBlock(block);

				editor->scene->addItem(block);
				block->setPos(pos);

			}
			else {
				QMessageBox::critical(nullptr, "XML", "Invalid value for type attribute: " + type);
				return;
			}
		}
		node = node.nextSibling();
	}
	

}
