#include "NodePen.h"
#include "GridScene.h"
#include "Shelf.h"

NodePen::~NodePen()
{
	clearNavigationLines();
}

Node* NodePen::press(const QPointF& point)
{
	clearNavigationLines();
	m_node = new Node(point.x(), point.y(), NODE_RADIUS);
	return m_node.value();
}

Node* NodePen::lift()
{
	auto ret = m_node.value();
	m_node = std::nullopt;

	return ret;
}

Node* NodePen::move(const QPointF& point)
{
	if (m_node.has_value())
	{
		return m_node.value();
	}

	return nullptr;
}

void NodePen::hover(QGraphicsScene* scene, const QPointF& fromPoint)
{
	m_scene = scene;

	clearNavigationLines();

	QPen pen;
	pen.setColor(QColor{ 255, 0, 0 });

	std::vector<std::vector<QPointF>> pointsAtDirection;
	const auto directions = { Direction::Up, Direction::Right, Direction::Down, Direction::Left };
	for (const auto direction : directions)
		pointsAtDirection.push_back(((GridScene*)scene)->getNGridPointsInDirection(fromPoint, 100, direction));

	int iDirection{ 0 };
	for (const auto& points : pointsAtDirection)
	{
		for (const auto& point : points)
		{
			auto item = scene->itemAt(point, QTransform());
			auto node = dynamic_cast<Node*>(item);

			QPointF adjustedToPoint = point;
			((GridScene*)scene)->adjustPointByDirection(adjustedToPoint, *(std::begin(directions) + iDirection));

			if (node && node->getCenterOfSceneBoundingRect() == adjustedToPoint)
			{
				QLineF line{ fromPoint.x(), fromPoint.y(), point.x(), point.y() };
				m_navigationLines.push_back(scene->addLine(line, pen));
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

void NodePen::clearNavigationLines()
{
	if (m_scene.has_value())
	{
		for (const auto& line : m_navigationLines)
		{
			m_scene.value()->removeItem(line);
		}

		m_navigationLines.clear();
	}
}
