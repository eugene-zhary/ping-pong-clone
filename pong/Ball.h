#pragma once
#include "game_options.h"
#include "Player.h"
#include "PlayerBot.h"
#include "Bounds.h"
#include "Score.h"

class Ball : public Rectangle {
private:
	sf::Vector2f speed;

	Player* player;
	PlayerBot* bot;
	Bounds* boundsTop;
	Bounds* boundsBot;
	Score* scorePlayer;
	Score* scoreBot;

	sf::SoundBuffer* buffer;
	sf::Sound* soundPlayer;
	sf::Sound* soundBot;
	sf::Sound* soundGoal;

	unsigned short boundsLimit;
	
	void reset();
	bool CheckCollision(Rectangle* rect);
public:
	Ball(Player* player, PlayerBot* bot, Score* scorePlayer, Score* scoreBot, Bounds* boundsTop, Bounds* boundsBot);

	void update(double time);

	~Ball();
};