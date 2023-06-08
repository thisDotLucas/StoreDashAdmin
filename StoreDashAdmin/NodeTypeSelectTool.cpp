#include "NodeTypeSelectTool.h"

NodeTypeSelectTool::NodeTypeSelectTool(Node* node, QWidget* parent) : m_node(node)
{
	ui.setupUi(this);
	connect(ui.okButton, &QPushButton::pressed, this, &NodeTypeSelectTool::okButtonPressed);

	NodeType type = m_node->getNodeType();
	if (type == NodeType::Basic)
		ui.basicRadioButton->setChecked(true);
	else if (type == NodeType::Start)
		ui.startRadioButton->setChecked(true);
	else if (type == NodeType::Shelf)
		ui.shelfRadioButton->setChecked(true);
	else
		ui.endRadioButton->setChecked(true);
}

void NodeTypeSelectTool::okButtonPressed()
{
	if (ui.basicRadioButton->isChecked())
		m_node->setNodeType(NodeType::Basic);
	else if (ui.startRadioButton->isChecked())
		m_node->setNodeType(NodeType::Start);
	else if (ui.shelfRadioButton->isChecked())
		m_node->setNodeType(NodeType::Shelf);
	else
		m_node->setNodeType(NodeType::End);
}