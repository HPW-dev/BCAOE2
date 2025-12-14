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
    std::string player;

    bool is_bot();
    
    bool is_water(int x, int y);

    Knight(int _x, int _y);
    void action(float dt) override;
};
