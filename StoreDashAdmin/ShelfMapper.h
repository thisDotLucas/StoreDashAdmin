#pragma once
#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtGui>
#include "ui_MapShelf.h"
#include "DrawingArea.h"
#include "Shelf.h"
#include <optional>


class ShelfMapper : public QDialog
{
	Q_OBJECT

public:
	ShelfMapper(Shelf* shelf, QWidget* parent = Q_NULLPTR);
	std::optional<std::string> getModuleId() const;
	std::optional<std::string> getShelfId() const;

private slots:
	void okButtonPressed();

private:
	Shelf* m_shelf;
	Ui::Dialog ui;
};

