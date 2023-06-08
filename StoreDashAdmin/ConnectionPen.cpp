#include "ConnectionPen.h"


Connection* ConnectionPen::press(const QPointF& point)
{
	return m_connection.value();
}

Connection* ConnectionPen::lift()
{
	return m_connection.value();
}

Connection* ConnectionPen::move(const QPointF& point)
{
	if (m_connection.has_value())
	{
		m_connection.value()->setLine(0, 0, point.x() - m_connection.value()->x(), point.y() - m_connection.value()->y());
		m_connection.value()->update();

		return m_connection.value();
	}

	return nullptr;
}
