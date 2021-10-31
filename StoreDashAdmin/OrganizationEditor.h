#pragma once

#include <QtWidgets/QWidget>
#include "ui_OrganizationEditor.h"
#include "OrganizationEditor.h"

class OrganizationEditor : public QWidget
{
	Q_OBJECT

public:
	OrganizationEditor(QWidget* parent = Q_NULLPTR);

private slots:
	//TBA

private:
	Ui::OrganizationEditorClass ui;
};
