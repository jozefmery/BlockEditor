#include "DialogConst.h"

DialogConst::DialogConst(QWidget *parent)
	: QDialog(parent) {

	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));
}

void DialogConst::ok() {
	value = ui.value->text().toDouble();
	outputType = ui.output->currentText();

	close();
}

void DialogConst::cancel() {
	close();
}