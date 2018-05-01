#pragma once

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>

class Line : public QGraphicsLineItem {

	public:
		// constructors
		Line(QPointF p1, QPointF p2);

		// events
		void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
		void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
		void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

};

