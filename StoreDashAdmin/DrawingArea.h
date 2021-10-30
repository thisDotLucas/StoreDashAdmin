#pragma once

#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <optional>
#include "DrawableEntity.h"

class DrawingArea : public QGraphicsView
{
public:
	DrawingArea(QWidget* parent = 0);

	void setDrawableEntity(DrawableEntity* drawableEntity) { m_drawableEntity = drawableEntity; }

protected:
	void paintEvent(QPaintEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);

private:
	std::optional<DrawableEntity*> m_drawableEntity;
	std::unique_ptr<QGraphicsScene> m_scene;
};

