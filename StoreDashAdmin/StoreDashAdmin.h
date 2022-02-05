#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsScene>
#include <QtGui>
//#include <QtNetwork>
#include "ui_StoreDashAdmin.h"
#include "DrawingArea.h"

class StoreDashAdmin : public QWidget
{
	Q_OBJECT

public:
	StoreDashAdmin(QWidget* parent = Q_NULLPTR);
	void setCursorLabel(const QPointF& point);

private slots:
	virtual void keyPressEvent(QKeyEvent* e);
	void shelfButtonPressed();
	void nodeButtonPressed();
	void connectionButtonPressed();
	void saveButtonPressed();
	void loadButtonPressed();

private:
	//void postRequest(QByteArray& postData);
	//void onFinish(QNetworkReply* reply);
	Ui::StoreDashAdminClass ui;
};
