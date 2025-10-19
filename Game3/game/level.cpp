#include "../game/level.h"
#include <cassert>
#include "../engine/Graphik.h"
#include "../core/settings.h"
#include "objects.h"

const int TEXTURE_X = 50;
const int TEXTURE_Y = 50;

// безопасно ставить тайл в нужную позицию на уровне
void set_tile(Level& lvl, int x, int y, Tile tile) {
    if (x >= 0 && x < lvl.max_x)
    if (y >= 0 && y < lvl.max_y)
        lvl.tiles[y * lvl.max_x + x] = tile;
}

bool check_to_build(const Level& lvl, int x, int y, int max_x, int max_y) {
    if (x < 0 || x >= lvl.max_x * tile_size) return false;
    if (y < 0 || y >= lvl.max_y * tile_size) return false;
    int tile_x = x / tile_size;
    int tile_y = y / tile_size;
    
    for (int ty = 0; ty < max_y; ++ty)
        for (int tx = 0; tx < max_x; ++tx)
            if (tile_x + tx >= 0 && tile_x + tx < lvl.max_x)
                if (tile_y + ty >= 0 && tile_y + ty < lvl.max_y)
                    if (lvl.tiles.at((tile_y + ty) * lvl.max_x + (tile_x + tx)).free_to_build == false)
                        return false;
    return true;
}

void take_pos(Level& lvl, int x, int y, int max_x, int max_y) {
    if (x < 0 || x >= lvl.max_x * tile_size) return;
    if (y < 0 || y >= lvl.max_y * tile_size) return;
    int tile_x = x / tile_size;
    int tile_y = y / tile_size;
    
    for (int ty = 0; ty < max_y; ++ty)
        for (int tx = 0; tx < max_x; ++tx)
            if (tile_x + tx >= 0 && tile_x + tx < lvl.max_x)
                if (tile_y + ty >= 0 && tile_y + ty < lvl.max_y)
                    lvl.tiles.at((tile_y + ty) * lvl.max_x + (tile_x + tx)).free_to_build = false;
}

Level generate_level() {
    Level lvl;
    lvl.max_x = 100;
    lvl.max_y = 100;
    lvl.name = "Сгенерированный тестовый уровень\n";
    lvl.spawn_points = 2;
    lvl.tiles.resize(lvl.max_x * lvl.max_y);

    /* рандомная мешанина
    for (auto& tile: lvl.tiles) {
        // переделать потом
        switch (rand() % 3) {
        case 0: tile.texture = "Grass"; break;
        case 1: tile.texture = "Stone"; break;
        case 2: tile.texture = "Dirt"; break;
        }
        tile.canwalk = true;
        tile.canswim = false;
    }
    */

    for (int y = 0; y < lvl.max_y; ++y)
    for (int x = 0; x < lvl.max_x; ++x) {
        auto& tile = lvl.tiles[y * lvl.max_x + x];
        auto f = std::cos(x / 5 + 0.02f)*10 * std::sin(y / 5 + 0.02f)*10;
        f -= 2.f;
        tile.canwalk = true;
        tile.canswim = false;
        switch (unsigned(f) % 4) {
            case 0: tile.texture = "Grass"; break;
            case 1: tile.texture = "Dirt"; break;
            case 2: tile.texture = "Stone"; break;
            case 3: tile.texture = "Water";
                tile.canswim = true;
                tile.canwalk = false;
                tile.free_to_build = false;
                break;
        }
        
    }
    
    // насажать деревьев
    for (int i = 0; i < 1'000; ++i) {
        Object Tree;
        Tree.texture = "Tree";
        Tree.x = rand()% (lvl.max_x * TEXTURE_X - TEXTURE_X);
        Tree.y = rand()% (lvl.max_y * TEXTURE_Y - TEXTURE_Y);
        Tree.hp = Tree.hp_max = 100;
        Tree.type = Type::Tree;

        const auto& tile = lvl.tiles.at(int(Tree.y / tile_size) * lvl.max_x + int(Tree.x / tile_size));
        if (tile.texture == "Grass" || tile.texture == "Dirt") {   
            spawn(Tree);
        }
    }

    return lvl;
}

void camera_movement(sf::RenderWindow& Window, int x, int y, int max_x, int max_y)
{
    auto pos = sf::Mouse::getPosition(Window);
    auto mouse_x = pos.x;
    auto mouse_y = pos.y;

    // поменять скорость камеры
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        camera_speed += 0.5;
        std::cout << "camera speed: " << camera_speed << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
        camera_speed -= 0.5;
        std::cout << "camera speed: " << camera_speed << std::endl;
    }
    camera_speed = std::clamp(camera_speed, 1.0, 200.0);

    // движение камеры
    if (mouse_x <= 20)           camera_x -= camera_speed;
    if (mouse_x >= windowx - 20) camera_x += camera_speed;
    if (mouse_y <= 20)           camera_y -= camera_speed;
    if (mouse_y >= windowy - 20) camera_y += camera_speed;

    const auto bound = 40;
    if (camera_x <= -bound) camera_x = -bound;
    if (camera_y <= -bound) camera_y = -bound;
    if (camera_x >= max_x + bound) camera_x = max_x + bound;
    if (camera_y >= max_y + bound) camera_y = max_y + bound;
}

void draw_level(sf::RenderWindow& Window, const Level& lvl) {
    assert(lvl.max_x > 0);
    assert(lvl.max_y > 0);
    assert(!lvl.tiles.empty());

    for (int y = 0; y < lvl.max_y; ++y)
    for (int x = 0; x < lvl.max_x; ++x) {
        double pos_x = x*TEXTURE_X + camera_x*-1;
        double pos_y = y*TEXTURE_Y + camera_y*-1;
        if (pos_x >= -70 && pos_y >= -70 && pos_x < windowx && pos_y < windowy) {
            if (!build_name.empty() && !lvl.tiles[y * lvl.max_x + x].free_to_build)
                Draw_Texture(Window, pos_x, pos_y, "Kvadrat");
            else
                Draw_Texture(Window, pos_x, pos_y, lvl.tiles[y * lvl.max_x + x].texture);
        }
    }
}