#include "Shelf.h"
#include "ShelfMapper.h"
#include <iostream>
#include <QtWidgets/QMenu>
#include <QtWidgets/QGraphicsScene>

Shelf::Shelf(QJsonObject object)
{
	m_pressed = false;
	m_x = object.value("X").toInt();
	m_y = object.value("Y").toInt();
	m_w = object.value("Width").toInt();
	m_h = object.value("Height").toInt();

	setRect(QRectF(m_x, m_y, m_w, m_h));
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
}

Shelf::Shelf(const int x, const int y) : m_x(x), m_y(y), m_w(10), m_h(10)
{
	setRect(QRectF(x, y, 0, 0));
	m_pressed = false;
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
}

void Shelf::remove()
{
	this->scene()->removeItem(this);
	delete this;
}

std::optional<QJsonObject> Shelf::serialize(QJsonObject& root)
{
	QJsonObject jsonShelf;
	jsonShelf.insert("ModuleID", getModuleId().value_or("NULL").c_str());
	jsonShelf.insert("ShelfID", getShelfId().value_or("NULL").c_str());
	jsonShelf.insert("X", rect().x());
	jsonShelf.insert("Y", rect().y());
	jsonShelf.insert("Width", rect().width());
	jsonShelf.insert("Height", rect().height());

	auto shelfJsonArray = root.value("Shelves").toArray();
	shelfJsonArray << jsonShelf;
	root.insert("Shelves", shelfJsonArray);

	return jsonShelf;
}

void Shelf::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	m_pressed = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Shelf::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	m_pressed = false;
	update();
	QGraphicsItem::mouseReleaseEvent(event);
}

void Shelf::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	QMenu menu;
	menu.addAction("Delete");
	menu.addAction("Map");
	QAction* a = menu.exec(event->screenPos());

	if (a && a->text() == "Delete")
	{
		remove();
	}
	else if (a && a->text() == "Map")
	{
		ShelfMapper* w = new ShelfMapper(this, (QWidget*)this->scene()->parent()->parent());
		w->setWindowModality(Qt::WindowModality::ApplicationModal);
		w->show();
	}
}