#pragma once
#include <QtWidgets/QGraphicsItem>

class Pen
{
public:
	virtual ~Pen() {}
	virtual QGraphicsItem* press(const QPointF& point) = 0;
	virtual QGraphicsItem* lift() = 0;
	virtual QGraphicsItem* move(const QPointF& point) = 0;
};

