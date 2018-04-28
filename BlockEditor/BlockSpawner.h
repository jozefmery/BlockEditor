#pragma once

#include "Block.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class BlockSpawner : public QObject, public QGraphicsRectItem {

	Q_OBJECT

	public:
		// constructors
		BlockSpawner();

		// events
		void mousePressEvent(QGraphicsSceneMouseEvent* event);
		void mouseHoverEvent(QGraphicsSceneHoverEvent* event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

		// methods
		inline void addBlock(Block* block) { blocks.append(block); };

		// getters
		inline int getBlockOrder() { return blockOrder++; };
		inline QVector<Block*> getBlocks() { return blocks; };
		//setters
		inline int setBlockOrder(int const blockOrder) { this->blockOrder = blockOrder; };

	private:
		// attributes
		int blockOrder;
		QVector<Block*> blocks;

	signals:
		void clicked();

};