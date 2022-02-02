#include "ShelfPen.h"

Shelf* ShelfPen::press(const QPointF& point)
{
	m_shelf = new Shelf(point.x(), point.y());
	m_start = point;
	return m_shelf.value();
}

Shelf* ShelfPen::lift()
{
	return m_shelf.value();
}

Shelf* ShelfPen::move(const QPointF& point)
{
	if (m_shelf.has_value())
	{
		QRectF rect(m_start.x(), m_start.y(), point.x() - m_start.x(), point.y() - m_start.y());
		m_shelf.value()->setRect(rect.normalized());
		m_shelf.value()->update();

		return m_shelf.value();
	}

	return nullptr;
}
