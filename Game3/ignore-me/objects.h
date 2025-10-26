#pragma once
#include <string>
#include <vector>
#include <memory>
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

// Базовый класс для всех объектов в игре
class Object {
public:
    Type type {}; // кем является объект
    std::string texture {}; // название текстуры (не файла)
    float x {}; // положение x у объекта
    float y {}; // положение у у объекта
    rect hitbox{}; // хитбокс для попадания по объекту
    bool show_interface {}; // если True - можно увидеть интерфейс взаимодействия

    explit Object(Type _type);
    inline virtual void spawn_me() {}
};

// Объекты разрушаемые/с жизнями
class NPS : public Object {
public:
    float speed{}; // скорость объекта
    int hp{}; // жизни объекта или количество ресурса
    int hp_max{};
    int damage{}; // урон при атаке
};

struct Price {
    int gold {};
    int stone {};
    int wood {};
};

// Постройки
class Buildings : public NPS {
public:
    Price price {};
};

// стенка
class Wall : public Buildings {
public:
    Wall();
    void spawn_me() override;
};

class Barraks : public Buildings {
public:
    Barraks();
    void spawn_me() override;
};
class Main : public Buildings {
public:
    Main();
    void spawn_me() override;
};
class House: public Buildings {
public:
    House();
    void spawn_me() override;
};

class Tree : public NPS {};

inline std::vector<Object*> objects;

// спавн объекта
//void spawn(const Object& obj);
// отрисовка всех объектов
void draw_objects(sf::RenderWindow& window);
// обновить логику всех объектов
void update_objects(float dt=1.0/60.0);
