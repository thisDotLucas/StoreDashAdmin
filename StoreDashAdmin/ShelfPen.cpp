#include "ShelfPen.h"

Shelf* ShelfPen::press(const QPointF& point)
{
	m_shelf = new Shelf(point.x(), point.y());
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
		QRectF originalRect = m_shelf.value()->rect();
		QRectF rect(originalRect.x(), originalRect.y(), point.x() - originalRect.x(), point.y() - originalRect.y());
		m_shelf.value()->setRect(rect.normalized());
		m_shelf.value()->update();

		return m_shelf.value();
	}

	return nullptr;
}
