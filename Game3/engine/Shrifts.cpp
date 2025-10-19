#include "Shrifts.h"
using namespace std;

sf::Font font;

void Loading_font()
{
	font.openFromFile("resource/1shrift.ttf");
}

void Text_Draw (sf::RenderWindow& Screen,int x, int y, int sizefont, string text)
{
	sf::Text textdraw(font);
	textdraw.setPosition(sf::Vector2f( x,y ));
	textdraw.setString(text);
	textdraw.setCharacterSize(sizefont);
	textdraw.setFillColor({ 255,255,255 });
	Screen.draw(textdraw);
}