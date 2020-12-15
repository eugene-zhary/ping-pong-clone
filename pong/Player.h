#pragma once
#include "Rectangle.h"

class Player : public Rectangle
{
	void move_up(double time);
	void move_down(double time);
public:
	Player();

	void update(sf::RenderWindow* window, double time);

	~Player();
};