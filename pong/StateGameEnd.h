#pragma once
#include "State.h"
#include "StateGame.h"
#include "StateMenu.h"

class StateGameEnd :public IState {
private:
	bool isBot;
	bool fin;

	sf::Font *font;
	sf::Text *text;
	sf::Text *buttons;

	sf::SoundBuffer *buffer;
	sf::Sound *finSound;

	unsigned short selected_index;
	unsigned short move_step;

	void move_up();
	void move_down();

	bool isSelected;
	void select();
public:
	StateGameEnd(bool isBot, bool fin);
	void init()override;
	void event(sf::RenderWindow *window, sf::Event *event, State *state)override;
	void update(sf::RenderWindow *window, sf::Time *time, State *state)override;
	void render(sf::RenderWindow *window)override;
	void clear()override;
	~StateGameEnd();
};