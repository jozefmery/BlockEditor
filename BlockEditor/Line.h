#pragma once

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

class Block;
class BlockEditor;

class Line : public QGraphicsLineItem {

	public:
		// attributes
		BlockEditor* parent;

		// constructors
		Line(QPointF p1, QPointF p2, BlockEditor* editor);

		// events
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
		void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

		// getters
		Block* getOutBlock() const;
		Block* getInBlock() const;

		// setters
		void setOutBlock(Block* outBlock);
		void setInBlock(Block* inBlock);

	private:
		// atributes
		Block* outBlock = nullptr;
		Block* inBlock = nullptr;

};

