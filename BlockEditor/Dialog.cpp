#include "Dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));
}

void Dialog::ok() {
	iPorts = ui.iPorts->currentText().toInt();
	oPorts = ui.oPorts->currentText().toInt();
	operation = ui.opration->currentText();

	close();
}

void Dialog::cancel() {
	close();
}
