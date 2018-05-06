/************************************************/
/* 	BlockEditor ICP 2018						*/
/*	Part: Computation							*/
/*	Authors:									*/
/*		Denis Dovičic		xdovic01			*/
/*		Jozef Méry			xmeryj00			*/
/************************************************/

#pragma once
#include "BlockEditor.h"

#include <QThread>

#define ADD	'+';
#define SUB	'-';
#define MUL '*';
#define DIV '/';

class Computation : public QThread {

	Q_OBJECT

	public:
		// constructors
		Computation(BlockEditor* currentView);

		// methods
		void run();

		// getters
		BlockEditor* getCurrentView() const;

		// setters
		void setCurrentView(BlockEditor* currentView);

	private:
		// attributes
		BlockEditor* currentView;
		Block* actualBlock;
		bool result;

		// methods
		void compute();
		void getValue();
		int getOperation();
		void add();
		void sub();
		void mul();
		void div();

	signals:
		void done();

};

