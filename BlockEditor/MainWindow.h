#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

private:

	inline void setUpChildren();

	void start();
	void pause();
	void stop();

private:
	Ui::MainWindowClass ui;
	QAction* controlActions[3];

signals:
	void customContextMenuRequested(QPoint pos);

public slots:
	void showContextMenu(QPoint pos);
	
};
