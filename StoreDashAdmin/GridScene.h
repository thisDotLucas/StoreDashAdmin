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

	// Distance between grid points.
	int getGridSize() const { return m_gridsize; }

	// Point to closest gridpoint from the point passed as argument.
	QPointF toClosetGridPoint(const QPointF& point);

	// Gets the n gridpoints in given direction (see Direction enum).
	std::vector<QPointF> getNGridPointsInDirection(const QPointF& start, const int n, const Direction direction);

	// Adjust point by one gridpoint to the given direction.
	void adjustPointByDirection(QPointF& point, Direction direction);

protected:
	// Draws the grid.
	void drawBackground(QPainter* painter, const QRectF& rect);

private:
	int m_gridsize = 10;
};

