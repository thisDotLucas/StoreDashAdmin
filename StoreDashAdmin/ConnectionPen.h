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
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	std::optional<Connection*> m_connection;
};

