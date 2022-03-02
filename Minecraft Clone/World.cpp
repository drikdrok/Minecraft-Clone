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
	//std::cout << "Look: " << game->camera->lookingAt.x << ", " << game->camera->lookingAt.y << ", " << game->camera->lookingAt.z << ";    Chunk: " << lookingAtCoords1.x << ", " << lookingAtCoords1.y << ", " << lookingAtCoords1.z << ";     Relative: " << lookingAtCoords2.x << ", " << lookingAtCoords2.y << ", " << lookingAtCoords2.z << std::endl;


	for (int x = -renderDistance; x < renderDistance; x++) {
		for (int y = -renderDistance; y < renderDistance; y++) {
			for (int z = -renderDistance; z < renderDistance; z++) {
				if (!chunkExists(glm::vec3(playerChunk.x + x, playerChunk.y + y, playerChunk.z + z))) {
					chunks.push_back(new Chunk(this->game, glm::vec3(playerChunk.x + x, playerChunk.y + y, playerChunk.z + z), 1));
				}
			}
		}
	}


	/*int amountToUpdate = (chunkUpdates.size() > 1) ? 1 : chunkUpdates.size();
	for (int i = 0; i < amountToUpdate; i++) {
		Chunk* c = chunkUpdates.front();
		chunkUpdates.pop_front();
		c->generateMesh();
	}
	*/

	if (chunkUpdates.size() > 0) {
		Chunk* c = chunkUpdates.front();
		chunkUpdates.pop_front();
		c->generateMesh();
	}
}

bool World::chunkExists(glm::vec3 position) {
	for (auto& chunk : chunks)
		if (chunk->position == position)
			return true;

	return false;
}

Chunk* World::getChunk(glm::vec3 position) {
	for (Chunk* chunk : chunks)
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

void World::addChunkUpdate(Chunk* c) {

	//Check to make sure chunk is not already in deque
	std::deque<Chunk*>::iterator it = std::find(chunkUpdates.begin(), chunkUpdates.end(), c);
	if (it == chunkUpdates.end())
		chunkUpdates.push_back(c);
}

int World::getHeightOfBlock(int x, int z) {
	return abs(floor(noise.GetNoise((float)x, (float)z) * 30));
}





//CHUNK


void Chunk::generate() {
	/*for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			for (int z = 0; z < size; z++) {
				if (y == 7)
					blocks[x][y][z] = std::rand() % 6+2;
			}
		}
	}
	*/

	for (int x = 0; x < size; x++) {
		for (int z = 0; z < size; z++) {
			int heightGlobal = game->world->getHeightOfBlock(abs(position.x * 16 + x), abs(position.z * 16 + z)) ;
			int heightRelative = heightGlobal - position.y * 16;
			
			if (heightRelative < 0)
				continue;
			
			
			for (int y = (heightRelative > 15) ? 15 : heightRelative; y >= 0; y--) {
				int block = (heightGlobal > 5) ? 2 : 7;

				if (y < heightRelative - 4)
					block = 1;
				else if (y < heightRelative)
					block = 3;

				blocks[x][y][z] = block;
			}
		}
	}

	//generateMesh();
	game->world->addChunkUpdate(this);
}

void Chunk::generateMesh() {
	mesh.reset();

	//float timeStart = static_cast<float>(glfwGetTime());

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			for (int z = 0; z < size; z++) {
				if (blocks[x][y][z] != 0) {
					if (getBlock(glm::vec3(x - 1, y, z)) <= 0)
						mesh.addWestFace(x, y, z, blocks[x][y][z], 1.0f);

					if (getBlock(glm::vec3(x + 1, y, z)) <= 0)
						mesh.addEastFace(x, y, z, blocks[x][y][z], 1.0f);

					if (getBlock(glm::vec3(x, y + 1, z)) <= 0)
						mesh.addTopFace(x, y, z, blocks[x][y][z], 1.0f);

					if (getBlock(glm::vec3(x, y - 1, z)) <= 0)
						mesh.addBottomFace(x, y, z, blocks[x][y][z], 1.0f);

					if (getBlock(glm::vec3(x, y, z + 1)) <= 0)
						mesh.addNorthFace(x, y, z, blocks[x][y][z], 1.0f);

					if (getBlock(glm::vec3(x, y, z - 1)) <= 0)
						mesh.addSouthFace(x, y, z, blocks[x][y][z], 1.0f);

					//mesh.addBottomFace(x, y, z);
				}
			}
		}
	}

	//std::cout << "Time to generate mesh: " << static_cast<float>(glfwGetTime()) - timeStart << std::endl;
	//timeStart = static_cast<float>(glfwGetTime());

	mesh.setupMesh();

	//std::cout << "Time to setup mesh: " << static_cast<float>(glfwGetTime()) - timeStart << std::endl;

}

void Chunk::render(Shader* currentShader) {
	//currentShader->setFloat("brightness", 1.0f);

	mesh.render(glm::vec3(position.x * 16, position.y * 16, position.z * 16), currentShader);

}


int Chunk::getBlock(glm::vec3 p) {
	if (p.x < 0 || p.x > 15 || p.y < 0 || p.y > 15 || p.z < 0 || p.z > 15)
		return game->world->getBlock(glm::vec3(position.x * 16 + p.x, position.y * 16 + p.y, position.z * 16 + p.z));

	return blocks[(int)p.x][(int)p.y][(int)p.z];
}

void Chunk::setBlock(glm::vec3 position, int type) {
	blocks[(int)position.x][(int)position.y][(int)position.z] = type;
	
	generateMesh();

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			for (int z = -1; z <= 1; z++) {
				if (game->world->chunkExists(glm::vec3(this->position.x + x, this->position.y + y, this->position.z + z))) {
					 //game->world->getChunk(glm::vec3(position.x + x, position.y + y, position.z + z))->generateMesh();
					game->world->addChunkUpdate(game->world->getChunk(glm::vec3(this->position.x + x, this->position.y + y, this->position.z + z)));
				}
			}
		}
	}
}