#pragma once
#include "Serializable.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <set>

static constexpr const char* CONTEXT_MENU_CONNECT_TO = "Connect to...";
static int runningNumber = 0;
static constexpr double NODE_RADIUS = 20.0;

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
	Node(QJsonObject object, std::map<QString, std::map<QString, std::set<QString>>>* ids);
	Node(const int x, const int y, const double radius);

	// Center of the nodes bounding rectangle.
	QPointF getCenterOfSceneBoundingRect();

	// Set color to picked state.
	void setPickedColor();

	// Set color according to state.
	void resetColor();

	// Serialize to Json object.
	std::optional<QJsonObject> serialize(QJsonObject& root);

	int getId() const { return m_id; }

	// Remove from drawing.
	void remove();

	// Update internal datastructures that keeps track of which connections this node is involved with.
	void isStartFor(Connection* connection) { m_startFor.insert(connection); };
	void isEndFor(Connection* connection) { m_endFor.insert(connection); };
	void removeConnection(Connection* connection);

	void setNodeType(const NodeType type);
	NodeType getNodeType() const { return m_type; };

	// Clear navigation lines from drawing.
	void clearNavigationLines();

	// Draw navigation lines to drawing.
	void setNavigationLines(const QPointF& fromPoint);

	void setModuleId(const std::string& id) { m_moduleId = id; };
	void setShelfId(const std::string& id) { m_shelfId = id; };
	std::optional<std::string> getModuleId() const { return m_moduleId; };
	std::optional<std::string> getShelfId() const { return m_shelfId; };

protected:
	// Handles mouse press event.
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	// Handles mouse relase event.
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	// Handles context menu event.
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

	// On changes in the state in QTGraphicsItem. 
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);

	// Handles key press event.
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
