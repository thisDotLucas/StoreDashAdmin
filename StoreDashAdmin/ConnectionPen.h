#pragma once
#include "Pen.h"
#include "Connection.h"
#include "qpoint.h"
#include <optional>

class ConnectionPen : public Pen
{
public:
	// While pressing mouse 1.
	Connection* press(const QPointF& point) override;

	// While relasing mouse 1.
	Connection* lift() override;

	// While holding down mouse 1.
	Connection* move(const QPointF& point) override;

	// The cursorshape used for this pen.
	Qt::CursorShape cursorShape() override { return Qt::CrossCursor; }

private:
	std::optional<Connection*> m_connection;
};

