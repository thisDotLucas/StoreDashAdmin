#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsView>
#include <optional>


class Picker
{
public:
	virtual ~Picker() {}

	// Pick item under point.
	virtual std::optional<QGraphicsItem*> pick(QGraphicsView* view, QPointF point) = 0;
};

