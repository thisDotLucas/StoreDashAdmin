#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtGui>
#include "ui_MapShelf.h"
#include "Node.h"
#include <optional>


class ShelfMapper : public QDialog
{
	Q_OBJECT

public:
	ShelfMapper(Node* shelfNode, std::map<QString, std::set<QString>>* ids, QWidget* parent = Q_NULLPTR);
	std::optional<std::string> getModuleId() const;
	std::optional<std::string> getShelfId() const;

private slots:
	void okButtonPressed();
	void cancelButtonPressed();
	void moduleChanged();
	void shelfChanged();

private:
	Node* m_shelfNode;
	Ui::ShelfMapperDialog ui;
	std::optional<std::string> m_selectedModuleAtStart;
	std::optional<std::string> m_selectedShelfAtStart;
	std::optional<std::string> m_selectedModule;
	std::optional<std::string> m_selectedShelf;
	std::map<QString, std::set<QString>>* m_ids;
};

