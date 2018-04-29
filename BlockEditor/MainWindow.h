#pragma once

#include "ui_MainWindow.h"
#include "Scaler.h"
#include "Block.h"
#include <QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QGraphicsItem>

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

	Ui::MainWindowClass ui;

	QTabWidget *editorTabs;

signals:
	void customContextMenuRequested(QPoint pos);
};
