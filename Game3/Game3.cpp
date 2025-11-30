#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <ctime>
#include "core/settings.h"
#include "engine/Graphik.h"
#include "game/Players.h"
#include "engine/Shrifts.h"
#include "engine/interface.h"
#include "game/level.h"
#include "game/objects.h"
#include "game/knight.h"
using namespace std;

void MakePlayers() 
{
	Player Player1;
	Player1.food = rand()%100000;
	Player1.stone = rand() % 100000;
	Player1.wood = rand() % 100000;
	Player1.gold = rand() % 100000;
	Player1.Nickname = "Ivan";
	Player1.botornotbot = false;
	Player Player2;
	Player2.food = 10;
	Player2.stone = 10;
	Player2.wood = 10;
	Player2.gold = 6;
	Player2.Nickname = "George";
	Player2.botornotbot = true;
	Players.push_back(Player1);
	Players.push_back(Player2);
}

// загрузка текстур игры
void loading_textures() {
	Load_Texture("House", "resource/House.png");
	Load_Texture("Main", "resource/The_town_hall.png");
	Load_Texture("Wall", "resource/Wall.png");
	Load_Texture("Barraks", "resource/Barracks.png");
	Load_Texture("Villager", "resource/Villager.png");
	Load_Texture("Knight", "resource/Knight.png");
	Load_Texture("Stone", "resource/Stone.png");
	Load_Texture("Dirt", "resource/Dirt.png");
	Load_Texture("Dirt", "resource/Dirt.png");
	Load_Texture("Grass", "resource/Grass.png");
	Load_Texture("Water", "resource/Water.png");
	Load_Texture("Stone_iron", "resource/Stone_iron.png");
	Load_Texture("Tree", "resource/Tree.png");
	Load_Texture("Gold_iron", "resource/Gold_iron.png");
	Load_Texture("Fish", "resource/Fish.png");
	Load_Texture("Kvadrat", "resource/Kvadrat.png");
}

// загрузка звуков
void loading_sounds() {
	//...
}

int main()
{
	// сид рандома перемешивает генерацию чисел
	srand(time(0));

	// начальная загрузка игры
	loading_textures();
	loading_sounds();
	make_interface();
	Loading_font();
	MakePlayers();
	auto level = generate_level();
	level_game = &level;
	int fps = 0;

	// Этот код потом снести:
	for (int i = 0; i <= 0; i++)
		spawn(new Knight());
	
	// Делаем окно
	sf::RenderWindow Okno(sf::VideoMode(sf::Vector2u(windowx,windowy)), "AOE");
	//Okno.setVerticalSyncEnabled(true);
	Okno.setFramerateLimit(60);
	sf::Clock clock;
	auto time_start = clock.getElapsedTime();
	
	// основной цикл игры
	while (eslinashaigravckluchena)
	{
		// обработка выхода из игры
        while (auto event = Okno.pollEvent()) {
            if (
                event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
                )
            {
				eslinashaigravckluchena = false;
                Okno.close();
            }

        }

		// тут мышка
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || 
			sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            auto pos = sf::Mouse::getPosition(Okno);
			mouseposx = pos.x;
			mouseposy = pos.y;
			mouseleft = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			mouseright = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
			Conrol_interface(level, pos.x, pos.y, mouseright);
        } else {
			mouseleft = mouseright = false;
		}
		
		Okno.clear(); // удалить предыдущий кадр
		camera_movement(Okno, mouseposx, mouseposy, level.max_x*50 - windowx, level.max_y*50 - windowy);
		update_objects();

		draw_level(Okno, level);
		draw_objects(Okno);
		Draw_interface(Okno);
		Okno.display(); // показать кадр игры
		fps++;

		auto time_end = clock.getElapsedTime();
		if ((time_end - time_start).asSeconds() > 1) {
			game_fps = fps;
			fps = 0;
			time_start = clock.getElapsedTime();
		}
	}
}