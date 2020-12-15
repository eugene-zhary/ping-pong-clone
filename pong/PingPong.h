#pragma once
#include "StateMenu.h"
#include "StateGame.h"

class PingPong{
private:
	//all events from the user
	void processEvents();
	//update the game logic
	void update(sf::Time time);
	//rendering of the game
	void render();

	sf::Image ico;

	sf::RenderWindow window;
	State state;
public:
	PingPong();

	void run(int minimum_frame_per_seconds);

	~PingPong();
};