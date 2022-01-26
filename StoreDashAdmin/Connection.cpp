#include "Connection.h"
#include "qjsonarray.h"
#include <QtWidgets/QGraphicsScene>

Connection::Connection(QJsonObject object, const std::map<int, Node*>& nodeMap)
{
	int fromId = object.value("From").toInt();
	int toId = object.value("To").toInt();

	setStart(std::shared_ptr<Node>(nodeMap.at(fromId)));
	setEnd(std::shared_ptr<Node>(nodeMap.at(toId)));
}

Connection::Connection(std::shared_ptr<Node> start) : m_start(start), m_end(nullptr)
{
}

void Connection::setStart(std::shared_ptr<Node> start)
{
	if (m_end != start)
	{
		m_start = start;
		if (m_end)
			setLine(m_start->origo().x(), m_start->origo().y(), m_end->origo().x(), m_end->origo().y());
	}
}

void Connection::setEnd(std::shared_ptr<Node> end)
{
	if (m_start != end)
	{
		m_end = end;
		if (m_start)
			setLine(m_start->origo().x(), m_start->origo().y(), m_end->origo().x(), m_end->origo().y());
	}
}

std::optional<QJsonObject> Connection::serialize(QJsonObject& root)
{
	QJsonObject jsonConnection;
	jsonConnection.insert("From", m_start->getId());
	jsonConnection.insert("To", m_end->getId());

	auto connectionJsonArray = root.value("Connections").toArray();
	connectionJsonArray << jsonConnection;
	root.insert("Connections", connectionJsonArray);

	return jsonConnection;
}

void Connection::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Connection::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}
