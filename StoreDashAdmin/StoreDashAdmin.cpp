#include "StoreDashAdmin.h"
#include "Shelf.h"

StoreDashAdmin::StoreDashAdmin(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);

	m_drawingArea = std::make_unique<DrawingArea>(ui.drawingArea);
	m_drawingArea->setObjectName(QString::fromUtf8("graphicsView"));
	m_drawingArea->setMouseTracking(true);

	ui.verticalLayout_2->addWidget(m_drawingArea.get());

	connect(ui.shelfButton, &QPushButton::pressed, this, &StoreDashAdmin::shelfButtonPressed);
}

void StoreDashAdmin::shelfButtonPressed()
{
	//m_drawingArea->setDrawableEntity(/*new Shelf*/);
}