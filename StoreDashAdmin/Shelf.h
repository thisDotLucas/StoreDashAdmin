#pragma once
#include "DrawableEntity.h"
#include "Serializable.h"
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <optional>

class Shelf : public QGraphicsRectItem, public Serializable
{
public:
	Shelf(QJsonObject object);
	Shelf(const int x, const int y);
	void remove();
	std::optional<QJsonObject> serialize(QJsonObject& root);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);
	virtual void keyPressEvent(QKeyEvent* e);
};

