#include "knight.h"
#include "core/settings.h"

Knight::Knight() {
    texture = "Knight";
    x = rand()%100;
    y = rand()%100;
    armor = 5;
    armorhp = 5;
    type = Type::Knight;
    speed = 60;
    hp_max = hp = 123;
    damage = 15;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 20;
    hitbox.h = 20;
    
    //bool show_interface {}; // если True - можно увидеть интерфейс взаимодействия
}
bool Knight::is_water(int x, int y) {
    x /= 50;
    y /= 50;
    Tile tile = get_tile(x, y,*level_game);
    if (tile.canswim == 0)
        return(0);
    else
        return(1);
}

void Knight::action(float dt) {
    Object::action(dt);

    static auto target_x = x;
    static auto target_y = y;

    // если нажали мышкой:
    if (mouseleft && mouse_in_level(mouseposx, mouseposy)) {
        target_x = mouseposx + camera_x;
        target_y = mouseposy + camera_y;
    }

    auto dx = target_x - x;
    auto dy = target_y - y;

    /*
    if (dx < 0) x -= speed * dt;
    else        x += speed * dt;
    if (dy < 0) y -= speed * dt;
    else        y += speed * dt;
    */

    auto dist = distance(x, y, target_x, target_y);
    if (dist >= 1) {
        dx /= dist;
        dy /= dist;
        x += dx * speed * dt;
        y += dy * speed * dt;
    }
    if (is_water(x, y) == 1) {
        x = safe_x;
        y = safe_y;
        return;
    }
    safe_x = x;
    safe_y = y;
}
