#pragma once
#include <QtWidgets/QGraphicsItem>
#include "Serializable.h"
#include "Node.h"
#include <map>

class Connection : public QGraphicsLineItem, public Serializable
{
public:
	Connection(QJsonObject object, const std::map<int, Node*>& nodeMap);
	Connection(Node* start);

	// Connection starts at this node.
	void setStart(Node* start);

	// Connection ends at this node.
	void setEnd(Node* end);

	// Checks that the connection data is valid.
	bool isValid() const { return m_start && m_end; }

	// Checks if connection collides with a shelf.
	bool hasCollissions() const;

	// Get start node.
	Node* start() const { return m_start; }

	// Get end node.
	Node* end() const { return m_end; }

	// Serialize to a Json object.
	std::optional<QJsonObject> serialize(QJsonObject& root);

	// Remove from drawing.
	void remove();

	// Move the start node.
	void moveStart(const QPointF& newPoint);

	// Move the end node.
	void moveEnd(const QPointF& newPoint);

protected:
	// Handles mouse press event.
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	// Handles mouse relase event.
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
	// Creates the graphics for the connection.
	void createLine();

	Node* m_start;
	Node* m_end;
};
