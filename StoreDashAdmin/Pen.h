#pragma once
#include <QtWidgets/QGraphicsItem>


class Pen
{
public:
	virtual ~Pen() {}

	// While pressing mouse 1.
	virtual QGraphicsItem* press(const QPointF& point) = 0;

	// While relasing mouse 1.
	virtual QGraphicsItem* lift() = 0;

	// While holding down mouse 1.
	virtual QGraphicsItem* move(const QPointF& point) = 0;

	// While moving the cursor without holding down mouse 1.
	virtual void hover(QGraphicsScene* scene, const QPointF& point) = 0;

	// The cursorshape used for this pen.
	virtual Qt::CursorShape cursorShape() = 0;
};

