#include "DrawingArea.h"
#include <iostream>

DrawingArea::DrawingArea(QWidget* parent) : QGraphicsView(parent)
{
	m_scene = std::make_unique<QGraphicsScene>();
	this->setScene(m_scene.get());
}

void DrawingArea::paintEvent(QPaintEvent* e)
{
}

void DrawingArea::mousePressEvent(QMouseEvent* e)
{
}

void DrawingArea::mouseReleaseEvent(QMouseEvent* e)
{
}

void DrawingArea::mouseMoveEvent(QMouseEvent* e)
{
}
