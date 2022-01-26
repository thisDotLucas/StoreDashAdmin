#pragma once
#include "Pen.h"
#include "Connection.h"
#include "qpoint.h"
#include <optional>

class ConnectionPen : public Pen
{
public:
	Connection* press(const QPointF& point) override;
	Connection* lift() override;
	Connection* move(const QPointF& point) override;

private:
	std::optional<Connection*> m_connection;
};

