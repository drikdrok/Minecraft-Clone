#include "World.h"

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
	for (int x = 0; x < this->size; x++) {
		for (int y = 0; y < this->size; y++) {
			for (int z = 0; z < this->size; z++) {
				if (this->blocks[x][y][z] != 0)
					cube.render(1, glm::vec3(x, y, z), currentShader);
			}
		}
	}
}