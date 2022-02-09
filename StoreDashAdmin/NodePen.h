#pragma once
#include "Pen.h"
#include "Node.h"
#include "qpoint.h"

class NodePen : public Pen
{
public:
	Node* press(const QPointF& point) override;
	Node* lift() override;
	Node* move(const QPointF& point) override;
	void hover(QGraphicsScene* scene, const QPointF& point) override;
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	void clearNavigationLines();
	std::optional<Node*> m_node;
	std::vector<QGraphicsItem*> m_navigationLines;
	std::optional<QGraphicsScene*> m_scene;
};

