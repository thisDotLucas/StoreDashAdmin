#pragma once
#include "DrawableEntity.h"
#include "Serializable.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QPainter>

static constexpr const char* CONTEXT_MENU_CONNECT_TO = "Connect to...";
static int runningNumber = 0;

class Node : public QGraphicsEllipseItem, public Serializable
{
public:
	Node(QJsonObject object);
	Node(const int x, const int y, const double radius);
	QPointF origo() const { return { m_x + 0.0, m_y + 0.0 }; }
	void setPickedColor();
	void resetColor();
	std::optional<QJsonObject> serialize(QJsonObject& root);
	int getId() const { return m_id; }

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
	int m_x;
	int m_y;
	double m_radius;
	bool m_pressed;
	int m_id;
};
