#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtGui>
#include "ui_NodeType.h"
#include "Node.h"
#include <optional>


class NodeTypeSelectTool : public QDialog
{
	Q_OBJECT

public:
	NodeTypeSelectTool(Node* node, QWidget* parent = Q_NULLPTR);

private slots:
	void okButtonPressed();

private:
	Node* m_node;
	Ui::Dialog ui;
};