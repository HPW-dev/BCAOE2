#include "../engine/Graphik.h"

void Draw_rect(sf::RenderWindow& Window, rect Rect, bool filled)
{
	sf::RectangleShape Kruzhok(sf::Vector2f (Rect.w , Rect.h) );
	if (!filled) {
		Kruzhok.setFillColor(sf::Color::Transparent);
		Kruzhok.setOutlineThickness(2);
	} else {
		Kruzhok.setFillColor(Rect.color);
	}
	Kruzhok.setOutlineColor(Rect.color);
	Kruzhok.setPosition(sf::Vector2f (Rect.x , Rect.y));
	Window.draw(Kruzhok);
}

// пример: Load_Texture("Building", "Resources/Texture.png")
void Load_Texture(std::string textureid, std::string tofile)
{
	Texture x;
	x.file = tofile;
	x.tex = std::make_shared<sf::Texture>();
	try {
		x.tex->loadFromFile(tofile);
	} catch (...) {
		std::cerr << "Error while reading texture file \"" << tofile << "\"";
	}
	x.spr = std::make_shared<sf::Sprite>(*x.tex);

	listoftexture[textureid] = std::move(x);
}

void Draw_Texture(sf::RenderWindow& wnd, int x, int y, std::string textureid) 
{
	auto tex = listoftexture[textureid];
	tex.spr->setPosition(sf::Vector2f(x, y));
	wnd.draw(*tex.spr);
}

