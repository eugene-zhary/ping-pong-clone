#pragma once
#include "State.h"
#include "StateMenu.h"
#include "StateGameEnd.h"
#include "Ball.h"


class StateGame : public IState {
private:
	bool isBot;
	//GAME PART
	sf::Font* font;
	Score* scorePlayer;
	Score* scoreBot;

	Player* player;
	PlayerBot* bot;
	Bounds* boundsTop;
	Bounds* boundsBot;
	Ball* ball;
	//PAUSE PART

	sf::RectangleShape* pauseRect;
	sf::Text* pause_symbol;

	bool pause;

	enum { TITLE, RESUME, MENU }buttons;
	sf::RectangleShape* pauseBackground;
	sf::Text* pause_text;
	unsigned short selected_index;
	unsigned short move_step;

	void move_up();
	void move_down();

	bool isSelected;
	void select();
	void unselect();
	//MUSIC PART
	sf::Music* gameMusic;
public:
	StateGame();
	StateGame(bool isBot);
	void init()override;
	void event(sf::RenderWindow* window, sf::Event* event, State* state)override;
	void update(sf::RenderWindow* window, sf::Time* time, State* state)override;
	void render(sf::RenderWindow* window)override;
	void clear()override;
};