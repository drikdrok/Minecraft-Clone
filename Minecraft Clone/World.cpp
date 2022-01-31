#include "World.h"
#include "Game.h"
#include "Camera.h"

Cube cube;

void World::generate() {
	cube.initialize();

	for (int x = 0; x < this->size; x++) {
		for (int z = 0; z < this->size; z++) {
			this->blocks[x][7][z] = 1;
		}
	}
}

int World::getBlock(int x, int y, int z) {
	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size) //Todo: allow negative coordinates
		return -1;

	return this->blocks[x][y][z];
}

void World::setBlock(int x, int y, int z, int type) {
	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size)
		return;

	this->blocks[x][y][z] = type;
}

void World::render(Shader* currentShader) {

	currentShader->setFloat("brightness", 1.0f);

	for (int x = 0; x < this->size; x++) {
		for (int y = 0; y < this->size; y++) {
			for (int z = 0; z < this->size; z++) {
				if (this->blocks[x][y][z] != 0) {
					if (glm::vec3(x, y, z) == game->camera->lookingAt)
						currentShader->setFloat("brightness", 1.5f);
					
					cube.render(blocks[x][y][z], glm::vec3(x, y, z), currentShader);

					currentShader->setFloat("brightness", 1.0f);
				}
			}
		}
	}
}