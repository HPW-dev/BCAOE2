#pragma once
#include "objects.h"
#include "game/level.h"

class Knight: public Object {
public:
    float armor = 5;
    float armorhp = 5;
    float safe_x;
    float safe_y;
    
    bool is_water(int x, int y);

    Knight();
    void action(float dt) override;
};
