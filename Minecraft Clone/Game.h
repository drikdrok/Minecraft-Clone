#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"

#include "World.h"
#include "Player.h"

class Camera;

class Game
{
	private:

	public: 
		World* world;
		Player* player;
		Camera* camera;


		void initialize(Camera* camera);
		void update(float dt);
		void render(Shader* currentShader);
};

