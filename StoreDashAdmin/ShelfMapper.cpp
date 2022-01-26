#include "ShelfMapper.h"

ShelfMapper::ShelfMapper(Shelf* shelf, QWidget* parent) : m_shelf(shelf)
{
	ui.setupUi(this);
	connect(ui.okButton, &QPushButton::pressed, this, &ShelfMapper::okButtonPressed);

	if (m_shelf->getModuleId().has_value())
		ui.textEdit->setText(QString(m_shelf->getModuleId().value().c_str()));

	if (m_shelf->getShelfId().has_value())
		ui.textEdit_2->setText(QString(m_shelf->getShelfId().value().c_str()));
}

void ShelfMapper::okButtonPressed()
{
	auto moduleId = getModuleId();
	if (moduleId.has_value())
		m_shelf->setModuleId(moduleId.value());

	auto shelfId = getShelfId();
	if (shelfId.has_value())
		m_shelf->setShelfId(shelfId.value());
}

std::optional<std::string> ShelfMapper::getModuleId() const
{
	if (ui.textEdit->toPlainText().isEmpty())
		return std::nullopt;

	return ui.textEdit->toPlainText().toStdString();
}

std::optional<std::string> ShelfMapper::getShelfId() const
{
	if (ui.textEdit_2->toPlainText().isEmpty())
		return std::nullopt;

	return ui.textEdit_2->toPlainText().toStdString();
}
