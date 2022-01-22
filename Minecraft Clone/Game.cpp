#include "Game.h"


void Game::initialize() {
	world.generate();
}

void Game::update(float dt) {

}

void Game::render(Shader* currentShader) {
	world.render(currentShader);
}
