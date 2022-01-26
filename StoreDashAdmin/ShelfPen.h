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

private:
	std::optional<Shelf*> m_shelf;
};

