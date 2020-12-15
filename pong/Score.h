#pragma once
#include "main.h"

class Score :public sf::Text {
private:
	unsigned short value;
public:
	Score(unsigned short value, sf::Font& font, unsigned short font_size);
	void incrementScore();
	void update();
	unsigned short getValue();
	~Score();
};