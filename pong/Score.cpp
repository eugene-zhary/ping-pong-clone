#include "Score.h"

Score::Score(unsigned short value, sf::Font &font, unsigned short font_size) : value(value),Text(std::to_string(this->value),font, font_size)
{
	this->setFillColor(sf::Color(BRIGHT));
}

void Score::incrementScore() {
	this->value++;
}

void Score::update() {
	this->setString(std::to_string(this->value));
}
unsigned short Score::getValue()
{
	return this->value;
}
Score::~Score()
{
}