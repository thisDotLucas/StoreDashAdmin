#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsScene>
#include <QtNetwork>
#include <QtGui>
#include "ui_StoreDashAdmin.h"
#include "DrawingArea.h"


class StoreDashAdmin : public QWidget
{
	Q_OBJECT

public:
	StoreDashAdmin(QWidget* parent = Q_NULLPTR);

	// Sets the label diaplaying cursor coordinates on drawing.
	void setCursorLabel(const QPointF& point);

	// Set the token for backend authorization.
	void setToken(const QString& token) { m_authToken = token; emit hasToken(); };

	std::map<QString, std::map<QString, std::set<QString>>>* getIdMap() { return &m_ids; }
	const std::map<QString, std::map<QString, std::set<QString>>>& getStaticIdMap() { return m_static_ids; }
	DrawingArea* getView() const { return (DrawingArea*)ui.graphicsView; };

private slots:
	// On key press event.
	virtual void keyPressEvent(QKeyEvent* e);

	// on shelf button press.
	void shelfButtonPressed();

	// on node button press.
	void nodeButtonPressed();

	// on connection button press.
	void connectionButtonPressed();

	// on save button press.
	void saveButtonPressed();

	// on load button press.
	void loadButtonPressed();

	void getIds();
	void gotToken();
	void gotIds();

signals:
	void hasToken();

private:
	void getToken();
	Ui::StoreDashAdminClass ui;
	std::optional<QString> m_authToken;
	QNetworkAccessManager* m_manager;
	QNetworkReply* m_reply;
	QNetworkAccessManager* m_manager2;
	QNetworkReply* m_reply2;
	std::map<QString, std::map<QString, std::set<QString>>> m_static_ids;
	std::map<QString, std::map<QString, std::set<QString>>> m_ids;
};
