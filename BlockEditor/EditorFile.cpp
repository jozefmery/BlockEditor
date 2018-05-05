#include "EditorFile.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <cassert>

static const QString DEFAULT_NAME("new scheme");

EditorFile::EditorFile() 
	: 
	fullPath(""), 
	displayPath(DEFAULT_NAME)
{}

EditorFile::EditorFile(const QString path) 
	:
	fullPath(path)
{
	setDisplayPath();
}

void EditorFile::setDisplayPath()
{
	QRegularExpression re("(?:.*/)*(.*)\\..*");
	QRegularExpressionMatch match = re.match(fullPath);

	assert(match.hasMatch());

	displayPath = match.captured(1);
}
