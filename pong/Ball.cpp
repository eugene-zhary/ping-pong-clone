#pragma once
#include "Ball.h"

Ball::Ball(Player *player, PlayerBot *bot, Score *scorePlayer, Score *scoreBot, Bounds *boundsTop, Bounds *boundsBot) :
	Rectangle(DISPLAY_WIDTH / 2 - 7.5, DISPLAY_HEIGHT / 2 - 7.5, 15, 15),
	speed(0.005f, 0.005f), player(player), bot(bot), scorePlayer(scorePlayer), scoreBot(scoreBot), boundsTop(boundsTop), boundsBot(boundsBot)
{
	this->buffer = new sf::SoundBuffer();
	this->buffer->loadFromFile(AUDIO_PLAYER);
	this->soundPlayer = new sf::Sound(*this->buffer);
	this->soundPlayer->setVolume(static_cast<float>(getSoundVolume()));

	this->buffer = new sf::SoundBuffer();
	this->buffer->loadFromFile(AUDIO_BOT);
	this->soundBot = new sf::Sound(*this->buffer);
	this->soundBot->setVolume(static_cast<float>(getSoundVolume()));

	this->buffer = new sf::SoundBuffer();
	this->buffer->loadFromFile(AUDIO_GOAL);
	this->soundGoal = new sf::Sound(*this->buffer);
	this->soundGoal->setVolume(static_cast<float>(getSoundVolume()));

	this->boundsLimit = 15;
}

bool Ball::CheckCollision(Rectangle* rect)
{
	return this->getGlobalBounds().intersects(rect->getGlobalBounds());
}

void Ball::reset() {
	this->setPosition(DISPLAY_WIDTH / 2 - 7.5f, DISPLAY_HEIGHT / 2 - 7.5f);

	this->player->setPosition(10, DISPLAY_HEIGHT / 2 - 50.f);
	this->bot->setPosition(DISPLAY_WIDTH - 25, DISPLAY_HEIGHT / 2 - 50.f);

	this->speed.x = 0.005f;
	this->speed.y = 0.005f;
}

void Ball::update(double time) {
	if (this->speed.y > Rectangle::getSpeed() - 0.0001 && this->bot->getIsBot() == true) {
		(this->speed.y > 0.f) ? this->bot->setSpeed(static_cast<double>(this->speed.y)) : this->bot->setSpeed(static_cast<double>(this->speed.y) * -1);
	}

	//bounds of window's width
	if (this->CheckCollision(this->boundsTop)) {
		this->speed.y *= -1.f;
		this->setPosition(this->getPosition().x, 10);
	}
	if (this->CheckCollision(this->boundsBot)) {
		this->speed.y *= -1.f;
		this->setPosition(this->getPosition().x, 575);
	}

	//bounds of window's height
	if (this->getPosition().x < 0.f) {
		this->scoreBot->incrementScore();
		setScoreBot(scoreBot->getValue());
		this->soundGoal->play();
		this->reset();
	}
	else if (this->getPosition().x + this->getSize().x > DISPLAY_WIDTH) {
		this->scorePlayer->incrementScore();
		setScorePlayer(scorePlayer->getValue());
		this->soundGoal->play();
		this->reset();
	}

	//bounds of players
	if (this->CheckCollision(this->player))
	{
		if (this->getPosition().x > this->player->getPosition().x + this->player->getSize().x - boundsLimit) {
			this->setPosition(25, this->getPosition().y);
			this->speed.x *= -1.f;
			(rand() % 2 == 1) ? this->speed.y *= -1.f : this->speed.y *= 1.f;

			if (this->speed.x < -0.0015f) {
				this->speed.x += 0.0005f;
			}

			if (this->speed.y > 0.f) {
				if (this->speed.y > 0.0015f) {
					this->speed.y -= 0.0005f;
				}
			}
			else {
				if (this->speed.y < -0.0015f) {
					this->speed.y += 0.0005f;
				}
			}
			this->soundPlayer->play();
		}
		else {
			this->speed.x *= 1.f;
		}
	}
	if (this->CheckCollision(this->bot))
	{
		if (this->getPosition().x + this->getSize().x < this->bot->getPosition().x + boundsLimit){
			this->setPosition(860, this->getPosition().y);
			this->speed.x *= -1.f;
			(rand() % 2 == 1) ? this->speed.y *= -1.f : this->speed.y *= 1.f;

			if (this->speed.x > 0.0015f) {
				this->speed.x -= 0.0005f;
			}

			if (this->speed.y > 0.f) {
				if (this->speed.y > 0.0015f) {
					this->speed.y -= 0.0005f;
				}
			}
			else {
				if (this->speed.y < -0.0015f) {
					this->speed.y += 0.0005f;
				}
			}
			this->soundBot->play();
		}
	}

	//ball moving
	this->move(-(static_cast<float>(time) / this->speed.x), -(static_cast<float>(time) / this->speed.y));
}

Ball::~Ball() {
	delete this->buffer;
	delete this->soundPlayer;
	delete this->soundBot;
	delete this->soundGoal;
}