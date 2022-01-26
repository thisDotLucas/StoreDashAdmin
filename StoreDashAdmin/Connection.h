#pragma once
#include <QtWidgets/QGraphicsItem>
#include "Serializable.h"
#include "Node.h"
#include <map>

class Connection : public QGraphicsLineItem, public Serializable
{
public:
	Connection(QJsonObject object, const std::map<int, Node*>& nodeMap);
	Connection(std::shared_ptr<Node> start);
	void setStart(std::shared_ptr<Node> start);
	void setEnd(std::shared_ptr<Node> end);
	bool isValid() const { return m_start && m_end; }
	std::shared_ptr<Node> start() const { return m_start; }
	std::shared_ptr<Node> end() const { return m_end; }
	std::optional<QJsonObject> serialize(QJsonObject& root);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
	std::shared_ptr<Node> m_start;
	std::shared_ptr<Node> m_end;
};

