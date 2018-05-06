/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: EditorFile							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#pragma once
#include <QtCore>

class EditorFile {

public:

	EditorFile();
	EditorFile(const QString path);

public:

	inline const QString getFullPath() const { return fullPath; }
	inline const QString getDisplayPath() const { return displayPath; }
	inline void setFullPath(QString path)
	{
		fullPath = path;
		setDisplayPath();
	}

private:

	void setDisplayPath();
	
private:

	QString fullPath;
	QString displayPath;

};