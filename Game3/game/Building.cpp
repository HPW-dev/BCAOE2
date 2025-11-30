#include <iostream>
#include "../game/Building.h"
#include "../game/level.h"
#include "objects.h"
#include "../core/settings.h"

rect get_default_hitbox(int x, int y) {
    return rect {
        .x = float(x),
        .y = float(y),
        .w = float(tile_size * 2),
        .h = float(tile_size * 2)
    };
}

void build(const std::string& name, int x, int y) {
    istakenbuild = false; // когда здание поставлено, можно выйти из режима постройки

    if (name == "Main") {
        Object* building = new Object();
        building->texture = name;
        building->x = (x / tile_size) * tile_size;
        building->y = (y / tile_size) * tile_size;
        building->hp = building->hp_max = 200;
        building->type = Type::Main_house;
        building->hitbox = get_default_hitbox(building->x, building->y);
        spawn(building);
    } else if (name == "Barraks") {
        Object* building = new Object();
        building->texture = name;
        building->x = (x / tile_size) * tile_size;
        building->y = (y / tile_size) * tile_size;
        building->hp = building->hp_max = 150;
        building->type = Type::Barraks;
        building->hitbox = get_default_hitbox(building->x, building->y);
        spawn(building);
    } else if (name == "Wall") {
        Object* building = new Object();
        building->texture = name;
        building->x = (x / tile_size) * tile_size;
        building->y = (y / tile_size) * tile_size;
        building->hp = building->hp_max = 50;
        building->type = Type::Wall;
        building->hitbox = get_default_hitbox(building->x, building->y);
        spawn(building);
    } else if (name == "House") {
        Object* building = new Object();
        building->texture = name;
        building->x = (x / tile_size) * tile_size;
        building->y = (y / tile_size) * tile_size;
        building->hp = building->hp_max = 100;
        building->type = Type::House;
        building->hitbox = get_default_hitbox(building->x, building->y);
        spawn(building);
    }
    else {
        std::cerr << "Unknown building name: \"" << name << "\"\n";
        std::terminate();
    };
}