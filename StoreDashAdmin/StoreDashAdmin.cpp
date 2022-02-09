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

	ui.shelfButton->setIcon(QIcon("stand.png"));
	ui.nodeButton->setIcon(QIcon("neural.png"));
	ui.connectionButton->setIcon(QIcon("chains.png"));
	ui.saveButton->setIcon(QIcon("save.png"));
	ui.loadButton->setIcon(QIcon("open-folder.png"));

	ui.shelfButton->setIconSize(QSize(25, 25));
	ui.nodeButton->setIconSize(QSize(25, 25));
	ui.connectionButton->setIconSize(QSize(25, 25));
	ui.saveButton->setIconSize(QSize(25, 25));
	ui.loadButton->setIconSize(QSize(25, 25));

	connect(this, &StoreDashAdmin::hasToken, this, &StoreDashAdmin::getIds);
	getToken();

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
				Node* nodeItem = new Node{ node.toObject(), getIdMap() };
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

void StoreDashAdmin::getIds()
{
	QNetworkRequest backendRequest(QUrl{ "https://products-api.eu1.cluster.storeda.sh/product/v1/layout" });
	backendRequest.setRawHeader(QByteArray("Authorization"), QByteArray(("Bearer " + m_authToken.value().toStdString()).c_str()));
	backendRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

	m_manager2 = new QNetworkAccessManager();
	m_reply2 = m_manager2->get(backendRequest);

	QObject::connect(m_reply2, &QNetworkReply::finished, this, &StoreDashAdmin::gotIds);
}

void StoreDashAdmin::gotToken()
{
	if (m_reply->error() == QNetworkReply::NoError)
	{
		QString token = QJsonDocument::fromJson(m_reply->readAll()).object().value("access_token").toString();
		setToken(token);
	}
	else
	{
		QString err = m_reply->errorString();
		qDebug() << err;
	}
	m_reply->deleteLater();
}

void StoreDashAdmin::gotIds()
{
	if (m_reply2->error() == QNetworkReply::NoError)
	{
		QJsonObject json = QJsonDocument::fromJson(m_reply2->readAll()).object().value("data").toObject();
		for (const auto& key : json.keys())
		{
			std::set<QString> values;
			for (const auto& value : json.value(key).toArray())
				values.insert(QString{ std::to_string(value.toInt()).c_str() });

			m_ids.insert({ key, values });
		}
	}
	else
	{
		QString err = m_reply2->errorString();
		qDebug() << err;
	}
	m_reply2->deleteLater();
}

void StoreDashAdmin::getToken()
{
	m_manager = new QNetworkAccessManager();

	QNetworkRequest request(QUrl{ "https://storedash-project.eu.auth0.com/oauth/token" });
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	QString body = "{ \"client_id\": \"BzL4Q8lag6ZKEjOcljqlOD5Dlwjaztcq\", \"client_secret\" : \"-53CuLQAslaOQzSOF9eWQv7C2w8svDfxI9jXRJltjKYDbgPC9dFwSW8GqUIilbyn\", \"audience\" : \"https://products-api.eu1.cluster.storeda.sh/\", \"grant_type\" : \"client_credentials\" }";
	m_reply = m_manager->post(request, body.toUtf8());

	QObject::connect(m_reply, &QNetworkReply::finished, this, &StoreDashAdmin::gotToken);
}

void StoreDashAdmin::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_Escape)
	{
		ui.graphicsView->clearPenAndPicker();
	}

	QWidget::keyPressEvent(e);
}
