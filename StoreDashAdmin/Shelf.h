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
	void setModuleId(std::string& id) { m_moduleId = id; };
	void setShelfId(std::string& id) { m_shelfId = id; };
	std::optional<std::string> getModuleId() const { return m_moduleId; };
	std::optional<std::string> getShelfId() const { return m_shelfId; };
	std::optional<QJsonObject> serialize(QJsonObject& root);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

private:
	int m_x;
	int m_y;
	double m_w;
	double m_h;
	bool m_pressed;
	std::optional<std::string> m_moduleId;
	std::optional<std::string> m_shelfId;
};

