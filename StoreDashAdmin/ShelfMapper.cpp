#include "ShelfMapper.h"

ShelfMapper::ShelfMapper(Node* shelfNode, const std::map<QString, std::map<QString, std::set<QString>>>& staticIds, std::map<QString, std::map<QString, std::set<QString>>>* ids, QWidget* parent) : m_shelfNode(shelfNode), m_ids(ids)
{
	ui.setupUi(this);
	connect(ui.okButton, &QPushButton::pressed, this, &ShelfMapper::okButtonPressed);
	connect(ui.cancelButton, &QPushButton::pressed, this, &ShelfMapper::cancelButtonPressed);
	connect(ui.moduleList, &QListWidget::currentItemChanged, this, &ShelfMapper::moduleChanged);
	connect(ui.shelfList, &QListWidget::currentItemChanged, this, &ShelfMapper::shelfChanged);

	m_selectedModuleAtStart = shelfNode->getModuleId();
	m_selectedShelfAtStart = shelfNode->getShelfId();

	if (m_selectedModuleAtStart.has_value() && m_selectedShelfAtStart.has_value() && m_selectedModuleAtStart != "NULL" && m_selectedShelfAtStart != "NULL")
	{
		m_ids->at(QString{ m_selectedModuleAtStart.value().c_str() }).insert({ QString{ m_selectedShelfAtStart.value().c_str() }, staticIds.at(QString{ m_selectedModuleAtStart.value().c_str() }).at(QString{ m_selectedShelfAtStart.value().c_str() }) });
	}

	ui.moduleText->setText(QString{ shelfNode->getModuleId().value_or("").c_str() });
	ui.shelfText->setText(QString{ shelfNode->getShelfId().value_or("").c_str() });

	for (const auto& [_module, _] : *m_ids)
		ui.moduleList->addItem(_module);

	auto foundModuleItem = ui.moduleList->findItems(QString{ shelfNode->getModuleId().value_or("").c_str() }, Qt::MatchFlag::MatchExactly);
	if (foundModuleItem.size() == 1)
		ui.moduleList->setCurrentItem(foundModuleItem[0]);

	auto foundShelfItem = ui.shelfList->findItems(QString{ shelfNode->getShelfId().value_or("").c_str() }, Qt::MatchFlag::MatchExactly);
	if (foundShelfItem.size() == 1)
		ui.shelfList->setCurrentItem(foundShelfItem[0]);
}

void ShelfMapper::okButtonPressed()
{
	auto moduleId = getModuleId();
	auto shelfId = getShelfId();

	if (moduleId.has_value() && shelfId.has_value())
	{
		m_shelfNode->setModuleId(moduleId.value());
		m_shelfNode->setShelfId(shelfId.value());

		m_ids->at(QString{ moduleId.value().c_str() }).erase(QString{ shelfId.value().c_str() });
	}

	close();
}

void ShelfMapper::cancelButtonPressed()
{
	close();
}

void ShelfMapper::moduleChanged()
{
	m_selectedModule = ui.moduleList->currentItem()->text().toStdString();
	ui.moduleText->setText(QString{ m_selectedModule.value_or("").c_str() });

	m_selectedShelf = std::nullopt;
	ui.shelfText->setText(QString{ "" });

	ui.shelfList->clear();
	for (const auto& [shelf, _] : m_ids->at(ui.moduleList->currentItem()->text()))
	{
		ui.shelfList->addItem(shelf);
	}
}

void ShelfMapper::shelfChanged()
{
	m_selectedShelf = ui.shelfList->currentItem() ? std::make_optional(ui.shelfList->currentItem()->text().toStdString()) : std::nullopt;
	ui.shelfText->setText(QString{ m_selectedShelf.value_or("").c_str() });

	ui.productList->clear();

	if (ui.moduleList->currentItem() && ui.shelfList->currentItem() && m_ids->contains(ui.moduleList->currentItem()->text()) && m_ids->at(ui.moduleList->currentItem()->text()).contains(ui.shelfList->currentItem()->text()))
		for (const auto& product : m_ids->at(ui.moduleList->currentItem()->text()).at(ui.shelfList->currentItem()->text()))
			ui.productList->addItem(product);
}

std::optional<std::string> ShelfMapper::getModuleId() const
{
	return m_selectedModule;
}

std::optional<std::string> ShelfMapper::getShelfId() const
{
	return m_selectedShelf;
}
