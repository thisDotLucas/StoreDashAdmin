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

private:
	std::optional<Node*> m_node;
};

