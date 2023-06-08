#pragma once

#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <optional>
#include <set>
#include "Pen.h"
#include "Picker.h"
#include "ShelfPen.h"


enum class PenState
{
	None,
	Shelf,
	Section
};

class DrawingArea : public QGraphicsView
{
public:
	DrawingArea(QWidget* parent = 0);

	void setPen(std::shared_ptr<Pen> pen);
	void setPicker(std::shared_ptr<Picker> pen);

	// Gets the closest grid point from the point passed as argument.
	QPointF getClosestGridPoint(const QPointF& point);

	// Destroy current pen or picker.
	void clearPenAndPicker();

protected:
	// Handles mouse press event.
	void mousePressEvent(QMouseEvent* e);

	// Handles mouse relase event.
	void mouseReleaseEvent(QMouseEvent* e);

	// Handles mouse move event.
	void mouseMoveEvent(QMouseEvent* e);

	// Handles key press event.
	virtual void keyPressEvent(QKeyEvent* e);

	// Handles scroll wheel event.
	virtual void wheelEvent(QWheelEvent* event);

private:
	// Updates cursor according to the current state.
	void updateCursor();

	std::optional<std::shared_ptr<Pen>> m_pen;
	std::optional<std::shared_ptr<Picker>> m_picker;

	// start position for pan
	QPointF m_startPos;
};

