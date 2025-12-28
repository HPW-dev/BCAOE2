#pragma once
#include "objects.h"
#include "game/level.h"

class Knight: public Object {
public:
    float armor = 5;
    float armorhp = 5;
    float safe_x;
    float safe_y;
    float target_x;
    float target_y;
    int hp_target {0};
    
    bool is_water(int x, int y);

    void target_bot();

    Knight(int _x, int _y);
    void action(float dt) override;
};
