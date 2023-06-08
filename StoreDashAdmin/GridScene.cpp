#include "GridScene.h"
#include "qpainter.h"
#include "StoreDashAdmin.h"
#include "DrawingArea.h"

GridScene::GridScene(QObject* parent) : QGraphicsScene(parent)
{
}

QPointF GridScene::toClosetGridPoint(const QPointF& point)
{
	const qreal x = round(point.x() / m_gridsize) * m_gridsize;
	const qreal y = round(point.y() / m_gridsize) * m_gridsize;

	return QPointF{ x, y };
}

std::vector<QPointF> GridScene::getNGridPointsInDirection(const QPointF& start, const int n, const Direction direction)
{
	QPointF gridPoint = start;

	std::vector<QPointF> out;
	while (out.size() < n)
	{
		adjustPointByDirection(gridPoint, direction);
		out.push_back(gridPoint);
	}

	return out;
}

void GridScene::adjustPointByDirection(QPointF& point, Direction direction)
{
	// Note the QT coordinate system, Y axis is inverted.
	switch (direction)
	{
	case Direction::Up:
		point.setY(point.y() - m_gridsize);
		break;
	case Direction::Right:
		point.setX(point.x() + m_gridsize);
		break;
	case Direction::Down:
		point.setY(point.y() + m_gridsize);
		break;
	case Direction::Left:
		point.setX(point.x() - m_gridsize);
		break;
	}
}

void GridScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	// At some point displaying gridpoints does not make any sense.
	if (((StoreDashAdmin*)parent())->getView()->transform().m11() < 0.3)
		return;

	QPen pen;
	painter->setPen(pen);

	const qreal left = int(rect.left()) - (int(rect.left()) % m_gridsize);
	const qreal top = int(rect.top()) - (int(rect.top()) % m_gridsize);
	QVector<QPointF> points;
	for (qreal x = left; x < rect.right(); x += m_gridsize) {
		for (qreal y = top; y < rect.bottom(); y += m_gridsize) {
			points.append(QPointF(x, y));
		}
	}
	painter->drawPoints(points.data(), points.size());
}
