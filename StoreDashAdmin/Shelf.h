#pragma once
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

	// Remove from drawing.
	void remove();

	// Serialize to Json object.
	std::optional<QJsonObject> serialize(QJsonObject& root);

protected:
	// Handles mouse press event.
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

	// Handles mouse release event.
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	// Handles context menu event.
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

	// On changes in the state in QTGraphicsItem. 
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);

	// Handles key press event.
	virtual void keyPressEvent(QKeyEvent* e);
};

