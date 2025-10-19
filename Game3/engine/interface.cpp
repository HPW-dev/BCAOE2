#include "../engine/interface.h"
#include <SFML/Graphics.hpp>
#include "../engine/Graphik.h"
#include "../game/Players.h"
#include "Shrifts.h"
#include "../core/settings.h"
#include "../game/Building.h"
#include "../game/level.h"
#include "../core/Rect.h"
#include <string>
#include <format>
#include <vector>
#include <functional>
using namespace std;

rect interfaceboard = rect{ 0,600,1080,120, sf::Color(0,0,0,150) };
vector <Build_button> ListOfButtons;

void make_interface()
{
	ListOfButtons.push_back(Build_button{
		.textureid = "Main",
		.button_end = rect {15, 615, 90, 90, sf::Color::Green},
		.name = "Main",
		.gold = 50,
		.wood = 20,
		.stone = 30,
	});
	ListOfButtons.push_back(Build_button{
		.textureid = "House",
		.button_end = rect {120, 615, 90, 90, sf::Color::Red},
		.name = "House",
		.gold = 0,
		.wood = 10,
		.stone = 10 });
	ListOfButtons.push_back(Build_button{
		.textureid = "Barraks",
		.button_end = rect {225, 615, 90, 90, sf::Color::Yellow},
		.name = "Barraks",
		.gold = 20,
		.wood = 10,
		.stone = 0 });
	ListOfButtons.push_back( Build_button{
		.textureid = "Wall",
		.button_end = rect {330, 615, 90, 90, sf::Color::Blue},
		.name = "Wall",
		.gold = 0,
		.wood = 10,
		.stone = 5 });
}
void Conrol_interface(Level& level, int x, int y, bool is_right)
{
	// режим установки здания
	if (!is_right && istakenbuild) {
		if (y <= windowy - interfaceboard.h - 50) { // проврка что здание ставится не в интерфейсе
			if (check_to_build(level, x + camera_x, y + camera_y, 2, 2)) {
				build(build_name, x + camera_x, y + camera_y);
				take_pos(level, x + camera_x, y + camera_y, 2, 2);
				istakenbuild = false;
				build_name = {};
			}
		}
	}

	if (!is_right) { // если не правая кнопка
		for (auto& button : ListOfButtons) {
			if (button.button_end.on_click(x, y) && !istakenbuild) {
				auto& player = Players.at(0);

				//std::cout << "Button name: " << button.name << "\n";
				if (player.gold >= button.gold
				&& player.wood >= button.wood
				&& player.stone >= button.stone) {
					if (button.action) 
						button.action();
					build_name = button.textureid;
        			istakenbuild = true;
					player.gold -= button.gold;
					player.wood -= button.wood;
					player.stone -= button.stone;
				} else {
					std::cout << "not enough resources for building\n";
				}
			} // if collision detect
		} // for buttons
	}
}
void Draw_interface(sf::RenderWindow& Screen)
{
	Draw_rect(Screen, interfaceboard, true);
	for (int i = 0; i < ListOfButtons.size(); i++)
	{
		Draw_rect(Screen, ListOfButtons[i].button_end);
		Draw_Texture(
			Screen,
			ListOfButtons[i].button_end.x,
			ListOfButtons[i].button_end.y,
			ListOfButtons[i].textureid
		);
	}

	if (istakenbuild) {
		auto pos = sf::Mouse::getPosition(Screen);
		Draw_Texture(
			Screen,
			(int(pos.x)/tile_size)*tile_size,
			(int(pos.y)/tile_size)*tile_size,
			build_name);
	}

	// отрисовка интерфейса
	for (int i = 0; i < Players.size(); i++)
	{
		auto txt = std::format("Player name: {} | Food: {} | Gold {} | Wood {} | Stone {}"
			, Players[i].Nickname, Players[i].food, Players[i].gold, Players[i].wood, Players[i].stone);
		Text_Draw(Screen, 650, 0 + i * 20, 15, txt);
	}

	Text_Draw(Screen, 10, 10, 40, "FPS: " + std::to_string(game_fps));
}
