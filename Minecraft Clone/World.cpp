#include "World.h"
#include "Game.h"
#include "Camera.h"


glm::vec3 positionToChunk(glm::vec3 position) {
	return glm::vec3(floor(position.x / 16), floor(position.y / 16), floor(position.z / 16));
}

glm::vec3 positionToRelativeChunkCoords(glm::vec3 position) {
	int x = (position.x >= 0) ? ((int)position.x % 16) : (((int)position.x % 16 == 0) ? 0 : 16 + ((int)position.x % 16));
	int y = (position.y >= 0) ? ((int)position.y % 16) : (((int)position.y % 16 == 0) ? 0 : 16 + ((int)position.y % 16));
	int z = (position.z >= 0) ? ((int)position.z % 16) : (((int)position.z % 16 == 0) ? 0 : 16 + ((int)position.z % 16));

	return glm::vec3(x, y, z);
}	



void World::generate() {
	chunks.push_back(new Chunk(this->game, glm::vec3(0,0,0), 1));
}

void World::render(Shader* currentShader) {
	glm::vec3 playerChunk = positionToChunk(game->camera->Position);
	for (int x = -renderDistance; x < renderDistance; x++) {
		for (int y = -renderDistance; y < renderDistance; y++) {
			for (int z = -renderDistance; z < renderDistance; z++) {
				getChunk(glm::vec3(playerChunk.x + x, playerChunk.y + y, playerChunk.z + z))->render(currentShader);
			}
		}
	}
}

void World::update() {
	glm::vec3 playerChunk = positionToChunk(game->camera->Position);
	glm::vec3 lookingAtCoords1 = positionToChunk(game->camera->lookingAt);
	glm::vec3 lookingAtCoords2 = positionToRelativeChunkCoords(game->camera->lookingAt);
	//std::cout << "PlayerChunk: " << playerChunk.x << ", " << playerChunk.y << ", " << playerChunk.z << std::endl;
	std::cout << "Look: " << game->camera->lookingAt.x << ", " << game->camera->lookingAt.y << ", " << game->camera->lookingAt.z << ";    Chunk: " << lookingAtCoords1.x << ", " << lookingAtCoords1.y << ", " << lookingAtCoords1.z << ";     Relative: " << lookingAtCoords2.x << ", " << lookingAtCoords2.y << ", " << lookingAtCoords2.z << std::endl;


	for (int x = -renderDistance; x < renderDistance; x++) {
		for (int y = -renderDistance; y < renderDistance; y++) {
			for (int z = -renderDistance; z < renderDistance; z++) {
				if (!chunkExists(glm::vec3(playerChunk.x + x, playerChunk.y + y, playerChunk.z + z))) {
					chunks.push_back(new Chunk(this->game, glm::vec3(playerChunk.x + x, playerChunk.y + y, playerChunk.z + z), 1));
				}
			}
		}
	}
}

bool World::chunkExists(glm::vec3 position) {
	for (auto& chunk : chunks)
		if (chunk->position == position)
			return true;

	return false;
}

Chunk* World::getChunk(glm::vec3 position) {
	for (auto& chunk : chunks)
		if (chunk->position == position)
			return chunk;
}



int World::getBlock(glm::vec3 position) {
	if (!chunkExists(positionToChunk(position)))
		return -1;

	Chunk* c = getChunk(positionToChunk(position));
	return c->getBlock(positionToRelativeChunkCoords(position));
}

void World::setBlock(glm::vec3 position, int type) {
	Chunk* c = getChunk(positionToChunk(position));
	c->setBlock(positionToRelativeChunkCoords(position), type);
}





//CHUNK


void Chunk::generate() {
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			for (int z = 0; z < size; z++) {
				if (y == 7)
					blocks[x][y][z] = std::rand() % 6+2;
			}
		}
	}

	generateMesh();
}

void Chunk::generateMesh() {
	mesh.reset();


	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			for (int z = 0; z < size; z++) {
				if (blocks[x][y][z] != 0) {
					if (game->world->getBlock(glm::vec3(position.x * 16 + x - 1, position.y * 16 + y, position.z * 16 + z)) <= 0)
						mesh.addWestFace(x, y, z, blocks[x][y][z]);

					if (game->world->getBlock(glm::vec3(position.x * 16 + x + 1, position.y * 16 + y, position.z * 16 + z)) <= 0)
						mesh.addEastFace(x, y, z, blocks[x][y][z]);

					if (game->world->getBlock(glm::vec3(position.x * 16 + x, position.y * 16 + y + 1, position.z * 16 + z)) <= 0)
						mesh.addTopFace(x, y, z, blocks[x][y][z]);

					if (game->world->getBlock(glm::vec3(position.x * 16 + x, position.y * 16 + y - 1, position.z * 16 + z)) <= 0)
						mesh.addBottomFace(x, y, z, blocks[x][y][z]);

					if (game->world->getBlock(glm::vec3(position.x * 16 + x, position.y * 16 + y, position.z * 16 + z + 1)) <= 0)
						mesh.addNorthFace(x, y, z, blocks[x][y][z]);

					if (game->world->getBlock(glm::vec3(position.x * 16 + x, position.y * 16 + y, position.z * 16 + z - 1)) <= 0)
						mesh.addSouthFace(x, y, z, blocks[x][y][z]);

					//mesh.addBottomFace(x, y, z);
				}
			}
		}
	}
	mesh.setupMesh();
}

void Chunk::render(Shader* currentShader) {
	currentShader->setFloat("brightness", 1.0f);

	mesh.render(blocks[0][7][0], glm::vec3(position.x * 16, position.y * 16, position.z * 16), currentShader);

}


int Chunk::getBlock(glm::vec3 position) {
	return blocks[(int)position.x][(int)position.y][(int)position.z];
}

void Chunk::setBlock(glm::vec3 position, int type) {
	blocks[(int)position.x][(int)position.y][(int)position.z] = type;
	
	generateMesh();
}