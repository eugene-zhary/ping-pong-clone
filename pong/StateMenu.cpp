#include "StateMenu.h"

void StateMenu::init() {
	this->font = new sf::Font();
	font->loadFromFile(FONT);

	this->menu = new sf::Text[MAX_NUBER_OF_ITEMS_MENU_GENERAL]();

	for (int i = 0; i < MAX_NUBER_OF_ITEMS_MENU_GENERAL; i++) {
		this->menu[i].setFont(*this->font);
		this->menu[i].setFillColor(sf::Color(BRIGHT));
		this->menu[i].setCharacterSize(32U);
	}

	this->move_step = 4;

	this->menu[TITLE].setString("PING PONG");
	this->menu[TITLE].setCharacterSize(64U);
	this->menu[TITLE].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->menu[TITLE].getString().getSize())* this->menu[TITLE].getCharacterSize() / 2), static_cast<float>(this->menu[TITLE].getCharacterSize()));

	this->menu[CONTINUE].setString("CONTINUE");
	this->menu[CONTINUE].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->menu[CONTINUE].getString().getSize())* this->menu[CONTINUE].getCharacterSize() / 2), DISPLAY_HEIGHT / 2 - static_cast<float>(this->menu[CONTINUE].getCharacterSize()) / 2);

	this->menu[PLAY].setString("NEW GAME");
	this->menu[PLAY].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->menu[PLAY].getString().getSize())* this->menu[PLAY].getCharacterSize() / 2), this->menu[CONTINUE].getPosition().y + static_cast<float>(this->menu[CONTINUE].getCharacterSize()) + 10);

	this->menu[OPTIONS].setString("OPTIONS");
	this->menu[OPTIONS].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->menu[OPTIONS].getString().getSize())* this->menu[OPTIONS].getCharacterSize() / 2), this->menu[PLAY].getPosition().y + static_cast<float>(this->menu[PLAY].getCharacterSize()) + 10);

	this->menu[EXIT].setString("EXIT");
	this->menu[EXIT].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->menu[EXIT].getString().getSize())* this->menu[EXIT].getCharacterSize() / 2), this->menu[OPTIONS].getPosition().y + static_cast<float>(this->menu[OPTIONS].getCharacterSize()) + 10);

	(getScorePlayer() == 0 && getScoreBot() == 0) ? this->selected_index = PLAY : this->selected_index = CONTINUE;

	this->musicMenu = new sf::Music();
	this->musicMenu->openFromFile(AUDIO_MENU);
	this->musicMenu->setVolume(static_cast<float>(getMusicVolume()));
	this->musicMenu->play();

	this->isSelected = false;
}

void StateMenu::select() {
	this->isSelected = true;

	if (this->selected_index == PLAY) {

		this->menu[PLAY].setCharacterSize(36U);
		this->menu[PLAY].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
		this->menu[PLAY].setFillColor(sf::Color(YELLOW));
	}
	else if (this->selected_index == CONTINUE) {
		this->menu[CONTINUE].setCharacterSize(36U);
		this->menu[CONTINUE].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
		this->menu[CONTINUE].setFillColor(sf::Color(YELLOW));
	}
}
void StateMenu::move_up() {
	if (getScorePlayer() == 0 && getScoreBot() == 0) {
		if (this->selected_index - 1 >= 2) {
			this->menu[this->selected_index].setCharacterSize(32U);
			this->menu[this->selected_index].move(move_step, move_step);
			this->menu[this->selected_index].setFillColor(sf::Color(BRIGHT));

			this->selected_index--;
			this->menu[this->selected_index].setCharacterSize(36U);
			this->menu[this->selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
			this->menu[this->selected_index].setFillColor(sf::Color(YELLOW));
		}
	}
	else {
		if (this->selected_index - 1 >= 1) {
			this->menu[this->selected_index].setCharacterSize(32U);
			this->menu[this->selected_index].move(move_step, move_step);
			this->menu[this->selected_index].setFillColor(sf::Color(BRIGHT));

			this->selected_index--;
			this->menu[this->selected_index].setCharacterSize(36U);
			this->menu[this->selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
			this->menu[this->selected_index].setFillColor(sf::Color(YELLOW));
		}
	}


}
void StateMenu::move_down() {
	if (this->selected_index + 1 < MAX_NUBER_OF_ITEMS_MENU_GENERAL) {
		this->menu[this->selected_index].setCharacterSize(32U);
		this->menu[this->selected_index].move(move_step, move_step);
		this->menu[this->selected_index].setFillColor(sf::Color(BRIGHT));

		this->selected_index++;
		this->menu[this->selected_index].setCharacterSize(36U);
		this->menu[this->selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->menu[this->selected_index].setFillColor(sf::Color(YELLOW));
	}
}

void StateMenu::event(sf::RenderWindow* window, sf::Event* event, State* state) {
	//KEYBOARD
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
		(isSelected) ? this->move_up() : this->select();
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
		(isSelected) ? this->move_down() : this->select();
	}

	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Enter && this->isSelected) {
		switch (this->selected_index)
		{
		case CONTINUE:
			state->setState(new StateGame(getTypeGame()));
			break;
		case PLAY:
			state->setState(new StateMenuPlayers());
			break;
		case OPTIONS:
			state->setState(new StateOptions());
			break;
		case EXIT:
			window->close();
			break;
		default:
			break;
		}
	}

	//MOUSE
	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
		if (menu[PLAY].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateMenuPlayers());
		}
		else if (menu[CONTINUE].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			if (getScorePlayer() != 0 || getScoreBot() != 0) {
				state->setState(new StateGame(getTypeGame()));
			}
		}
		else if (menu[OPTIONS].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateOptions());
		}
		else if (menu[EXIT].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			window->close();
		}
	}
}

void StateMenu::update(sf::RenderWindow* window, sf::Time* time, State* state) {

}

void StateMenu::render(sf::RenderWindow* window) {
	window->clear(sf::Color(DARK));

	window->draw(this->menu[TITLE]);
	if (getScorePlayer() != 0 || getScoreBot() != 0)
		window->draw(this->menu[CONTINUE]);
	window->draw(this->menu[PLAY]);
	window->draw(this->menu[OPTIONS]);
	window->draw(this->menu[EXIT]);
}

void StateMenu::clear() {
	delete[] this->menu;
	delete this->font;

	delete this->musicMenu;
}
//================================================================================================================================================================================================================================================================================================
void StateMenuPlayers::init() {
	this->font = new sf::Font();
	font->loadFromFile(FONT);

	this->vsChoice = new sf::Text[MAX_NUBER_OF_ITEMS_MENU_ADDITIONAL]();
	for (int i = 0; i < MAX_NUBER_OF_ITEMS_MENU_ADDITIONAL; i++) {
		this->vsChoice[i].setFont(*this->font);
		this->vsChoice[i].setFillColor(sf::Color(BRIGHT));
		this->vsChoice[i].setCharacterSize(32U);
	}
	this->vsChoice[TITLE].setString("PING PONG");
	this->vsChoice[TITLE].setCharacterSize(64U);
	this->vsChoice[TITLE].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->vsChoice[TITLE].getString().getSize())* this->vsChoice[TITLE].getCharacterSize() / 2), static_cast<float>(this->vsChoice[TITLE].getCharacterSize()));

	this->vsChoice[PLAYER].setString("PLAY vs PLAYER");
	this->vsChoice[PLAYER].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->vsChoice[PLAYER].getString().getSize())* this->vsChoice[PLAYER].getCharacterSize() / 2), DISPLAY_HEIGHT / 2 - static_cast<float>(this->vsChoice[PLAYER].getCharacterSize()) / 2);

	this->vsChoice[BOT].setString("PLAY vs BOT   ");
	this->vsChoice[BOT].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->vsChoice[BOT].getString().getSize())* this->vsChoice[BOT].getCharacterSize() / 2), this->vsChoice[PLAYER].getPosition().y + static_cast<float>(this->vsChoice[PLAYER].getCharacterSize()) + 10);

	this->vsChoice[MENU].setString("MENU");
	this->vsChoice[MENU].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (static_cast<float>(this->vsChoice[MENU].getString().getSize())* this->vsChoice[MENU].getCharacterSize() / 2), this->vsChoice[BOT].getPosition().y + static_cast<float>(this->vsChoice[BOT].getCharacterSize()) + 10);

	this->selected_index = 1;
	this->move_step = 4;
	this->isSelected = false;
}

void StateMenuPlayers::select() {
	this->isSelected = true;

	this->vsChoice[PLAYER].setCharacterSize(36U);
	this->vsChoice[PLAYER].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
	this->vsChoice[PLAYER].setFillColor(sf::Color(YELLOW));
}
void StateMenuPlayers::move_up() {
	if (this->selected_index - 1 >= 1) {
		this->vsChoice[this->selected_index].setCharacterSize(32U);
		this->vsChoice[this->selected_index].move(move_step, move_step);
		this->vsChoice[this->selected_index].setFillColor(sf::Color(BRIGHT));

		this->selected_index--;
		this->vsChoice[this->selected_index].setCharacterSize(36U);
		this->vsChoice[this->selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->vsChoice[this->selected_index].setFillColor(sf::Color(YELLOW));
	}
}
void StateMenuPlayers::move_down() {

	if (this->selected_index + 1 < MAX_NUBER_OF_ITEMS_MENU_ADDITIONAL) {
		this->vsChoice[this->selected_index].setCharacterSize(32U);
		this->vsChoice[this->selected_index].move(move_step, move_step);
		this->vsChoice[this->selected_index].setFillColor(sf::Color(BRIGHT));

		this->selected_index++;
		this->vsChoice[this->selected_index].setCharacterSize(36U);
		this->vsChoice[this->selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->vsChoice[this->selected_index].setFillColor(sf::Color(YELLOW));
	}
}

void StateMenuPlayers::event(sf::RenderWindow* window, sf::Event* event, State* state)
{
	//KEYBOARD
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
		(isSelected) ? this->move_up() : this->select();
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
		(isSelected) ? this->move_down() : this->select();
	}

	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Enter && this->isSelected) {
		switch (this->selected_index)
		{
		case PLAYER:
			setScorePlayer(0);
			setScoreBot(0);
			state->setState(new StateGame(false));
			break;
		case BOT:
			setScorePlayer(0);
			setScoreBot(0);
			state->setState(new StateGame(true));
			break;
		case MENU:
			state->setState(new StateMenu());
			break;
		default:
			break;
		}
	}

	//MOUSE
	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
		if (vsChoice[PLAYER].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setScorePlayer(0);
			setScoreBot(0);
			state->setState(new StateGame(false));
		}
		else if (vsChoice[BOT].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setScorePlayer(0);
			setScoreBot(0);
			state->setState(new StateGame(true));
		}
		else if (vsChoice[MENU].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateMenu());
		}
	}
}

void StateMenuPlayers::update(sf::RenderWindow* window, sf::Time* time, State* state)
{
}

void StateMenuPlayers::render(sf::RenderWindow* window)
{
	window->clear(sf::Color(DARK));

	for (int i = 0; i < MAX_NUBER_OF_ITEMS_MENU_ADDITIONAL; i++) {
		window->draw(this->vsChoice[i]);
	}
}

void StateMenuPlayers::clear()
{
	delete[] this->vsChoice;
	delete this->font;
}