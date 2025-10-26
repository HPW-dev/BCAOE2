#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../core/Rect.h"

// Все возможные типы объектов
enum class Type {
    Unknown = 0,

    // ресурсы:
    Fish,
    Tree,
    Stone_iron,
    Gold_iron,

    // юниты:
    Villager,
    Knight,

    // Здания:
    Main_house,
    Barraks,
    Wall,
    House,
};

struct Object {
    Type type {}; // кем является объект
    std::string texture {}; // название текстуры (не файла)
    float x {}; // положение x у объекта
    float y {}; // положение у у объекта
    float speed {}; // скорость объекта
    int hp {}; // жизни объекта или количество ресурса
    int hp_max {};
    int damage {}; // урон при атаке
    rect hitbox {}; // хитбокс для попадания по объекту
    bool show_interface {}; // если True - можно увидеть интерфейс взаимодействия
};

inline std::vector<Object> objects;

// спавн объекта
void spawn(const Object& obj);
// отрисовка всех объектов
void draw_objects(sf::RenderWindow& window);
// обновить логику всех объектов
void update_objects(float dt=1.0/60.0);
