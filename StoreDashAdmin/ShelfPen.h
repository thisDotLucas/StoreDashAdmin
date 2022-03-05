#pragma once
#include "Pen.h"
#include "Shelf.h"
#include "qpoint.h"

class ShelfPen : public Pen
{
public:
	// While pressing mouse 1.
	Shelf* press(const QPointF& point) override;

	// While relasing mouse 1.
	Shelf* lift() override;

	// While holding down mouse 1.
	Shelf* move(const QPointF& point) override;

	// While moving the cursor without holding down mouse 1.
	void hover(QGraphicsScene* scene, const QPointF& point) override;

	// The cursorshape used for this pen.
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	std::optional<Shelf*> m_shelf;
	QPointF m_start{};
};

