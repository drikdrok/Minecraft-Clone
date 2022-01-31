#pragma once

class Game;


class Player
{
private:
	Game* game;

public:
	Player(Game* game){
		this->game = game;
	};

	int blockInHand = 1;

	void update(float dt);

	void scrollWheel(double yoffset);
};

