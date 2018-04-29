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

	private:

	signals:
		void clicked();

};