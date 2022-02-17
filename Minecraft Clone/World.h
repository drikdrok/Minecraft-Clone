#pragma once

#include "shader.h"
#include "Cube.h"
#include <vector>

#include "Mesh.h"

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
		}

		void generate();
		void render(Shader* currentShader);
		void update();

		int getBlock(glm::vec3 position);


		bool chunkExists(glm::vec3 position);

		Chunk* getChunk(glm::vec3 position);

		void setBlock(glm::vec3 position, int type);

	private:
		Game* game;

		int renderDistance = 2;




		std::vector<Chunk*> chunks;

};


class Chunk {
public:
	Chunk(Game* game, glm::vec3 position, int block) {
		this->game = game;
		this->position = position;

		generate();
	}


	void generate();
	void render(Shader* currentShader);

	int getBlock(glm::vec3 position);
	void setBlock(glm::vec3 position, int type);

	glm::vec3 position;



private:
	int blocks[16][16][16] = { 0 };
	Game* game;

	const int size = 16;
	

	Mesh mesh;

	void generateMesh();


};
