#pragma once

#include "shader.h"
#include "Cube.h"

class Game;

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

		static const int size = 16;

	private:
		int blocks[size][size][size] = { 0 };

		Game* game;


};

