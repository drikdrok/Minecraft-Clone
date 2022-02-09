#pragma once

#include "shader.h"
#include "Cube.h"
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Game;
class Chunk;

class World
{
	public:
		World(Game* game) { 
			this->game = game;
			generate(); 
		}
		void generate();
		void render(Shader* currentShader);
		int getBlock(int x, int y, int z);
		void setBlock(int x, int y, int z, int type);

		void update();

		static const int size = 16;

	private:
		//int blocks[size][size][size] = { 0 };

		std::vector<Chunk*> chunks;

		Game* game;


		int renderDistance = 1;

		Chunk* getChunk(glm::vec3 position);
		glm::vec3 getChunkOfBlock(glm::vec3 block);



};


class Chunk {
public:

	Chunk(Game* game, glm::vec3 position, int block) {
		this->game = game;
		this->position = position;

		generate(block);
	}

	void generate(int block);
	void render(Shader* currentShader);
	int getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, int type);


	glm::vec3 position;



private:
	int blocks[16][16][16] = { 0 };

	int size = 16;


	Game* game;



};
