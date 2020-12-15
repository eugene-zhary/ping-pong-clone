#pragma once
#include "State.h"
#include "StateMenu.h"


class StateOptions :public IState
{
private:
	sf::Font* font;
	sf::Text* options;
	sf::Text* values;
	sf::Text* description;


	sf::Text* text_plus;
	sf::Text* text_minus;
	sf::RectangleShape* plus;
	sf::RectangleShape* minus;

	enum { SOUND, MUSIC,CONTROL, MENU }buttons;
	short selected_index_general;
	short selected_index_additional;
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

