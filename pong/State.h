#pragma once
#include "main.h"

class State;

class IState {
public:
	virtual void init() = 0;
	virtual void event(sf::RenderWindow *window, sf::Event *event, State *state) = 0;
	virtual void update(sf::RenderWindow *window, sf::Time *time, State *state) = 0;
	virtual void render(sf::RenderWindow *window) = 0;
	virtual void clear() = 0;
};

class State {
private:
	sf::RenderWindow *window;
	IState *state;
public:
	State();
	void setState(IState *state);
	void setWindow(sf::RenderWindow *window);

	void event(sf::Event *event, State *state);
	void update(sf::Time *time, State *state);
	void render();
	~State();
};