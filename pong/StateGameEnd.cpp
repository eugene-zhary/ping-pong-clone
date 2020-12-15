#include "StateGameEnd.h"

StateGameEnd::StateGameEnd(bool isBot, bool fin) :isBot(isBot), fin(fin) {}

void StateGameEnd::init() {
	this->font = new sf::Font();
	this->font->loadFromFile(FONT);

	(this->isBot) ?
		(this->fin) ? this->text = new sf::Text("YOU WIN\n", *this->font, 32U) :
		this->text = new sf::Text("YOU LOSE\n", *this->font, 32U) :
		(this->fin) ? this->text = new sf::Text("PLAYER 1 WIN\n", *this->font, 32U) :
		this->text = new sf::Text("PLAYER 2 WIN\n", *this->font, 32U);

	this->text->setPosition(100, 100);
	this->text->setFillColor(sf::Color(BRIGHT));

	this->buttons = new sf::Text[MAX_NUBER_OF_ITEMS_END]();

	for (int i = 0; i < MAX_NUBER_OF_ITEMS_END; i++) {
		this->buttons[i].setFont(*this->font);
		this->buttons[i].setCharacterSize(32U);
		this->buttons[i].setFillColor(sf::Color(BRIGHT));
	}
	this->buttons[0].setString("TRY AGAIN");
	this->buttons[0].setPosition(this->text->getPosition().x, this->text->getPosition().y + this->buttons[0].getCharacterSize() + 50);
	this->buttons[1].setString("MENU");
	this->buttons[1].setPosition(this->text->getPosition().x, this->buttons[0].getPosition().y + this->buttons[1].getCharacterSize() + 10);

	this->buffer = new sf::SoundBuffer();
	(this->isBot) ?
		(this->fin) ? this->buffer->loadFromFile(AUDIO_WIN) : this->buffer->loadFromFile(AUDIO_LOSE) :
		(this->fin) ? this->buffer->loadFromFile(AUDIO_WIN) : this->buffer->loadFromFile(AUDIO_WIN);

	this->finSound = new sf::Sound(*this->buffer);
	this->finSound->setVolume(static_cast<float>(getSoundVolume()));
	this->finSound->play();

	this->selected_index = 0;
	this->move_step = 4;
	this->isSelected = false;
}

void StateGameEnd::select() {
	this->isSelected = true;

	this->buttons[0].setCharacterSize(36U);
	this->buttons[0].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
	this->buttons[0].setFillColor(sf::Color(YELLOW));
}
void StateGameEnd::move_up() {
	if (selected_index - 1 >= 0) {
		this->buttons[selected_index].setCharacterSize(32U);
		this->buttons[selected_index].move(move_step, move_step);
		this->buttons[selected_index].setFillColor(sf::Color(BRIGHT));

		selected_index--;
		this->buttons[selected_index].setCharacterSize(36U);
		this->buttons[selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->buttons[selected_index].setFillColor(sf::Color(YELLOW));
	}
}
void StateGameEnd::move_down() {
	if (selected_index + 1 < 2) {
		this->buttons[selected_index].setCharacterSize(32U);
		this->buttons[selected_index].move(move_step, move_step);
		this->buttons[selected_index].setFillColor(sf::Color(BRIGHT));

		selected_index++;
		this->buttons[selected_index].setCharacterSize(36U);
		this->buttons[selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->buttons[selected_index].setFillColor(sf::Color(YELLOW));
	}
}

void StateGameEnd::event(sf::RenderWindow* window, sf::Event* event, State* state) {
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
		(isSelected) ? this->move_up() : this->select();
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
		(isSelected) ? this->move_down() : this->select();
	}

	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Enter && this->isSelected) {
		switch (selected_index)
		{
		case 0:
			state->setState(new StateGame(this->isBot));
			break;
		case 1:
			state->setState(new StateMenu());
			break;
		}
	}

	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
		if (this->buttons[0].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateGame(this->isBot));
		}
		else if (this->buttons[1].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateMenu());
		}
	}
}

void StateGameEnd::update(sf::RenderWindow* window, sf::Time* time, State* state) {

}

void StateGameEnd::render(sf::RenderWindow* window) {
	window->clear(sf::Color(DARK));

	(this->isBot) ?
		(this->fin) ? window->clear(sf::Color(GREEN)) :
		window->clear(sf::Color(RED)) :
		(this->fin) ? window->clear(sf::Color(DARK)) :
		window->clear(sf::Color(DARK));

	window->draw(*this->text);
	for (int i = 0; i < MAX_NUBER_OF_ITEMS_END; i++) {
		window->draw(this->buttons[i]);
	}
}

void StateGameEnd::clear() {
	delete this->finSound;
	delete this->buffer;

	delete[] this->buttons;
	delete this->text;
	delete this->font;
}

StateGameEnd::~StateGameEnd()
{
	this->clear();
}