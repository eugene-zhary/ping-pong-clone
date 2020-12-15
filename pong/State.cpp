#include "State.h"

State::State() {
	this->state = nullptr;
}

void State::setWindow(sf::RenderWindow* window) {
	this->window = window;
}
void State::setState(IState* state) {
	if (this->state != nullptr)this->state->clear();
	this->state = state;
	if (this->state != nullptr)this->state->init();
}

void State::event(sf::Event* event, State* state) {
	if (this->state != nullptr)this->state->event(this->window, event, state);
}
void State::update(sf::Time* time, State* state) {
	if (this->state != nullptr)this->state->update(this->window, time, state);
}
void State::render() {
	if (this->state != nullptr)this->state->render(this->window);
}


State::~State() {
	if (this->state != nullptr)	this->state->clear();
}