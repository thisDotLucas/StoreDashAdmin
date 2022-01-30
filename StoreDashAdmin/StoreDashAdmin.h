#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsScene>
#include <QtGui>
#include "ui_StoreDashAdmin.h"
#include "DrawingArea.h"

class StoreDashAdmin : public QWidget
{
	Q_OBJECT

public:
	StoreDashAdmin(QWidget* parent = Q_NULLPTR);
	void setCursorLabel(const QPointF& point);

private slots:
	void shelfButtonPressed();
	void nodeButtonPressed();
	void connectionButtonPressed();
	void saveButtonPressed();
	void loadButtonPressed();

private:
	Ui::StoreDashAdminClass ui;
};