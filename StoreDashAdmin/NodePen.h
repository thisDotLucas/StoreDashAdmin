#pragma once
#include "Pen.h"
#include "Node.h"
#include "qpoint.h"


class NodePen : public Pen
{
public:
	~NodePen();

	// While pressing mouse 1.
	Node* press(const QPointF& point) override;

	// While relasing mouse 1.
	Node* lift() override;

	// While holding down mouse 1.
	Node* move(const QPointF& point) override;

	// While moving the cursor without holding down mouse 1.
	void hover(QGraphicsScene* scene, const QPointF& point) override;

	// The cursorshape used for this pen.
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	// Clear navigation lines from the drawing.
	void clearNavigationLines();

	std::optional<Node*> m_node;
	std::vector<QGraphicsItem*> m_navigationLines;
	std::optional<QGraphicsScene*> m_scene;
};

