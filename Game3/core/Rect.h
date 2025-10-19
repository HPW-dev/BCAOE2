#pragma once
#include <SFML/Graphics.hpp>

// прямоугольник (для кнопок и проверки столкновений)
class rect
{
public:
	// позиция левого верхнего угла
	float x;
	float y;
	// размеры
	float w;
	float h;
	sf::Color color;

	bool on_click(int mouse_x, int mouse_y) const;
};