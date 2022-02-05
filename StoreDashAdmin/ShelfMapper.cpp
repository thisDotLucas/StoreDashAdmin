#include "ShelfMapper.h"

ShelfMapper::ShelfMapper(Shelf* shelf, std::map<QString, std::vector<QString>> ids, QWidget* parent) : m_shelf(shelf), m_ids(ids)
{
	ui.setupUi(this);
	connect(ui.okButton, &QPushButton::pressed, this, &ShelfMapper::okButtonPressed);
	connect(ui.cancelButton, &QPushButton::pressed, this, &ShelfMapper::cancelButtonPressed);
	connect(ui.moduleList, &QListWidget::currentItemChanged, this, &ShelfMapper::moduleChanged);
	connect(ui.shelfList, &QListWidget::currentItemChanged, this, &ShelfMapper::shelfChanged);

	for (const auto& [_module, _] : m_ids)
		ui.moduleList->addItem(_module);
}

void ShelfMapper::okButtonPressed()
{
	auto moduleId = getModuleId();
	if (moduleId.has_value())
		m_shelf->setModuleId(moduleId.value());

	auto shelfId = getShelfId();
	if (shelfId.has_value())
		m_shelf->setShelfId(shelfId.value());

	close();
}

void ShelfMapper::cancelButtonPressed()
{
	close();
}

void ShelfMapper::moduleChanged()
{
	m_selectedModule = ui.moduleList->currentItem()->text().toStdString();

	m_selectedShelf = std::nullopt;
	ui.shelfList->clear();
	for (const auto& shelf : m_ids[ui.moduleList->currentItem()->text()])
		ui.shelfList->addItem(shelf);
}

void ShelfMapper::shelfChanged()
{
	m_selectedShelf = ui.moduleList->currentItem()->text().toStdString();
}

std::optional<std::string> ShelfMapper::getModuleId() const
{
	return m_selectedModule;
}

std::optional<std::string> ShelfMapper::getShelfId() const
{
	return m_selectedShelf;
}
