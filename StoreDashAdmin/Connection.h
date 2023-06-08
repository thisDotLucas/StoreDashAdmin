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
	void setStart(Node* start);
	void setEnd(Node* end);
	bool isValid() const { return m_start && m_end; }
	bool hasCollissions() const;
	Node* start() const { return m_start; }
	Node* end() const { return m_end; }
	std::optional<QJsonObject> serialize(QJsonObject& root);
	void remove();
	void moveStart(const QPointF& newPoint);
	void moveEnd(const QPointF& newPoint);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:

	void createLine();

	Node* m_start;
	Node* m_end;
};
