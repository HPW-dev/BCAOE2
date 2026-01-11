#include <random>
#include <iostream>
#include <algorithm>
#include "knight.h"
#include "core/settings.h"

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
    attack_speed = 120; int attack_speed;
    
    //bool show_interface {}; // если True - можно увидеть интерфейс взаимодействия
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

    if (!is_bot()) {
        // если нажали мышкой:
        if (mouseleft && mouse_in_level(mouseposx, mouseposy)) {
            target_x = mouseposx + camera_x;
            target_y = mouseposy + camera_y;
        }
    } else {
        if (hp_target <= 0 || botfps % 5 == 0)
            target_bot();
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

    collided = false; // произошло столкновение хоть с кем-то
    // проверить столкновения
    for (auto& o: objects) {
        if (this != o) {
            auto d = distance(x, y, o->x, o->y);
            bool low_distance = d <= 25; // близко к объекту
            bool time_to_attack = fps % attack_speed == 0;
            bool other_player = o->player != this->player;
            collided |= low_distance;
            if (low_distance && time_to_attack && other_player) {
                o->hp -= damage;
                //std::cout << texture << " attack " << o->texture << std::endl;
            }
            if (o->hp <= 0)
                o->kill(this);
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

    void Knight::target_bot() {
        std::vector<Object*> Players_to_atack;

        for (auto& o : objects)
            if (!o->is_bot() && o->player != nullptr)
                Players_to_atack.push_back(o);

        // перемешать список объектов пригодных для атаки
        std::default_random_engine random;
        std::shuffle(Players_to_atack.begin(), Players_to_atack.end(), random);

        Object* target = Players_to_atack[0];
        target_x = target->x;
        target_y = target->y;
        hp_target = target->hp;
    }
