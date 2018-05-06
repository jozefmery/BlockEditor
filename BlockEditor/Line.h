#pragma once

#include "Block.h"

#include <QGraphicsLineItem>
#include <QDebug>


class BlockEditor;

class Line : public QGraphicsLineItem {

	public:
		// attributes
		BlockEditor* parent;

		// constructors
		Line(QPointF p1, QPointF p2, BlockEditor* editor);

		// events
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

		// getters
		Block* getOutBlock() const;
		Block* getInBlock() const;
		Block::BlockIO* getInPort() const;
		Block::BlockIO* getOutPort() const;

		// setters
		void setOutBlock(Block* outBlock);
		void setInBlock(Block* inBlock);
		void setInPort(Block::BlockIO* input);
		void setOutPort(Block::BlockIO* output);

	private:
		// atributes
		Block* outBlock = nullptr;
		Block* inBlock = nullptr;
		Block::BlockIO* input;
		Block::BlockIO* output;

};

