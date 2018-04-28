#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>

int screenWidth;
int screenHeight;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QRect rec = QApplication::desktop()->screenGeometry();

	screenWidth = rec.width();
	screenHeight = rec.height();

	MainWindow main_window;
	main_window.show();
	
	QApplication::setWindowIcon(QIcon(":/Resources/main_icon.png"));

	
	return QApplication::exec();
}
