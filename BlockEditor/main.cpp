﻿/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: main								*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>

int screenWidth;
int screenHeight;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	MainWindow main_window;
	main_window.show();
	
	QApplication::setWindowIcon(QIcon(":/Resources/main_icon.png"));

	return QApplication::exec();
}
