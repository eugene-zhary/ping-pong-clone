#pragma once
#include "Rectangle.h"

class PlayerBot : public Rectangle
{
private:
	bool isBot;
	void move_up(double time);
	void move_down(double time);
public:
	PlayerBot();
	PlayerBot(bool isBot);

	void update(double time, Rectangle ball);
	bool getIsBot();

	~PlayerBot();
};