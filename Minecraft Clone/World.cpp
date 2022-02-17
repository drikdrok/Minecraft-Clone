#include "World.h"
#include "Game.h"
#include "Camera.h"
#include <stdlib.h>

Cube cube;



int signOf(int x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}


void World::generate() {
	cube.initialize();

	
}

int World::getBlock(int x, int y, int z) {
	return getChunk(getChunkOfBlock(game->camera->lookingAt))->getBlock(x, y, z);
}

void World::setBlock(int x, int y, int z, int type) {
	getChunk(getChunkOfBlock(game->camera->lookingAt))->setBlock(x, y, z, type);
	std::cout << "Chunk of block = " << getChunk(getChunkOfBlock(game->camera->lookingAt))->position.x << ", " << getChunk(getChunkOfBlock(game->camera->lookingAt))->position.y << ", " << getChunk(getChunkOfBlock(game->camera->lookingAt))->position.z << ", " << std::endl;
}

void World::render(Shader* currentShader) {

	glm::vec3 playerChunk = getChunk(getChunkOfBlock(game->player->getPosition()))->position;

	for (auto& v : chunks) {
		if (v->position.x >= playerChunk.x - renderDistance * 16 && v->position.x <= playerChunk.x + renderDistance * 16 &&
			v->position.y >= playerChunk.y - renderDistance * 16 && v->position.y <= playerChunk.y + renderDistance * 16 &&
			v->position.z >= playerChunk.z - renderDistance * 16 && v->position.z <= playerChunk.z + renderDistance * 16) {
			v->render(currentShader);
		}

		//v->render(currentShader);
	}

	//chunks[0]->render(currentShader);
}


void World::update() {
	glm::vec3 playerChunk = getChunk(getChunkOfBlock(game->camera->lookingAt))->position;

	for (int x = -renderDistance; x < renderDistance; x++) {
		for (int y = -renderDistance; y < renderDistance; y++) {
			for (int z = -renderDistance; z < renderDistance; z++) {
				getChunk(glm::vec3(playerChunk.x + x*16, playerChunk.y + y*16, playerChunk.z + z*16));
			}
		}
	}

	//std::cout << "Chunks: " << chunks.size() << std::endl;
}

Chunk* World::getChunk(glm::vec3 position) {
	for (auto& v : this->chunks) {
		if (v->position == position) {
			return v;
		}
	}

	//Chunk doesn't exist, create it
	Chunk* chunk = new Chunk(this->game, position, std::rand() % 7+1);
	this->chunks.push_back(chunk);


	return chunk;
}


glm::vec3 World::getChunkOfBlock(glm::vec3 block) {
	int x = block.x;
	int y = block.y;
	int z = block.z;
	
	if (x >= 0)
		x -= x % 16;
	else
		x = (ceil(x / 16) - 1) * 16;

	if (y >= 0)
		y -= y % 16;
	else
		y = (ceil(y / 16) - 1) * 16;
	
	if (z >= 0)
		z -= z % 16;
	else
		z = (ceil(z / 16) - 1) * 16;

	return glm::vec3(x, y, z);
}



//----------------------------------------------------------
//CHUNK
//----------------------------------------------------------

void Chunk::generate(int block) {
	for (int x = 0; x < this->size; x++) {
		for (int z = 0; z < this->size; z++) {
			this->setBlock(x, 7, z, block);
		}
	}
}

void Chunk::render(Shader* currentShader) {
	currentShader->setFloat("brightness", 1.0f);

	for (int x = 0; x < this->size; x++) {
		for (int y = 0; y < this->size; y++) {
			for (int z = 0; z < this->size; z++) {
				if (this->blocks[x][y][z] != 0) {
					if (glm::vec3(position.x + x, position.y + y, position.z + z) == game->camera->lookingAt)
						currentShader->setFloat("brightness", 1.5f);

					cube.render(blocks[x][y][z], glm::vec3(position.x + x, position.y + y, position.z + z), currentShader);

					currentShader->setFloat("brightness", 1.0f);
				}
			}
		}
	}
}


int Chunk::getBlock(int x, int y, int z) {
	if (x >= 0)
		x = x % 16;
	else
		x = (ceil(x / 16) - 1) * 16 - x;

	if (y >= 0)
		y = y % 16;
	else
		y = (ceil(y / 16) - 1) * 16 - y;

	if (z >= 0)
		z = z % 16;
	else
		z = (ceil(z / 16) - 1) * 16 - z;

	x = abs(x);
	y = abs(y);
	z = abs(z);

	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size) //Todo: allow negative coordinates
		return -1;

	return this->blocks[x][y][z];
}
void Chunk::setBlock(int x, int y, int z, int type) {

	if (x >= 0)
		x = x % 16;
	else
		x = (ceil(x / 16) - 1) * 16 - x;

	if (y >= 0)
		y = y % 16;
	else
		y = (ceil(y / 16) - 1) * 16 - y;

	if (z >= 0)
		z = z % 16;
	else
		z = (ceil(z / 16) - 1) * 16 - z;

	x = abs(x);
	y = abs(y);
	z = abs(z);

	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size)
		return;


	this->blocks[x][y][z] = type;
}