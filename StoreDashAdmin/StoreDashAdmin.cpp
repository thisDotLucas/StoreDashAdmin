#include "StoreDashAdmin.h"
#include "Shelf.h"
#include "ShelfPen.h"
#include "NodePen.h"
#include "ConnectionPen.h"
#include "ConnectionPicker.h"
#include "GridScene.h"
#include <QFileDialog>
#include <iostream>

StoreDashAdmin::StoreDashAdmin(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	ui.graphicsView->setScene(new GridScene(this));

	connect(ui.shelfButton, &QPushButton::pressed, this, &StoreDashAdmin::shelfButtonPressed);
	connect(ui.nodeButton, &QPushButton::pressed, this, &StoreDashAdmin::nodeButtonPressed);
	connect(ui.connectionButton, &QPushButton::pressed, this, &StoreDashAdmin::connectionButtonPressed);
	connect(ui.saveButton, &QPushButton::pressed, this, &StoreDashAdmin::saveButtonPressed);
	connect(ui.loadButton, &QPushButton::pressed, this, &StoreDashAdmin::loadButtonPressed);
}

void StoreDashAdmin::shelfButtonPressed()
{
	ui.graphicsView->setPen(std::make_shared<ShelfPen>());
}

void StoreDashAdmin::setCursorLabel(const QPointF& point)
{
	std::stringstream stream;
	stream << std::to_string(int(point.x())) << ", " << std::to_string(int(point.y()));

	ui.posLabel->setText(QString::fromStdString(stream.str()));
}

void StoreDashAdmin::nodeButtonPressed()
{
	ui.graphicsView->setPen(std::make_shared<NodePen>());
}

void StoreDashAdmin::connectionButtonPressed()
{
	ui.graphicsView->setPicker(std::make_shared<ConnectionPicker>());
}

void StoreDashAdmin::saveButtonPressed()
{
	QJsonObject jsonObject;
	jsonObject.insert("Connections", QJsonArray{});
	jsonObject.insert("Nodes", QJsonArray{});
	jsonObject.insert("Shelves", QJsonArray{});

	for (const auto& item : ui.graphicsView->items())
	{
		Serializable* serializableItem = dynamic_cast<Serializable*>(item);
		if (serializableItem)
			serializableItem->serialize(jsonObject).value();
	}

	QByteArray json = QJsonDocument(jsonObject).toJson();

	if (json.size())
	{
		auto fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("JSON (*.json)"));
		if (!fileName.isEmpty())
		{
			QFile file(fileName);
			file.open(QIODevice::WriteOnly);
			file.write(json);
			file.close();
		}
	}
}

void StoreDashAdmin::loadButtonPressed()
{
	auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("JSON (*.json)"));
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QByteArray data = file.readAll();
		file.close();

		QJsonParseError error;
		QJsonDocument jsonDocument = QJsonDocument().fromJson(data, &error);

		QJsonObject object = jsonDocument.object();
		bool isValid = object.find("Connections") != std::end(object) && object.find("Nodes") != std::end(object) && object.find("Shelves") != std::end(object);

		if (isValid)
		{
			ui.graphicsView->items().clear();

			QJsonArray shelves = object.value("Shelves").toArray();
			for (const auto& shelf : shelves)
			{
				ui.graphicsView->scene()->addItem(new Shelf{ shelf.toObject() });
			}

			std::map<int, Node*> nodeMap;
			QJsonArray nodes = object.value("Nodes").toArray();
			for (const auto& node : nodes)
			{
				Node* nodeItem = new Node{ node.toObject() };
				nodeMap.insert({ nodeItem->getId(), nodeItem });

				ui.graphicsView->scene()->addItem(nodeItem);
			}

			QJsonArray connections = object.value("Connections").toArray();
			for (const auto& connection : connections)
			{
				ui.graphicsView->scene()->addItem(new Connection{ connection.toObject(), nodeMap });
			}
		}
		else
		{
			qDebug() << "Invalid JSON document!";
		}
	}
}

//void StoreDashAdmin::organizationButtonPressed()
//{
//	organizationEditorWindow;// = new OrganizationEditor(this);
//	organizationEditorWindow.setWindowModality(Qt::WindowModality::WindowModal);
//	organizationEditorWindow.show();
//}