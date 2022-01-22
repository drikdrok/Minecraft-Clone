#pragma once

#include "shader.h"
#include "Cube.h"

class World
{
	public:
		World() { generate(); }
		void generate();
		void render(Shader* currentShader);
		int getBlock(int x, int y, int z);
		void setBlock(int x, int y, int z, int type);

		static const int size = 16;

	private:
		int blocks[size][size][size] = { 0 };

};

