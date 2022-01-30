#include "Connection.h"
#include "qjsonarray.h"
#include <QtWidgets/QGraphicsScene>

Connection::Connection(QJsonObject object, const std::map<int, Node*>& nodeMap) : m_start(nullptr), m_end(nullptr)
{
	int fromId = object.value("From").toInt();
	int toId = object.value("To").toInt();

	setStart(nodeMap.at(fromId));
	setEnd(nodeMap.at(toId));
}

Connection::Connection(Node* start) : m_start(start), m_end(nullptr)
{
}

void Connection::setStart(Node* start)
{
	if (m_end != start)
	{
		m_start = start;
		if (m_end != nullptr)
		{
			createLine();
		}
	}
}

void Connection::setEnd(Node* end)
{
	if (m_start != end)
	{
		m_end = end;
		if (m_start != nullptr)
		{
			createLine();
		}
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

void Connection::remove()
{
	m_start->removeConnection(this);
	m_end->removeConnection(this);

	this->scene()->removeItem(this);
	delete this;
}

void Connection::moveStart(const QPointF& newPoint)
{
	QRectF endBoundingRect = m_end->sceneBoundingRect();
	QPointF endRectMidPoint{ endBoundingRect.x() + endBoundingRect.width() / 2 , endBoundingRect.y() + endBoundingRect.height() / 2 };

	setLine(newPoint.x(), newPoint.y(), endRectMidPoint.x(), endRectMidPoint.y());
}

void Connection::moveEnd(const QPointF& newPoint)
{
	QRectF startBoundingRect = m_start->sceneBoundingRect();
	QPointF startRectMidPoint{ startBoundingRect.x() + startBoundingRect.width() / 2 , startBoundingRect.y() + startBoundingRect.height() / 2 };

	setLine(startRectMidPoint.x(), startRectMidPoint.y(), newPoint.x(), newPoint.y());
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

void Connection::createLine()
{
	if (m_start && m_end)
	{
		QRectF startBoundingRect = m_start->sceneBoundingRect();
		QPointF startRectMidPoint{ startBoundingRect.x() + startBoundingRect.width() / 2 , startBoundingRect.y() + startBoundingRect.height() / 2 };

		QRectF endBoundingRect = m_end->sceneBoundingRect();
		QPointF endRectMidPoint{ endBoundingRect.x() + endBoundingRect.width() / 2 , endBoundingRect.y() + endBoundingRect.height() / 2 };

		setLine(startRectMidPoint.x(), startRectMidPoint.y(), endRectMidPoint.x(), endRectMidPoint.y());

		m_start->isStartFor(this);
		m_end->isEndFor(this);
	}
}
