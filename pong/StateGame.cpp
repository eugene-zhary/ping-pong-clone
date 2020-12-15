#pragma once
#include "StateGame.h"

StateGame::StateGame() {
	this->isBot = true;
}
StateGame::StateGame(bool isBot) :isBot(isBot) {}

void StateGame::init() {
	//GAME PART
	setTypeGame(this->isBot);
	this->font = new sf::Font();
	this->font->loadFromFile(FONT);

	this->scorePlayer = new Score(getScorePlayer(), *this->font, 32U);
	this->scorePlayer->setPosition(static_cast<float>(DISPLAY_WIDTH) / 4 - (this->scorePlayer->getCharacterSize() / 2), 25);
	this->scoreBot = new Score(getScoreBot(), *this->font, 32U);
	this->scoreBot->setPosition((static_cast<float>(DISPLAY_WIDTH) / 4) * 3 - (this->scoreBot->getCharacterSize() / 2), 25);

	this->player = new Player();
	this->bot = new PlayerBot(this->isBot);
	this->boundsTop = new Bounds(0, 0);
	this->boundsBot = new Bounds(0, static_cast<double>(DISPLAY_HEIGHT) - 10);

	this->ball = new Ball(this->player, this->bot, this->scorePlayer, this->scoreBot, this->boundsTop, this->boundsBot);

	//PAUSE PART
	this->pause = false;

	this->pauseBackground = new sf::RectangleShape[2]();
	this->pauseBackground[0].setSize(sf::Vector2f(384, 250));
	this->pauseBackground[1].setSize(sf::Vector2f(364, 230));

	this->pauseBackground[0].setFillColor(sf::Color(BRIGHT));
	this->pauseBackground[1].setFillColor(sf::Color(DARK));
	this->pauseBackground[0].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->pauseBackground->getSize().x / 2), (static_cast<float>(DISPLAY_HEIGHT) / 2) - (this->pauseBackground->getSize().y / 2));
	this->pauseBackground[1].setPosition(this->pauseBackground[0].getPosition().x + 10, this->pauseBackground[0].getPosition().y + 10);

	this->selected_index = 1;
	this->move_step = 4;

	this->pause_text = new sf::Text[MAX_NUBER_OF_ITEMS_PAUSE]();

	for (int i = 0; i < MAX_NUBER_OF_ITEMS_PAUSE; i++) {
		this->pause_text[i].setFont(*this->font);
		this->pause_text[i].setFillColor(sf::Color(BRIGHT));
	}

	this->pause_text[TITLE].setString("PAUSED");
	this->pause_text[TITLE].setCharacterSize(48U);
	this->pause_text[TITLE].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->pause_text[TITLE].getString().getSize() * this->pause_text[TITLE].getCharacterSize() / 2), this->pauseBackground->getPosition().y + this->pause_text[TITLE].getCharacterSize());

	this->pause_text[RESUME].setString("RESUME");
	this->pause_text[RESUME].setCharacterSize(32U);
	this->pause_text[RESUME].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->pause_text[RESUME].getString().getSize() * this->pause_text[RESUME].getCharacterSize() / 2), this->pauseBackground->getPosition().y + this->pause_text[TITLE].getCharacterSize() * 3);

	this->pause_text[MENU].setString("MENU");
	this->pause_text[MENU].setCharacterSize(32U);
	this->pause_text[MENU].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->pause_text[MENU].getString().getSize() * this->pause_text[MENU].getCharacterSize() / 2), this->pause_text[RESUME].getPosition().y + static_cast<float>(this->pause_text[RESUME].getCharacterSize()) + 10);

	this->isSelected = false;

	this->pauseRect = new sf::RectangleShape(sf::Vector2f(64, 36));
	this->pauseRect->setFillColor(sf::Color(BRIGHT));
	this->pauseRect->setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->pauseRect->getSize().x / 2), 25);

	this->pause_symbol = new sf::Text("||", *this->font, 32U);
	this->pause_symbol->setFillColor(sf::Color(DARK));
	this->pause_symbol->setPosition(this->pauseRect->getPosition().x, this->pauseRect->getPosition().y + 4);

	//MUSIC PART
	this->gameMusic = new sf::Music();
	gameMusic->openFromFile(AUDIO_GAME);
	gameMusic->setVolume(static_cast<float>(getMusicVolume()));
	gameMusic->play();
}

void StateGame::select() {
	this->isSelected = true;

	this->pause_text[RESUME].setCharacterSize(36U);
	this->pause_text[RESUME].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
	this->pause_text[RESUME].setFillColor(sf::Color(YELLOW));
}
void StateGame::unselect()
{
	this->isSelected = false;

	this->pause_text[RESUME].setCharacterSize(32U);
	this->pause_text[RESUME].move(move_step, move_step);
	this->pause_text[RESUME].setFillColor(sf::Color(BRIGHT));
}
void StateGame::move_up() {
	if (selected_index - 1 >= 1) {
		this->pause_text[selected_index].setCharacterSize(32U);
		this->pause_text[selected_index].move(move_step, move_step);
		this->pause_text[selected_index].setFillColor(sf::Color(BRIGHT));

		selected_index--;
		this->pause_text[selected_index].setCharacterSize(36U);
		this->pause_text[selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->pause_text[selected_index].setFillColor(sf::Color(YELLOW));
	}
}
void StateGame::move_down() {
	if (selected_index + 1 < MAX_NUBER_OF_ITEMS_PAUSE) {
		this->pause_text[selected_index].setCharacterSize(32U);
		this->pause_text[selected_index].move(move_step, move_step);
		this->pause_text[selected_index].setFillColor(sf::Color(BRIGHT));

		selected_index++;
		this->pause_text[selected_index].setCharacterSize(36U);
		this->pause_text[selected_index].move(static_cast<float>(-move_step), static_cast<float>(-move_step));
		this->pause_text[selected_index].setFillColor(sf::Color(YELLOW));
	}
}

void StateGame::event(sf::RenderWindow* window, sf::Event* event, State* state) {
	//KEYBOARD
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Space) {
		this->pause = true;
		this->gameMusic->pause();
	}

	if (this->pause) {
		if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
			(isSelected) ? this->move_up() : this->select();
		}
		else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
			(isSelected) ? this->move_down() : this->select();
		}

		if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Enter && this->isSelected) {
			switch (selected_index)
			{
			case RESUME:
				this->pause = false;
				this->unselect();
				this->gameMusic->play();
				break;
			case MENU:
				state->setState(new StateMenu());
				break;
			}
		}

		//MOUSE
		if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
			if (this->pause_text[RESUME].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
				this->pause = false;
				this->gameMusic->play();
			}
			else if (this->pause_text[MENU].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
				state->setState(new StateMenu());
			}
		}
	}
	if (!this->pause) {
		if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
			if (this->pauseRect->getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
				this->pause = true;
				this->gameMusic->pause();
			}
		}
	}
}

void StateGame::update(sf::RenderWindow* window, sf::Time* time, State* state) {
	if (!this->pause) {
		this->player->update(window, time->asSeconds());
		this->bot->update(time->asSeconds(), *this->ball);
		this->ball->update(time->asSeconds());
		this->scorePlayer->update();
		this->scoreBot->update();
	}

	if (this->scorePlayer->getValue() == 3) {
		setScorePlayer(0);
		setScoreBot(0);
		state->setState(new StateGameEnd(this->isBot, true));
	}
	if (this->scoreBot->getValue() == 3) {
		setScorePlayer(0);
		setScoreBot(0);
		state->setState(new StateGameEnd(this->isBot, false));
	}
}

void StateGame::render(sf::RenderWindow* window) {
	window->clear(sf::Color(DARK));
	window->draw(*this->player);
	window->draw(*this->bot);
	window->draw(*this->boundsTop);
	window->draw(*this->boundsBot);
	window->draw(*this->ball);
	window->draw(*this->scorePlayer);
	window->draw(*this->scoreBot);
	window->draw(*this->pauseRect);
	window->draw(*this->pause_symbol);
	if (this->pause) {
		for (int i = 0; i < 2; i++)
			window->draw(this->pauseBackground[i]);
		for (int i = 0; i < MAX_NUBER_OF_ITEMS_PAUSE; i++)
			window->draw(this->pause_text[i]);
	}
}

void StateGame::clear() {
	delete this->gameMusic;

	delete this->ball;
	delete this->player;
	delete this->bot;
	delete this->scorePlayer;
	delete this->scoreBot;
	delete this->boundsTop;
	delete this->boundsBot;

	delete[] this->pause_text;
	delete[] this->pauseBackground;
	delete this->pauseRect;
	delete this->pause_symbol;

	delete this->font;
}