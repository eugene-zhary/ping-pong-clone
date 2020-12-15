#pragma once
#include "Rectangle.h"

Rectangle::Rectangle() :size(15, 75) {
	this->setSize(size);

	this->setFillColor(sf::Color(BRIGHT));

	this->speed = 0.003;
}

Rectangle::Rectangle(double pos_x, double pos_y, double width, double height) : size(static_cast<float>(width), static_cast<float>(height))
{
	this->setSize(size);

	this->setFillColor(sf::Color(BRIGHT));
	this->setPosition(static_cast<float>(pos_x), static_cast<float>(pos_y));

	this->speed = 0.003;
}

double Rectangle::getSpeed() {
	return this->speed;
}

void Rectangle::setSpeed(double speed) {
	this->speed = speed;
}

Rectangle::~Rectangle() {

}