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

	void update(float dt);
};

