#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtGui>
#include "ui_MapShelf.h"
#include "Shelf.h"
#include <optional>


class ShelfMapper : public QDialog
{
	Q_OBJECT

public:
	ShelfMapper(Shelf* shelf, std::map<QString, std::vector<QString>> ids, QWidget* parent = Q_NULLPTR);
	std::optional<std::string> getModuleId() const;
	std::optional<std::string> getShelfId() const;

private slots:
	void okButtonPressed();
	void cancelButtonPressed();
	void moduleChanged();
	void shelfChanged();

private:
	Shelf* m_shelf;
	Ui::ShelfMapperDialog ui;
	std::optional<std::string> m_selectedModule;
	std::optional<std::string> m_selectedShelf;
	std::map<QString, std::vector<QString>> m_ids;
};

