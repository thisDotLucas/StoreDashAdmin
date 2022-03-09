#include "Shelf.h"
#include "ShelfMapper.h"
#include "GridScene.h"
#include "StoreDashAdmin.h"
#include "DrawingArea.h"
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
	setRotation(object.value("Rotation").toInt());
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
}

Shelf::Shelf(const int x, const int y)
{
	setRect(QRectF(x, y, 0, 0));
	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
}

void Shelf::remove()
{
	this->scene()->removeItem(this);
	delete this;
}

std::optional<QJsonObject> Shelf::serialize(QJsonObject& root)
{
	QJsonObject jsonShelf;
	jsonShelf.insert("X", rect().x() + pos().x());
	jsonShelf.insert("Y", (rect().y() + pos().y()) * -1);
	jsonShelf.insert("Width", (int)rect().width());
	jsonShelf.insert("Height", (int)rect().height());
	jsonShelf.insert("Rotation", (int)rotation());

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

	if (!hasFocus() || !isSelected())
		return;

	QMenu menu;
	menu.addAction("Delete");

	QAction* a = menu.exec(event->screenPos());

	if (a && a->text() == "Delete")
	{
		remove();
	}
}

QVariant Shelf::itemChange(GraphicsItemChange change, const QVariant& value)
{
	auto result = QGraphicsItem::itemChange(change, value);

	return scene() && change == ItemPositionChange ? ((GridScene*)scene())->toClosetGridPoint(value.toPointF()) : result;
}

void Shelf::keyPressEvent(QKeyEvent* e)
{
	if ((hasFocus() && isSelected()) && e->key() == Qt::Key_Delete)
		remove();
	else if ((hasFocus() && isSelected()) && e->key() == Qt::Key_D)
	{
		setRotation(rotation() + 1.0);
	}
	else if ((hasFocus() && isSelected()) && e->key() == Qt::Key_A)
	{
		setRotation(rotation() - 1.0);
	}
	else
		QGraphicsItem::keyPressEvent(e);
}
