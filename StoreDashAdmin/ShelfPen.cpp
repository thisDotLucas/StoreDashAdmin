#include "ShelfPen.h"
#include "Connection.h"
#include "Node.h"


Shelf* ShelfPen::press(const QPointF& point)
{
	m_shelf = new Shelf(point.x(), point.y());
	m_start = point;
	return m_shelf.value();
}

Shelf* ShelfPen::lift()
{
	if (!m_shelf.has_value())
		return nullptr;

	auto items = m_shelf.value()->collidingItems();
	for (const auto& item : items)
	{
		if (dynamic_cast<Connection*>(item))
		{
			((Connection*)item)->remove();
		}
		else if (dynamic_cast<Node*>(item))
		{
			((Node*)item)->remove();
		}
	}

	auto ret = m_shelf.value();
	m_shelf = std::nullopt;

	return ret;
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

void ShelfPen::hover(QGraphicsScene* scene, const QPointF& point)
{
	return;
}
