#pragma once
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsScene>

enum class Direction
{
	Up,
	Right,
	Down,
	Left
};

class GridScene : public QGraphicsScene
{
public:
	GridScene(QObject* parent = 0);
	int getGridSize() const { return m_gridsize; }
	QPointF toClosetGridPoint(const QPointF& point);
	std::vector<QPointF> getNGridPointsInDirection(const QPointF& start, const int n, const Direction direction);
	void adjustPointByDirection(QPointF& point, Direction direction);

protected:
	void drawBackground(QPainter* painter, const QRectF& rect);

private:
	int m_gridsize = 10;
};

