#pragma once
#include "DrawableEntity.h"
#include "Serializable.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <set>

static constexpr const char* CONTEXT_MENU_CONNECT_TO = "Connect to...";
static int runningNumber = 0;

enum class NodeType
{
	Basic,
	Start,
	End,
	Shelf
};

class Connection;

class Node : public QGraphicsEllipseItem, public Serializable
{
public:
	Node(QJsonObject object, std::map<QString, std::set<QString>>* ids);
	Node(const int x, const int y, const double radius);
	QPointF getCenterOfSceneBoundingRect();
	void setPickedColor();
	void resetColor();
	std::optional<QJsonObject> serialize(QJsonObject& root);
	int getId() const { return m_id; }
	void remove();
	void isStartFor(Connection* connection) { m_startFor.insert(connection); };
	void isEndFor(Connection* connection) { m_endFor.insert(connection); };
	void removeConnection(Connection* connection);
	void setNodeType(const NodeType type);
	NodeType getNodeType() const { return m_type; };
	void clearNavigationLines();
	void setNavigationLines(const QPointF& fromPoint);
	void setModuleId(std::string& id) { m_moduleId = id; };
	void setShelfId(std::string& id) { m_shelfId = id; };
	std::optional<std::string> getModuleId() const { return m_moduleId; };
	std::optional<std::string> getShelfId() const { return m_shelfId; };

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);
	virtual void keyPressEvent(QKeyEvent* e);

private:
	int m_id;
	std::set<Connection*> m_startFor;
	std::set<Connection*> m_endFor;
	std::vector<QGraphicsItem*> m_navigationLines;
	NodeType m_type{ NodeType::Basic };
	std::optional<std::string> m_moduleId;
	std::optional<std::string> m_shelfId;
};
