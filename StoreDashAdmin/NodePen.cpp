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
		return m_node.value();
	}

	return nullptr;
}
