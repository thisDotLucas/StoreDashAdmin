#include "NodePen.h"

Node* NodePen::press(const QPointF& point)
{
	m_node = new Node(point.x(), point.y(), 20.0);
	return m_node.value();
}

Node* NodePen::lift()
{
	return m_node.value();
}

Node* NodePen::move(const QPointF& point)
{
	if (m_node.has_value())
	{
		//QRectF originalRect = m_node.value()->rect();
		//QRectF rect(originalRect.x(), originalRect.y(), point.x() - originalRect.x(), point.y() - originalRect.y());
		//m_node.value()->setRect(rect.normalized());
		//m_node.value()->update();

		return m_node.value();
	}

	return nullptr;
}
