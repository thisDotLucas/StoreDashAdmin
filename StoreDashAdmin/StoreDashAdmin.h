#pragma once

#include <QtWidgets/QWidget>
#include "ui_StoreDashAdmin.h"
#include "DrawingArea.h"
#include "OrganizationEditor.h"

class StoreDashAdmin : public QWidget
{
	Q_OBJECT

public:
	StoreDashAdmin(QWidget* parent = Q_NULLPTR);

private slots:
	void shelfButtonPressed();
	void organizationButtonPressed();

private:
	Ui::StoreDashAdminClass ui;
	OrganizationEditor organizationEditorWindow; //keeps the thing persistant
	std::unique_ptr<DrawingArea> m_drawingArea;
};
