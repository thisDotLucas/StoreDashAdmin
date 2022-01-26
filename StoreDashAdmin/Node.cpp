#include "Node.h"
#include "DrawingArea.h"
#include <QtWidgets/QMenu>
#include "qjsonarray.h"
#include <QtWidgets/QGraphicsScene>

Node::Node(QJsonObject object) : m_x(object.value("X").toInt()), m_y(object.value("Y").toInt()), m_radius(20.0), m_id(object.value("ID").toInt())
{
	QBrush brush;
	brush.setColor(QColor(105, 153, 93));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	setRect(QRectF(m_x - (m_radius / 2), m_y - (m_radius / 2), m_radius, m_radius));
	m_pressed = false;
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
}

Node::Node(const int x, const int y, const double radius) : m_x(x), m_y(y), m_radius(20.0), m_id(runningNumber++)
{
	QBrush brush;
	brush.setColor(QColor(105, 153, 93));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	setRect(QRectF(x - (m_radius / 2), y - (m_radius / 2), m_radius, m_radius));
	m_pressed = false;
	setFlag(ItemIsMovable);
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
	jsonNode.insert("X", rect().x());
	jsonNode.insert("Y", rect().y());

	auto nodeJsonArray = root.value("Nodes").toArray();
	nodeJsonArray << jsonNode;
	root.insert("Nodes", nodeJsonArray);

	return jsonNode;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	m_pressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	m_pressed = false;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

