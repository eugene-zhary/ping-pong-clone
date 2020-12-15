#include "StateOptions.h"

void StateOptions::init() {
	this->selected_index_general = 0;
	this->selected_index_additional = 0;
	this->isSelected = false;
	this->move_step = 4;

	this->font = new sf::Font();
	font->loadFromFile(FONT);

	this->options = new sf::Text[MAX_NUBER_OF_ITEMS_OPTIONS]();
	for (int i = 0; i < MAX_NUBER_OF_ITEMS_OPTIONS; i++) {
		this->options[i].setFont(*this->font);
		this->options[i].setFillColor(sf::Color(BRIGHT));
	}
	this->options[SOUND].setCharacterSize(32U);
	this->options[SOUND].setString("GAME SOUND");
	this->options[SOUND].setPosition(100, 100);

	this->options[MUSIC].setCharacterSize(32U);
	this->options[MUSIC].setString("MUSIC");
	this->options[MUSIC].setPosition(100, this->options[SOUND].getPosition().y + this->options[SOUND].getCharacterSize() + 10);

	this->options[CONTROL].setCharacterSize(32U);
	this->options[CONTROL].setString("CONTROL");
	this->options[CONTROL].setPosition(100, this->options[MUSIC].getPosition().y + this->options[MUSIC].getCharacterSize() + 10);

	this->options[MENU].setCharacterSize(32U);
	this->options[MENU].setString("MENU");
	this->options[MENU].setPosition((static_cast<float>(DISPLAY_WIDTH) / 2) - (this->options[MENU].getCharacterSize() * this->options[MENU].getString().getSize() / 2), this->options[CONTROL].getPosition().y + this->options[CONTROL].getCharacterSize() * 2);


	this->values = new sf::Text[3]();
	for (int i = 0; i < 3; i++) {
		this->values[i].setFont(*this->font);
		this->values[i].setCharacterSize(32U);
		this->values[i].setFillColor(sf::Color(BRIGHT));
		this->values[i].setPosition(static_cast<float>(DISPLAY_WIDTH) - 100 - this->values[i].getCharacterSize() * 4, this->options[i].getPosition().y);
	}
	this->values[0].setString(std::to_string(getSoundVolume()));
	this->values[1].setString(std::to_string(getMusicVolume()));

	this->values[2].setPosition(static_cast<float>(DISPLAY_WIDTH) - 100 - this->values[2].getCharacterSize() * 6, this->options[2].getPosition().y);
	(getControl()) ? this->values[2].setString("KEYBOARD") : this->values[2].setString("MOUSE");


	this->plus = new sf::RectangleShape[2]();
	this->minus = new sf::RectangleShape[2]();
	for (int i = 0; i < 2; i++) {
		this->plus[i].setSize(sf::Vector2f(32, 32));
		this->plus[i].setPosition(this->values[i].getPosition().x + this->values[i].getCharacterSize() * 3 + 10, this->values[i].getPosition().y);
		this->plus[i].setFillColor(sf::Color(BRIGHT));

		this->minus[i].setSize(sf::Vector2f(32, 32));
		this->minus[i].setPosition(this->values[i].getPosition().x - 42, this->values[i].getPosition().y);
		this->minus[i].setFillColor(sf::Color(BRIGHT));
	}

	this->text_plus = new sf::Text[2]();
	this->text_minus = new sf::Text[2]();
	for (int i = 0; i < 2; i++) {
		this->text_plus[i].setFont(*this->font);
		this->text_plus[i].setCharacterSize(32);
		this->text_plus[i].setFillColor(sf::Color(DARK));
		this->text_plus[i].setString("+");
		this->text_plus[i].setPosition(this->plus[i].getPosition());

		this->text_minus[i].setFont(*this->font);
		this->text_minus[i].setCharacterSize(32);
		this->text_minus[i].setFillColor(sf::Color(DARK));
		this->text_minus[i].setString("-");
		this->text_minus[i].setPosition(this->minus[i].getPosition());
	}

	this->description = new sf::Text();
	this->description->setFont(*this->font);
	this->description->setCharacterSize(32U);
	this->description->setFillColor(sf::Color(BRIGHT));
	this->description->setPosition(100, this->options[MENU].getPosition().y + this->options[MENU].getCharacterSize() * 3);
	this->description->setString("\tGAME CONTROL:\n\nmove up   - W/UP\nmove down - S/DOWN\npause     - SPACE");
}

void StateOptions::select() {
	this->isSelected = true;

	this->options[SOUND].setCharacterSize(36U);
	this->options[SOUND].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
	this->options[SOUND].setFillColor(sf::Color(YELLOW));
}
void StateOptions::move_up() {
	if (this->selected_index_general - 1 >= 0) {
		this->options[this->selected_index_general].setCharacterSize(32U);
		this->options[this->selected_index_general].move(static_cast<float>(this->move_step), static_cast<float>(this->move_step));
		this->options[this->selected_index_general].setFillColor(sf::Color(BRIGHT));

		this->selected_index_general--;
		this->options[this->selected_index_general].setCharacterSize(36U);
		this->options[this->selected_index_general].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
		this->options[this->selected_index_general].setFillColor(sf::Color(YELLOW));
	}
}
void StateOptions::move_down() {
	if (this->selected_index_general + 1 < MAX_NUBER_OF_ITEMS_OPTIONS) {
		this->options[this->selected_index_general].setCharacterSize(32U);
		this->options[this->selected_index_general].move(static_cast<float>(this->move_step), static_cast<float>(this->move_step));
		this->options[this->selected_index_general].setFillColor(sf::Color(BRIGHT));

		this->selected_index_general++;
		this->options[this->selected_index_general].setCharacterSize(36U);
		this->options[this->selected_index_general].move(static_cast<float>(-this->move_step), static_cast<float>(-this->move_step));
		this->options[this->selected_index_general].setFillColor(sf::Color(YELLOW));
	}
}

void StateOptions::event(sf::RenderWindow* window, sf::Event* event, State* state) {

	//KEYBOARD
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
		(isSelected) ? this->move_up() : this->select();
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
		(isSelected) ? this->move_down() : this->select();
	}

	//sound
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Right && this->selected_index_general == SOUND && this->isSelected)
	{
		setSoundVolume(getSoundVolume() + 5);
		this->values[0].setString(std::to_string(getSoundVolume()));
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Left && this->selected_index_general == SOUND && this->isSelected)
	{
		setSoundVolume(getSoundVolume() - 5);
		this->values[0].setString(std::to_string(getSoundVolume()));
	}
	//music
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Right && this->selected_index_general == MUSIC && this->isSelected)
	{
		setMusicVolume(getMusicVolume() + 5);
		this->values[1].setString(std::to_string(getMusicVolume()));
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Left && this->selected_index_general == MUSIC && this->isSelected)
	{
		setMusicVolume(getMusicVolume() - 5);
		this->values[1].setString(std::to_string(getMusicVolume()));
	}
	//control
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Right && this->selected_index_general == CONTROL && this->isSelected)
	{
		setControl(true);
		this->values[2].setString("KEYBOARD");
	}
	else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Left && this->selected_index_general == CONTROL && this->isSelected)
	{
		setControl(false);
		this->values[2].setString("MOUSE");
	}
	//menu
	if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Enter && this->selected_index_general == MENU && this->isSelected)
		state->setState(new StateMenu());


	//MOUSE

	if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
		if (this->minus[SOUND].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setSoundVolume(getSoundVolume() - 5);
			this->values[0].setString(std::to_string(getSoundVolume()));
		}
		else if (this->minus[MUSIC].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setMusicVolume(getMusicVolume() - 5);
			this->values[1].setString(std::to_string(getMusicVolume()));
		}
		else if (this->values[CONTROL].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			(getControl()) ? (setControl(false), this->values[2].setString("MOUSE")) : (setControl(true), this->values[2].setString("KEYBOARD"));
		}
		else if (this->plus[SOUND].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setSoundVolume(getSoundVolume() + 5);
			this->values[0].setString(std::to_string(getSoundVolume()));
		}
		else if (this->plus[MUSIC].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			setMusicVolume(getMusicVolume() + 5);
			this->values[1].setString(std::to_string(getMusicVolume()));
		}
		else if (this->options[MENU].getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
			state->setState(new StateMenu());
		}
	}
}

void StateOptions::update(sf::RenderWindow* window, sf::Time* time, State* state) {

}

void StateOptions::render(sf::RenderWindow* window) {
	window->clear(sf::Color(DARK));
	for (int i = 0; i < MAX_NUBER_OF_ITEMS_OPTIONS; i++)
		window->draw(this->options[i]);

	for (int i = 0; i < 3; i++)
	{
		window->draw(this->values[i]);
	}
	for (int i = 0; i < 2; i++) {
		window->draw(this->plus[i]);
		window->draw(this->minus[i]);
		window->draw(this->text_plus[i]);
		window->draw(this->text_minus[i]);
	}

	window->draw(*this->description);
}

void StateOptions::clear() {
	delete this->description;
	delete[] this->text_minus;
	delete[] this->text_plus;
	delete[] this->plus;
	delete[] this->minus;
	delete[] this->values;
	delete[] this->options;
	delete this->font;
}