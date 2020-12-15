#include "PingPong.h"

int main() {
	srand(time(NULL));

	PingPong game;
	game.run(FPS);

	return 0;
}