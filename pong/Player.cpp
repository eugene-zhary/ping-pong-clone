#pragma once
#include "Player.h"

Player::Player() : Rectangle(10, static_cast<double>(DISPLAY_HEIGHT) / 2 - 50, 15, 100) {}

void Player::update(sf::RenderWindow* window, double time) {
	if (getControl()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			move_up(time);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			move_down(time);
		}
	}
	else {
		(this->getPosition().y + (this->getSize().y / 2) >= sf::Mouse::getPosition(*window).y) ?
			move_up(time) : move_down(time);
	}

}

void Player::move_up(double time) {
	(this->getPosition().y < 10.f) ? this->move(0, 0) : this->move(0, -(static_cast<float>(time) / static_cast<float>(this->speed)));
}
void Player::move_down(double time) {
	(this->getPosition().y > DISPLAY_HEIGHT - (this->size.y + 10)) ? this->move(0, 0) : this->move(0, static_cast<float>(time) / static_cast<float>(this->speed));
}

Player::~Player() {

}