#include "knight.h"
#include "core/settings.h"
#include "Players.h"

Knight::Knight(int _x, int _y) {
    texture = "Knight";
    x = _x;
    y = _y;
    safe_x = _x;
    safe_y = _y;
    target_x = _x;
    target_y = _y;
    armor = 5;
    armorhp = 5;
    type = Type::Knight;
    speed = 200;
    hp_max = hp = 123;
    damage = 15;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 20;
    hitbox.h = 20;
    
    //bool show_interface {}; // если True - можно увидеть интерфейс взаимодействия
}

bool Knight::is_bot()
{
    for (auto p: Players) {
        if (p.botornotbot == true && p.Nickname == this->player)
            return true;
    }

    return false;
}
bool Knight::is_water(int x, int y) {
    x /= 50;
    y /= 50;
    Tile tile = get_tile(x, y,*level_game);
    if (tile.canswim == 0 && tile.free_to_build == 1)
        return(0);
    else
        return(1);
}

void Knight::action(float dt) {
    Object::action(dt);

    // если нажали мышкой:
    if (mouseleft && mouse_in_level(mouseposx, mouseposy) && !is_bot()) {
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

    // идти в сторону цели
    auto dist = distance(x, y, target_x, target_y);
    if (dist >= 50) {
        dx /= dist;
        dy /= dist;
        x += dx * speed * dt;
        y += dy * speed * dt;
    }
    else
    {
        dist = 0;
    }

    // проверить столкновения
    collided = false;
    for (auto& o: objects) {
        if (this != o) {
            auto d = distance(x, y, o->x, o->y);
            collided |= (d <= 25);
        }
    }
    // если врезались, то дёргаемся
    if (this->collided) {
        x += (rand() % 3 - 1) * 2;
        y += (rand() % 3 - 1) * 2;
    }

    if (is_water(x, y) == 1) {
        x = safe_x;
        y = safe_y;
        return;
    }
    safe_x = x;
    safe_y = y;
}
