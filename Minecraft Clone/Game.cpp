#include "Game.h"
#include "Camera.h"


void Game::initialize(Camera* camera) {
	world = new World(this);
	world->generate();

	player = new Player(this);

	this->camera = camera;
}

void Game::update(float dt) {

}

void Game::render(Shader* currentShader) {
	world->render(currentShader);
}
