#pragma once
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsScene>

class GridScene : public QGraphicsScene
{
public:
	GridScene(QObject* parent = 0);
	int getGridSize() const { return m_gridsize; }
	QPointF getClosetGridPoint(const QPointF& point);

protected:
	void drawBackground(QPainter* painter, const QRectF& rect);

private:
	int m_gridsize = 10;
};

