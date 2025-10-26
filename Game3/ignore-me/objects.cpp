#include <functional>
#include "objects.h"
#include "../engine/Graphik.h"
#include "../core/settings.h"
#include "../engine/interface.h"

std::vector<std::function<void ()>> spawn_order;

static void spawn(const Object& obj)
{
    spawn_order.push_back([o=obj]{
        objects.push_back(o);
    });
}

static void draw(sf::RenderWindow& window, const Object& obj)
{
    auto pos_x = obj.x - camera_x;
    auto pos_y = obj.y - camera_y;
    const auto MAX_TEXTURE_SIZE = 100;
    if (pos_x >= windowx + MAX_TEXTURE_SIZE) return;
    if (pos_y >= windowy + MAX_TEXTURE_SIZE) return;
    if (pos_x < -MAX_TEXTURE_SIZE) return;
    if (pos_y < -MAX_TEXTURE_SIZE) return;
    Draw_Texture(window, pos_x, pos_y, obj.texture);
}

void draw_objects(sf::RenderWindow& window)
{
    for (int i = 0; const auto& o: objects) {
        draw(window, o);
    }
}

static void check_click() {
    for (auto& obj: objects) {
        auto pos_x = mouseposx + camera_x;
        auto pos_y = mouseposy + camera_y;
        // rect_class xxx;
        // xxx.on_click(x, y)
        if (mouseleft && obj.hitbox.on_click(pos_x, pos_y)) {
            std::cout << "Object name: " << obj.texture << " in "
                << pos_x << ", " << pos_y << "\n";
        }
    }
}

void update_objects(float dt)
{
    for (auto action: spawn_order)
        action();
    spawn_order.clear();

    check_click();
}

Object::Object(Type _type): type {_type} {
    assert(type != Type::Unknown);
} 
