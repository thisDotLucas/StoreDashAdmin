#pragma once

#include "Entity.h"

class DrawableEntity : public Entity
{
	virtual void draw() = 0;
};

