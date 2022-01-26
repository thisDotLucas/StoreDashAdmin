#include "DrawingArea.h"
#include "Shelf.h"
#include "ShelfPen.h"
#include <iostream>

DrawingArea::DrawingArea(QWidget* parent) : QGraphicsView(parent)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void DrawingArea::setPen(std::shared_ptr<Pen> pen)
{
	m_pen = pen;
	m_picker = std::nullopt;
}

void DrawingArea::setPicker(std::shared_ptr<Picker> picker)
{
	m_picker = picker;
	m_pen = std::nullopt;
}

void DrawingArea::mousePressEvent(QMouseEvent* e)
{
	if (m_picker.has_value())
	{
		QGraphicsView::mousePressEvent(e);

		auto item = m_picker.value()->pick(this, mapToScene(e->pos()));
		if (item.has_value())
		{
			//m_items.insert(item.value());
			scene()->addItem(item.value());
			item.value()->update();
			m_picker = std::nullopt;
		}
	}
	else if (m_pen.has_value())
	{
		QPointF point = mapToScene(e->pos());
		scene()->addItem(m_pen.value()->press(point));
		QGraphicsView::mousePressEvent(e);
	}
}

void DrawingArea::mouseReleaseEvent(QMouseEvent* e)
{
	if (m_pen.has_value())
	{
		m_pen.value()->lift();
		m_pen = std::nullopt;
	}

	QGraphicsView::mouseReleaseEvent(e);
}

void DrawingArea::mouseMoveEvent(QMouseEvent* e)
{
	if (m_pen.has_value())
	{
		QPointF point = mapToScene(e->pos());
		m_pen.value()->move(point);
	}

	QGraphicsView::mouseMoveEvent(e);
}

void DrawingArea::wheelEvent(QWheelEvent* event)
{
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	constexpr double scaleFactor = 1.5;

	if (event->angleDelta().y() > 0)
	{
		scale(scaleFactor, scaleFactor);
	}
	else
	{
		scale(1 / scaleFactor, 1 / scaleFactor);
	}
}
