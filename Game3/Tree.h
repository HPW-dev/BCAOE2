#pragma once
#include "game/objects.h"
#include "game/level.h"

class Tree : public Object {
public:
	void kill(Object* other) override;
};