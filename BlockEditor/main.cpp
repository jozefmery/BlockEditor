#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);


	MainWindow main_window;
	main_window.show();
	
	QApplication::setWindowIcon(QIcon(":/Resources/main_icon.png"));

	
	return QApplication::exec();
}
