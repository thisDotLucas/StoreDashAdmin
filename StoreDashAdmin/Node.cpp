#include "Node.h"
#include "DrawingArea.h"
#include "Connection.h"
#include "NodeTypeSelectTool.h"
#include <QtWidgets/QMenu>
#include "qjsonarray.h"
#include "GridScene.h"
#include "ShelfMapper.h"
#include "StoreDashAdmin.h"
#include <QtWidgets/QGraphicsScene>

#define RGB_BASIC 105, 153, 93
#define RGB_START 173, 216, 230
#define RGB_SHELF 32, 178, 170
#define RGB_END 48, 25, 52
#define RGB_PICKED 244, 176, 123


namespace {

	const char* nodeTypeToString(const NodeType type)
	{
		switch (type)
		{
		case NodeType::Start:
			return "Start";
		case NodeType::End:
			return "End";
		case NodeType::Shelf:
			return "Shelf";
		default:
			return "Basic";
		}
	}

	NodeType stringToNodeType(const std::string& typeName)
	{
		if (typeName == "Basic")
			return NodeType::Basic;
		else if (typeName == "Start")
			return NodeType::Start;
		else if (typeName == "Shelf")
			return NodeType::Shelf;
		else
			return NodeType::End;
	}

}

Node::Node(QJsonObject object, std::map<QString, std::map<QString, std::set<QString>>>* ids)
{
	m_id = object.value("ID").toInt();

	if (m_id > runningNumber)
		runningNumber = m_id + 1;

	m_type = stringToNodeType(object.value("Type").toString().toStdString());

	if (m_type == NodeType::Shelf)
	{
		m_moduleId = object.value("ModuleID").toString().toStdString();
		m_shelfId = object.value("ShelfID").toString().toStdString();

		if (m_moduleId != "NULL" && m_shelfId != "NULL")
			ids->at(QString{ m_moduleId.value().c_str() }).erase(QString{ m_shelfId.value().c_str() });
	}

	const double x = object.value("X").toInt();
	const double y = object.value("Y").toInt() * -1.0;

	QBrush brush;
	brush.setColor(QColor(RGB_BASIC));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);

	resetColor();

	setRect(QRectF(x - (NODE_RADIUS / 2), y - (NODE_RADIUS / 2), NODE_RADIUS, NODE_RADIUS));
	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
}

Node::Node(const int x, const int y, const double radius) : m_id(runningNumber++)
{
	QBrush brush;
	brush.setColor(QColor(RGB_BASIC));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	setRect(QRectF(x - (radius / 2), y - (radius / 2), radius, radius));
	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
}

QPointF Node::getCenterOfSceneBoundingRect()
{
	QRectF boundingRect = sceneBoundingRect();
	return { boundingRect.x() + boundingRect.width() / 2 , boundingRect.y() + boundingRect.height() / 2 };
}

void Node::setPickedColor()
{
	QBrush brush;
	brush.setColor(QColor(RGB_PICKED));
	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	update();
}

void Node::resetColor()
{
	QBrush brush;

	switch (m_type)
	{
	case NodeType::Basic:
		brush.setColor(QColor(RGB_BASIC));
		break;
	case NodeType::Start:
		brush.setColor(QColor(RGB_START));
		break;
	case NodeType::Shelf:
		brush.setColor(QColor(RGB_SHELF));
		break;
	default:
		brush.setColor(QColor(RGB_END));
		break;
	}

	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	update();
}

std::optional<QJsonObject> Node::serialize(QJsonObject& root)
{
	QJsonObject jsonNode;
	jsonNode.insert("ID", m_id);
	jsonNode.insert("Type", nodeTypeToString(m_type));

	if (m_type == NodeType::Shelf)
	{
		jsonNode.insert("ModuleID", getModuleId().value_or("NULL").c_str());
		jsonNode.insert("ShelfID", getShelfId().value_or("NULL").c_str());
	}

	QRectF boundingRect = this->sceneBoundingRect();
	QPointF rectMidPoint{ boundingRect.x() + boundingRect.width() / 2 , boundingRect.y() + boundingRect.height() / 2 };

	jsonNode.insert("X", rectMidPoint.x());
	jsonNode.insert("Y", rectMidPoint.y() * -1);

	auto nodeJsonArray = root.value("Nodes").toArray();
	nodeJsonArray << jsonNode;
	root.insert("Nodes", nodeJsonArray);

	return jsonNode;
}

void Node::remove()
{
	auto copyStartFor = m_startFor;
	std::ranges::for_each(copyStartFor, &Connection::remove);
	m_startFor.clear();

	auto copyEndFor = m_endFor;
	std::ranges::for_each(copyEndFor, &Connection::remove);
	m_endFor.clear();

	this->scene()->removeItem(this);
	delete this;
}

void Node::removeConnection(Connection* connection)
{
	if (m_startFor.contains(connection))
		m_startFor.erase(connection);

	if (m_endFor.contains(connection))
		m_endFor.erase(connection);
}

void Node::setNodeType(const NodeType type)
{
	m_type = type;
	QBrush brush;

	switch (m_type)
	{
	case NodeType::Basic:
		brush.setColor(QColor(RGB_BASIC));
		break;
	case NodeType::Start:
		brush.setColor(QColor(RGB_START));
		break;
	case NodeType::Shelf:
		brush.setColor(QColor(RGB_SHELF));
		break;
	default:
		brush.setColor(QColor(RGB_END));
		break;
	}

	brush.setStyle(Qt::SolidPattern);
	setBrush(brush);
	update();

}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	update();
	QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	auto copyStartFor = m_startFor;
	std::ranges::for_each(copyStartFor, [&](Connection* c) { if (c->hasCollissions()) c->remove(); else c->show(); });

	auto copyEndFor = m_endFor;
	std::ranges::for_each(copyEndFor, [&](Connection* c) { if (c->hasCollissions()) c->remove(); else c->show(); });

	clearNavigationLines();
	update();

	QGraphicsItem::mouseReleaseEvent(event);
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	if (!hasFocus() || !isSelected())
		return;

	QMenu menu;
	menu.addAction("Delete");
	menu.addAction("Type");

	if (m_type == NodeType::Shelf)
		menu.addAction("Map");

	QAction* a = menu.exec(event->screenPos());

	if (a && a->text() == "Delete")
	{
		remove();
	}
	else if (a && a->text() == "Type")
	{
		NodeTypeSelectTool* w = new NodeTypeSelectTool(this, (QWidget*)this->scene()->parent()->parent());
		w->setWindowModality(Qt::WindowModality::ApplicationModal);
		w->show();
	}
	else if (a && a->text() == "Map")
	{
		ShelfMapper* w = new ShelfMapper(this, ((StoreDashAdmin*)this->scene()->parent())->getStaticIdMap(), ((StoreDashAdmin*)this->scene()->parent())->getIdMap(), (QWidget*)this->scene()->parent()->parent());
		w->setWindowModality(Qt::WindowModality::ApplicationModal);
		w->show();
	}
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
	auto result = QGraphicsItem::itemChange(change, value);
	auto point = value.toPointF();

	clearNavigationLines();

	if (change == ItemPositionChange && scene())
	{
		// Updates possible connections
		QPointF newMidPoint = getCenterOfSceneBoundingRect();

		std::ranges::for_each(m_startFor, [&](Connection* c) { c->moveStart(newMidPoint); });
		std::ranges::for_each(m_endFor, [&](Connection* c) { c->moveEnd(newMidPoint); });

		setNavigationLines(newMidPoint);
	}

	return scene() && change == ItemPositionChange ? ((GridScene*)scene())->toClosetGridPoint(value.toPointF()) : result;
}

void Node::keyPressEvent(QKeyEvent* e)
{
	if ((hasFocus() && isSelected()) && e->key() == Qt::Key_Delete)
		remove();
	else
		QGraphicsItem::keyPressEvent(e);
}

void Node::clearNavigationLines()
{
	for (const auto& line : m_navigationLines)
	{
		scene()->removeItem(line);
	}

	m_navigationLines.clear();
}

void Node::setNavigationLines(const QPointF& fromPoint)
{
	QPen pen;
	pen.setColor(QColor{ 255, 0, 0 });

	std::vector<std::vector<QPointF>> pointsAtDirection;
	const auto directions = { Direction::Up, Direction::Right, Direction::Down, Direction::Left };
	for (const auto direction : directions)
		pointsAtDirection.push_back(((GridScene*)scene())->getNGridPointsInDirection(fromPoint, 100, direction));

	int iDirection{ 0 };
	for (const auto& points : pointsAtDirection)
	{
		for (const auto& point : points)
		{
			auto item = scene()->itemAt(point, transform());
			auto node = dynamic_cast<Node*>(item);

			QPointF adjustedToPoint = point;
			((GridScene*)scene())->adjustPointByDirection(adjustedToPoint, *(std::begin(directions) + iDirection));

			if (node && item != this && node->getCenterOfSceneBoundingRect() == adjustedToPoint)
			{
				QPointF adjustedFromPoint = fromPoint;
				((GridScene*)scene())->adjustPointByDirection(adjustedFromPoint, *(std::begin(directions) + iDirection));
				QLineF line{ adjustedFromPoint.x(), adjustedFromPoint.y(), point.x(), point.y() };
				m_navigationLines.push_back(scene()->addLine(line, pen));
				break;
			}
			else if (dynamic_cast<Shelf*>(item))
			{
				break;
			}
		}

		iDirection++;
	}
}

