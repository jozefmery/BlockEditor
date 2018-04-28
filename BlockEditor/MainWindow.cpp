#include "MainWindow.h"
#include "BlockEditor.h"

BlockEditor* blockEditor;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	blockEditor = new BlockEditor;
	setCentralWidget(blockEditor);
	
}
