#pragma once
#include "Pen.h"
#include "Shelf.h"
#include "qpoint.h"

class ShelfPen : public Pen
{
public:
	Shelf* press(const QPointF& point) override;
	Shelf* lift() override;
	Shelf* move(const QPointF& point) override;
	void hover(QGraphicsScene* scene, const QPointF& point) override;
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	std::optional<Shelf*> m_shelf;
	QPointF m_start{};
};

