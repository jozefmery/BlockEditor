/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: Dialog								*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#include "Dialog.h"

#include <QDebug>

/**
 * Constructor of dialog.
 * @param parent widget parent
 */
Dialog::Dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.ok, SIGNAL(clicked()), SLOT(ok()));
	connect(ui.cancel, SIGNAL(clicked()), SLOT(cancel()));

	clickedOk = false;
}

/**
 * Slot for signal cliclked on OK button. Get values from widgets.
 */
void Dialog::ok() {
	inputType = ui.input->currentText();
	outputType = ui.output->currentText();
	operation = ui.opration->currentText();

	clickedOk = true;

	close();
}

/**
 * Slot for signal clicked on Cancel button. Close dialog.
 */
void Dialog::cancel() {

	clickedOk = false;

	close();
}
