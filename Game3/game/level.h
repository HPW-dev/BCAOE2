#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// из них состоит уровень - квадратики с текстурами
struct Tile {
    std::string texture {};
    bool canwalk = true;
    bool canswim = false;
    bool free_to_build = true;
};

struct Level {
    // максимальные размеры уровня
	int max_x {};
	int max_y {};
    std::string name {};
    int spawn_points {};
    std::vector<Tile> tiles {};
};

// поставить текстуру в определённое место
void set_tile(int x, int y, Tile tile);

// true, если строительство по координатам разрешено
bool check_to_build(const Level& lvl, int x, int y, int max_x, int max_y);

// занять место под постройку
void take_pos(Level& lvl, int x, int y, int max_x, int max_y);

Level generate_level();

// отрисовка уровня
void draw_level(sf::RenderWindow& Window, const Level& lvl);

void camera_movement(sf::RenderWindow& Window, int x, int y, int max_x, int max_y);
