#include "GridScene.h"
#include "qpainter.h"

GridScene::GridScene(QObject* parent) : QGraphicsScene(parent)
{
}

QPointF GridScene::getClosetGridPoint(const QPointF& point)
{
	int gridSize = m_gridsize;
	qreal x = round(point.x() / gridSize) * gridSize;
	qreal y = round(point.y() / gridSize) * gridSize;

	return QPointF{ x, y };
}

void GridScene::drawBackground(QPainter* painter, const QRectF& rect)
{
	QPen pen;
	painter->setPen(pen);

	qreal left = int(rect.left()) - (int(rect.left()) % m_gridsize);
	qreal top = int(rect.top()) - (int(rect.top()) % m_gridsize);
	QVector<QPointF> points;
	for (qreal x = left; x < rect.right(); x += m_gridsize) {
		for (qreal y = top; y < rect.bottom(); y += m_gridsize) {
			points.append(QPointF(x, y));
		}
	}
	painter->drawPoints(points.data(), points.size());
}
