#pragma once
#include <QtCore>

class EditorFile {

public:

	EditorFile();
	EditorFile(const QString path);

public:

	inline const QString getFullPath() const { return fullPath; }
	inline const QString getDisplayPath() const { return displayPath; }
	inline const bool hasChanged() const { return changed; }

	inline void setChanged(const bool val) { changed = val; }

private:

	void setDisplayPath();
	
private:

	QString fullPath;
	QString displayPath;
	bool changed;

};