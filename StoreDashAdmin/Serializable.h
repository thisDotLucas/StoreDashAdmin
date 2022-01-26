#pragma once
#include <qstring.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <optional>

struct JsonElement
{
	QString key;
	QJsonValue value;
};

class Serializable
{
public:
	virtual std::optional<QJsonObject> serialize(QJsonObject& root) = 0;
};

