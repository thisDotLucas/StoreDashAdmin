#include "ConnectionPicker.h"
#include "Node.h"
#include <algorithm>
#include <ranges>

ConnectionPicker::~ConnectionPicker()
{
	if (m_connection.has_value() && m_connection.value()->start())
		m_connection.value()->start()->resetColor();

	if (m_connection.has_value() && m_connection.value()->end())
		m_connection.value()->end()->resetColor();
}

std::optional<QGraphicsItem*> ConnectionPicker::pick(QGraphicsView* view, QPointF point)
{
	auto invalidItem = [](QGraphicsItem* item) { return !(item && dynamic_cast<Node*>(item)); };
	auto items = view->scene()->items();

	items.erase(std::remove_if(std::begin(items), std::end(items), invalidItem), std::end(items));
	auto item = std::find_if(std::begin(items), std::end(items),
		[](QGraphicsItem* item) { return item->isSelected(); });

	if (item != std::end(items))
	{
		if (!m_connection.has_value())
		{
			m_connection = new Connection(dynamic_cast<Node*>(*item));
			m_connection.value()->start()->setPickedColor();
			return std::nullopt;
		}
		else
		{
			m_connection.value()->setEnd(dynamic_cast<Node*>(*item));

			if (m_connection.value()->isValid())
			{
				m_connection.value()->start()->resetColor();
				return m_connection;
			}
			else
			{
				return std::nullopt;
			}
		}
	}

	return std::nullopt;
}
