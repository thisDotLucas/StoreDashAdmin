#include "DrawingArea.h"
#include "Shelf.h"
#include "ShelfPen.h"
#include "Connection.h"
#include "StoreDashAdmin.h"
#include "GridScene.h"
#include "ConnectionPicker.h"
#include <iostream>

DrawingArea::DrawingArea(QWidget* parent) : QGraphicsView(parent)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setSceneRect(QRect{ 0, 0, width(), height() });
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setDragMode(QGraphicsView::NoDrag);
	setMouseTracking(true);
}

void DrawingArea::setPen(std::shared_ptr<Pen> pen)
{
	m_pen = pen;
	m_picker = std::nullopt;
}

void DrawingArea::setPicker(std::shared_ptr<Picker> picker)
{
	m_picker = picker;
	m_pen = std::nullopt;
}

void DrawingArea::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Escape)
	{
		clearPenAndPicker();
	}

	QGraphicsView::keyPressEvent(e);
}

void DrawingArea::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton && e->modifiers().testFlag(Qt::ControlModifier))
	{
		m_startPos = mapToScene(e->pos());
		e->accept();
		setCursor(Qt::ClosedHandCursor);
	}
	else
	{
		QGraphicsView::mousePressEvent(e);

		if (m_picker.has_value())
		{
			auto item = m_picker.value()->pick(this, mapToScene(e->pos()));
			if (item.has_value())
			{
				scene()->addItem(item.value());

				if (dynamic_cast<Connection*>(item.value()) && ((Connection*)item.value())->hasCollissions())
					((Connection*)item.value())->remove();
				else
					item.value()->update();

				setPicker(std::make_shared<ConnectionPicker>());
			}
		}
		else if (m_pen.has_value())
		{
			const QPointF point = mapToScene(e->pos());
			scene()->addItem(m_pen.value()->press(getClosestGridPoint(point)));
		}
	}
}

void DrawingArea::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton && e->modifiers().testFlag(Qt::ControlModifier))
	{
		unsetCursor();
	}
	else
	{
		if (m_pen.has_value())
		{
			m_pen.value()->lift();
		}

		QGraphicsView::mouseReleaseEvent(e);
	}

	updateCursor();
}

void DrawingArea::mouseMoveEvent(QMouseEvent* e)
{
	QPointF point = mapToScene(e->pos());

	if (e->buttons() & Qt::LeftButton && e->modifiers().testFlag(Qt::ControlModifier))
	{
		const QPointF delta = mapToScene(e->pos()) - m_startPos;

		QRectF sceneR = sceneRect();
		sceneR.translate(-1 * delta.x(), -1 * delta.y());
		setSceneRect(sceneR);

		m_startPos = mapToScene(e->pos());

		update();
		e->accept();
		return;
	}

	((StoreDashAdmin*)this->window())->setCursorLabel(point);

	if (m_pen.has_value())
	{
		auto r = m_pen.value()->move(getClosestGridPoint(point));
		if (r == nullptr)
			m_pen.value()->hover(scene(), getClosestGridPoint(point));
	}

	updateCursor();

	QGraphicsView::mouseMoveEvent(e);
}

void DrawingArea::wheelEvent(QWheelEvent* event)
{
	const QPointF pos = mapToScene(event->position().toPoint());

	// scale from wheel angle
	const float delta = 1.0f + event->angleDelta().y() / 1000.0f;

	QRectF sceneR = sceneRect();
	if (delta < 1.f || transform().m11() < 17.0 /* Max zoom */)
	{
		sceneR.translate((pos - sceneR.center()));
		setSceneRect(sceneR);

		cursor().setPos(mapToGlobal(mapFromScene(pos.toPoint())));

		scale(delta, delta);
	}

	update();
	event->accept();
}

void DrawingArea::updateCursor()
{
	if (m_pen.has_value() && cursor().shape() != m_pen.value()->cursorShape())
		setCursor(m_pen.value()->cursorShape());
	else if (m_picker.has_value() && cursor().shape() != Qt::CrossCursor)
		setCursor(Qt::CrossCursor);
	else if (!(m_pen.has_value() || m_picker.has_value()) && cursor().shape() != Qt::ArrowCursor)
		setCursor(Qt::ArrowCursor);
}

QPointF DrawingArea::getClosestGridPoint(const QPointF& point)
{
	GridScene* gridScene = dynamic_cast<GridScene*> (scene());
	int gridSize = gridScene->getGridSize();
	qreal x = round(point.x() / gridSize) * gridSize;
	qreal y = round(point.y() / gridSize) * gridSize;

	return QPointF{ x, y };
}

void DrawingArea::clearPenAndPicker()
{
	m_pen = std::nullopt;
	m_picker = std::nullopt;
	updateCursor();
}
