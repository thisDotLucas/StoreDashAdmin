#include "Node.h"
#include "DrawingArea.h"
#include "Connection.h"
#include <QtWidgets/QMenu>
#include "qjsonarray.h"
#include <QtWidgets/QGraphicsScene>

Node::Node(QJsonObject object)
{
	m_id = object.value("ID").toInt();

	const double x = object.value("X").toInt();
	const double y = object.value("Y").toInt() * -1;
	constexpr double radius = 20.0;

	QBrush brush;
	brush.setColor(QColor(105, 153, 93));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	setRect(QRectF(x - (radius / 2), y - (radius / 2), radius, radius));
	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemIsSelectable);
}

Node::Node(const int x, const int y, const double radius) : m_id(runningNumber++)
{
	QBrush brush;
	brush.setColor(QColor(105, 153, 93));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	setRect(QRectF(x - (radius / 2), y - (radius / 2), radius, radius));
	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemIsSelectable);
}

void Node::setPickedColor()
{
	QBrush brush;
	brush.setColor(QColor(244, 176, 123));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	update();
}

void Node::resetColor()
{
	QBrush brush;
	brush.setColor(QColor(105, 153, 93));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	update();
}

std::optional<QJsonObject> Node::serialize(QJsonObject& root)
{
	QJsonObject jsonNode;
	jsonNode.insert("ID", m_id);

	QRectF boundingRect = this->sceneBoundingRect();
	QPointF rectMidPoint{ boundingRect.x() + boundingRect.width() / 2 , boundingRect.y() + boundingRect.height() / 2 };

	jsonNode.insert("X", rectMidPoint.x());
	jsonNode.insert("Y", rectMidPoint.y() * -1);

	auto nodeJsonArray = root.value("Nodes").toArray();
	nodeJsonArray << jsonNode;
	root.insert("Nodes", nodeJsonArray);

	return jsonNode;
}

void Node::remove()
{
	auto copyStartFor = m_startFor;
	std::ranges::for_each(copyStartFor, &Connection::remove);
	m_startFor.clear();

	auto copyEndFor = m_endFor;
	std::ranges::for_each(copyEndFor, &Connection::remove);
	m_endFor.clear();

	this->scene()->removeItem(this);
	delete this;
}

void Node::removeConnection(Connection* connection)
{
	if (m_startFor.contains(connection))
		m_startFor.erase(connection);

	if (m_endFor.contains(connection))
		m_endFor.erase(connection);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	QMenu menu;
	menu.addAction("Delete");

	QAction* a = menu.exec(event->screenPos());

	if (a && a->text() == "Delete")
	{
		remove();
	}
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
	auto result = QGraphicsItem::itemChange(change, value);

	if (change == ItemPositionChange && scene())
	{
		QRectF boundingRect = sceneBoundingRect();
		QPointF newMidPoint{ boundingRect.x() + boundingRect.width() / 2 , boundingRect.y() + boundingRect.height() / 2 };

		std::ranges::for_each(m_startFor, [&](Connection* c) { c->moveStart(newMidPoint); });
		std::ranges::for_each(m_endFor, [&](Connection* c) { c->moveEnd(newMidPoint); });
	}

	return result;
}

