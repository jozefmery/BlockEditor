#pragma once

#include "ui_MainWindow.h"
#include "Scaler.h"
#include "Block.h"
#include <QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QGraphicsItem>
#include <QFileDialog>
#include <QtXml/QtXml>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);

private:
	inline void setUpChildren();

	void createNewTab(QString& path);

private:
	Ui::MainWindowClass ui;

	QTabWidget *editorTabs;

signals:
	void customContextMenuRequested(QPoint pos);

private slots:
	
	void start();
	void pause();
	void stop();

	void createNewFile();
	void openFile();

};
