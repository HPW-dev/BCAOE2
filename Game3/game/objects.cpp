#include <functional>
#include <algorithm>
#include <cmath>
#include "objects.h"
#include "Players.h"
#include "../engine/Graphik.h"
#include "../core/settings.h"
#include "../engine/interface.h"
#include "../core/settings.h"

using namespace std;

std::vector<std::function<void ()>> spawn_order;

bool Object::is_bot()
{
    for (auto& p : Players) {
        if (&p == player && p.botornotbot == true)
            return true;
    }

    return false;
}

void spawn(Object* obj)
{
    spawn_order.push_back([o=obj]{
        objects.push_back(o);
    });
}

void Object::draw(sf::RenderWindow& window) const
{
    auto pos_x = this->x - camera_x;
    auto pos_y = this->y - camera_y;
    const auto MAX_TEXTURE_SIZE = 100;
    // сдвигать некоторые объекты вверх, чтобы не стояли в воде
    if (this->type == Type::Tree ||
        this->type == Type::Knight ||
        this->type == Type::Villager)
    {
        pos_y -= 50;
    }
    if (pos_x >= windowx + MAX_TEXTURE_SIZE) return;
    if (pos_y >= windowy + MAX_TEXTURE_SIZE) return;
    if (pos_x < -MAX_TEXTURE_SIZE) return;
    if (pos_y < -MAX_TEXTURE_SIZE) return;

    Draw_Texture(window, pos_x, pos_y, this->texture);

    // рисовать прямоугольник тут:
    #if 0
    rect h = hitbox;
    h.x = pos_x;
    h.y = pos_y;
    Draw_rect(window, h, false);
    #endif
}

void draw_objects(sf::RenderWindow& window)
{
    for (auto obj: objects)
        if (obj->hp > 0)
            obj->draw(window);
}

void Object::action(float dt) {
    if (x > level_game->max_x * 50)
        x = level_game->max_x * 50 - 1;
    if (y > level_game->max_y * 50)
        y = level_game->max_y * 50 - 1;
    if (x < 0)
        x = 0;
    if (y < 20)
        y = 20;
    hitbox.x = x;
    hitbox.y = y;
    //std::cout << "Hitbox: x" << hitbox.x << ", y " << hitbox.y << "\n";
}

void Object::on_click() {
    // действие при нажатии
}
static void check_click() {
    for (auto obj: objects) {
        auto pos_x = mouseposx + camera_x;
        auto pos_y = mouseposy + camera_y;

        if (mouseleft && obj->hitbox.on_click(pos_x, pos_y)) {
            /* std::cout << "Object name: " << obj.texture << " in "
                << pos_x << ", " << pos_y << "\n"; */
            obj->on_click();
        }
    }
}

void update_objects(float dt)
{
    for (auto spawner: spawn_order)
        spawner();
    spawn_order.clear();

    for (auto obj: objects)
        if (obj->hp > 0)
            obj->action(dt);
    check_click();

    std::erase_if(objects, [](Object* obj)
    {
        return obj->hp <= 0;
    });
}

double distance(double ax, double ay, double bx, double by) {
    auto dx = ax - bx;
    auto dy = ay - by;
    return std::sqrt(dx*dx + dy*dy);
}

bool Object::check_hitbox(const Object other) {
    auto a = this->hitbox;
    auto b = other.hitbox;

    if (&a == &b)
        return false;

    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

void Object::kill(Object* other) {

}
