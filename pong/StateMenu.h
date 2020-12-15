#pragma once
#include "State.h"
#include "StateGame.h"
#include "StateOptions.h"



//general menu
class StateMenu :public IState
{
private:
	sf::Font* font;
	sf::Text* menu;

	enum { TITLE,CONTINUE, PLAY, OPTIONS, EXIT };
	unsigned short selected_index;
	unsigned short move_step;

	void move_up();
	void move_down();

	bool isSelected;
	void select();

	sf::Music* musicMenu;
public:
	void init()override;
	void event(sf::RenderWindow* window, sf::Event* event, State* state)override;
	void update(sf::RenderWindow* window, sf::Time* time, State* state)override;
	void render(sf::RenderWindow* window)override;
	void clear()override;
};

//additional menu
class StateMenuPlayers :public IState {
private:
	sf::Font* font;
	sf::Text* vsChoice;

	enum { TITLE, PLAYER, BOT, MENU }buttonsAdditional;

	unsigned short selected_index;
	unsigned short move_step;

	void move_up();
	void move_down();

	bool isSelected;
	void select();
public:
	void init()override;
	void event(sf::RenderWindow* window, sf::Event* event, State* state)override;
	void update(sf::RenderWindow* window, sf::Time* time, State* state)override;
	void render(sf::RenderWindow* window)override;
	void clear()override;
};