#pragma once

#include <QtWidgets/QWidget>
#include "ui_StoreDashAdmin.h"
#include "DrawingArea.h"

class StoreDashAdmin : public QWidget
{
	Q_OBJECT

public:
	StoreDashAdmin(QWidget* parent = Q_NULLPTR);

private slots:
	void shelfButtonPressed();

private:
	Ui::StoreDashAdminClass ui;
	std::unique_ptr<DrawingArea> m_drawingArea;
};
