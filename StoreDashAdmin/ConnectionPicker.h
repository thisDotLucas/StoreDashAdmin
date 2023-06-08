#pragma once
#include "Picker.h"
#include "Connection.h"


class ConnectionPicker : public Picker
{
public:
	ConnectionPicker() {}
	~ConnectionPicker();

	// Pick start and end node for new connection.
	std::optional<QGraphicsItem*> pick(QGraphicsView* view, QPointF point) override;

private:
	std::optional<Connection*> m_connection;
};

