#include "PingPong.h"

PingPong::PingPong() :window(sf::VideoMode(DISPLAY_WIDTH, DISPLAY_HEIGHT), "PING-PONG", sf::Style::Close)
{
	this->ico.loadFromFile(IMAGE_ICO);
	this->window.setIcon(ICO_WIDTH, ICO_HEIGHT, this->ico.getPixelsPtr());

	this->state.setWindow(&this->window);
	this->state.setState(new StateMenu());
}

void PingPong::run(int minimum_frame_per_seconds) {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
	while (window.isOpen()) {
		processEvents();

		timeSinceLastUpdate = clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
	}
}

void PingPong::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			this->window.close();
		}
		if (event.type == sf::Event::Resized) {
			this->window.setSize(sf::Vector2u(DISPLAY_WIDTH, DISPLAY_HEIGHT));
		}
		this->state.event(&event, &this->state);
	}
}

void PingPong::update(sf::Time time) {
	this->state.update(&time, &this->state);
}

void PingPong::render() {
	this->state.render();
	this->window.display();
}

PingPong::~PingPong()
{

}