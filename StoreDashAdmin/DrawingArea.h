#pragma once

#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <optional>
#include <set>
#include "DrawableEntity.h"
#include "Pen.h"
#include "Picker.h"
#include "ShelfPen.h"

enum class PenState
{
	None,
	Shelf,
	Section
};

class DrawingArea : public QGraphicsView
{
public:
	DrawingArea(QWidget* parent = 0);

	void setPen(std::shared_ptr<Pen> pen);
	void setPicker(std::shared_ptr<Picker> pen);

protected:
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	virtual void wheelEvent(QWheelEvent* event);

private:
	std::optional<std::shared_ptr<Pen>> m_pen;
	std::optional<std::shared_ptr<Picker>> m_picker;
};

