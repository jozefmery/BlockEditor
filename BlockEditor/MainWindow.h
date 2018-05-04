#pragma once

#include "EditorFile.h"
#include "Computation.h"
#include "ui_MainWindow.h"

#include <QTabWidget>
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <vector>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(QWidget *parent = nullptr);

	private:
		inline void setUpChildren();

		void createNewTab(const QString& name);
		int getFileIndex(const QString fullPath);
		void openFile(const QString path, const bool addToRecent);

		Ui::MainWindowClass ui;
		QTabWidget *editorTabs;
		std::vector<EditorFile> files;

	signals:
		void customContextMenuRequested(QPoint pos);

	private slots:
		void start();
		void pause();
		void stop();

		void createNewFile();
		void showAbout();
		void clearHistory();
		void openFileBrowse();
		void closeFile(int idx);
		void closeCurrent();
		void closeAll();
		void exitApp();
};
