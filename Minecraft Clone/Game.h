#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"

#include "World.h"

class Game

{
	private:

	public: 
		World world;

		void initialize();
		void update(float dt);
		void render(Shader* currentShader);
};

