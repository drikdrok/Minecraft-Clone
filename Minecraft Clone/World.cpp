#include "World.h"
#include "Game.h"
#include "Camera.h"
#include <stdlib.h>

#include "Mesh.h"

Cube cube;


glm::vec3 blockToChunkCoords(int x, int y, int z);

int signOf(int x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}


void World::generate() {
	cube.initialize();

	
}

int World::getBlock(int x, int y, int z) {
	if (!chunkExists(glm::vec3(x, y, z)))
		return -1;

	return getChunk(getChunkOfBlock(glm::vec3(x, y, z)))->getBlock(x, y, z);
}

void World::setBlock(int x, int y, int z, int type) {
	getChunk(getChunkOfBlock(game->camera->lookingAt))->setBlock(x, y, z, type);
	getChunk(getChunkOfBlock(game->camera->lookingAt))->generateMesh();
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

bool World::chunkExists(glm::vec3 position) {
	for (auto& v : this->chunks) {
		if (v->position == position) {
			return true;
		}
	}

	return false;
}


glm::vec3 World::getChunkOfBlock(glm::vec3 block) {
	int x = block.x;
	int y = block.y;
	int z = block.z;

	glm::vec3 coords = blockToChunkCoords(x, y, z);
	
	if (x >= 0)
		x -= x % 16;
	else
		x -= coords.x;

	if (y >= 0)
		y -= y % 16;
	else
		y -= coords.y;
	
	if (z >= 0)
		z -= z % 16;
	else
		z -= coords.z;

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

	generateMesh();
}

void Chunk::generateMesh() {
	mesh.reset();
	for (int x = 0; x < this->size; x++) {
		for (int y = 0; y < this->size; y++) {
			for (int z = 0; z < this->size; z++) {
				if (this->blocks[x][y][z] != 0) {
					if (game->world->getBlock(x - 1, y, z) <= 0)
						mesh.addWestFace(x, y, z);

					if (game->world->getBlock(x + 1, y, z) <= 0)
						mesh.addEastFace(x, y, z);

					if (game->world->getBlock(x, y + 1, z) <= 0)
						mesh.addTopFace(x, y, z);

					if (game->world->getBlock(x, y - 1, z) <= 0)
						mesh.addBottomFace(x, y, z);

					if (game->world->getBlock(x, y , z+1) <= 0)
						mesh.addNorthFace(x, y, z);

					if (game->world->getBlock(x, y , z-1) <= 0)
						mesh.addBottomFace(x, y, z);

					//mesh.addTopFace(x, y, z);


				}
			}
		}
	}
	mesh.setupMesh();

}

void Chunk::render(Shader* currentShader) {
	currentShader->setFloat("brightness", 1.0f);

	for (int x = 0; x < this->size; x++) {
		for (int y = 0; y < this->size; y++) {
			for (int z = 0; z < this->size; z++) {
				if (this->blocks[x][y][z] != 0) {
					if (glm::vec3(position.x + x, position.y + y, position.z + z) == game->camera->lookingAt)
						currentShader->setFloat("brightness", 1.5f);

					cube.render(blocks[x][y][z], glm::vec3(x + position.x*16, position.y + y, position.z + z), currentShader);


					currentShader->setFloat("brightness", 1.0f);
				}
			}
		}
	}

	//mesh.render(1, position, currentShader);
}


int Chunk::getBlock(int x, int y, int z) {
	glm::vec3 coords = blockToChunkCoords(x, y, z);

	x = coords.x;
	y = coords.y;
	z = coords.z;

	x = abs(x);
	y = abs(y);
	z = abs(z);

	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size) //Todo: allow negative coordinates
		return -1;

	return this->blocks[x][y][z];
}
void Chunk::setBlock(int x, int y, int z, int type) {

	glm::vec3 coords = blockToChunkCoords(x, y, z);

	x = coords.x;
	y = coords.y;
	z = coords.z;

	//std::cout << "Block-Chunk Coords: " << x << ", " << y << ", " << z << std::endl;

	x = abs(x);
	y = abs(y);
	z = abs(z);

	if (x < 0 || y < 0 || z < 0 || x > this->size || y > this->size || z > this->size)
		return;


	this->blocks[x][y][z] = type;
}


glm::vec3 blockToChunkCoords(int x, int y, int z) {
	if (x >= 0)
		x = x % 16;
	else
		x = 16 + (x % 16);

	if (y >= 0)
		y = y % 16;
	else
		y = 16 + (y % 16);

	if (z >= 0)
		z = z % 16;
	else
		z = 16 + (z % 16);

	if (x == 16) x = 0;
	if (y == 16) y = 0;
	if (z == 16) z = 0;

	return glm::vec3(x, y, z);
}