#include "Shelf.h"
#include "ShelfMapper.h"
#include <iostream>
#include <QtWidgets/QMenu>
#include <QtWidgets/QGraphicsScene>

Shelf::Shelf(QJsonObject object)
{
	const double x = object.value("X").toDouble();
	const double y = object.value("Y").toDouble() * -1;
	const int w = object.value("Width").toInt();
	const int h = object.value("Height").toInt();

	setRect(QRectF(x, y, w, h));
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
}

Shelf::Shelf(const int x, const int y)
{
	setRect(QRectF(x, y, 0, 0));
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
	jsonShelf.insert("X", sceneBoundingRect().x());
	jsonShelf.insert("Y", sceneBoundingRect().y() * -1);
	jsonShelf.insert("Width", sceneBoundingRect().width());
	jsonShelf.insert("Height", sceneBoundingRect().height());

	auto shelfJsonArray = root.value("Shelves").toArray();
	shelfJsonArray << jsonShelf;
	root.insert("Shelves", shelfJsonArray);

	return jsonShelf;
}

void Shelf::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Shelf::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
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