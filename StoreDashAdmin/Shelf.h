#pragma once
#include "DrawableEntity.h"
#include <QtWidgets/QGraphicsItem>

class Shelf : public DrawableEntity, public QGraphicsItem
{
	void draw() override;
};

