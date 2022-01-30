#pragma once
#include "DrawableEntity.h"
#include "Serializable.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <set>

static constexpr const char* CONTEXT_MENU_CONNECT_TO = "Connect to...";
static int runningNumber = 0;

class Connection;

class Node : public QGraphicsEllipseItem, public Serializable
{
public:
	Node(QJsonObject object);
	Node(const int x, const int y, const double radius);
	void setPickedColor();
	void resetColor();
	std::optional<QJsonObject> serialize(QJsonObject& root);
	int getId() const { return m_id; }
	void remove();
	void isStartFor(Connection* connection) { m_startFor.insert(connection); };
	void isEndFor(Connection* connection) { m_endFor.insert(connection); };
	void removeConnection(Connection* connection);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
	int m_id;
	std::set<Connection*> m_startFor;
	std::set<Connection*> m_endFor;
};
