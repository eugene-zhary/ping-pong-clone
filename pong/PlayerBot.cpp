#pragma once
#include "PlayerBot.h"

PlayerBot::PlayerBot() : Rectangle(static_cast<double>(DISPLAY_WIDTH) - 25, static_cast<double>(DISPLAY_HEIGHT) / 2 - 50, 15, 100) {
	this->isBot = true;
}

PlayerBot::PlayerBot(bool isBot) : Rectangle(static_cast<double>(DISPLAY_WIDTH) - 25, static_cast<double>(DISPLAY_HEIGHT) / 2 - 50, 15, 100)
{
	this->isBot = isBot;
}

void PlayerBot::update(double time, Rectangle ball) {

	if (this->isBot) {
		(this->getPosition().y + (this->getSize().y / 2) >= ball.getPosition().y) ? move_up(time) : move_down(time);
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			move_up(time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			move_down(time);
		}
	}
}

bool PlayerBot::getIsBot()
{
	return this->isBot;
}

void PlayerBot::move_up(double time) {
	(this->getPosition().y < 10.f) ? this->move(0, 0) : this->move(0, -(static_cast<float>(time) / static_cast<float>(this->speed)));
}
void PlayerBot::move_down(double time) {
	(this->getPosition().y > DISPLAY_HEIGHT - (this->size.y + 10)) ? this->move(0, 0) : this->move(0, static_cast<float>(time) / static_cast<float>(this->speed));
}

PlayerBot::~PlayerBot() {

}