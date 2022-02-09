#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Game;


class Player
{
private:
	Game* game;

	glm::vec3 position;

public:
	Player(Game* game){
		this->game = game;
	};

	int blockInHand = 1;

	void update(float dt);

	void scrollWheel(double yoffset);

	glm::vec3 getPosition() { 
		return glm::vec3(floor(position.x), floor(position.y), floor(position.z));
	}
	void setPosition(glm::vec3 position) { this->position = position; }
};

