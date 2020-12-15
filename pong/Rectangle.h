#pragma once
#include "main.h"

class Rectangle : public sf::RectangleShape {
protected:
	sf::Vector2f size;
	double speed;
public:
	Rectangle();
	Rectangle(double pos_x,double pos_y, double width, double height);

	double getSpeed();
	void setSpeed(double speed);

	~Rectangle();
};