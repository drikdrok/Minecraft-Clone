#include "Game.h"
#include "Camera.h"


void Game::initialize(Camera* camera) {
	world = new World(this);
	world->generate();

	player = new Player(this);

	this->camera = camera;

	/*

	//South
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);
	mesh.addVertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f);

	//North
	mesh.addVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	mesh.addVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
	mesh.addVertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f);
	mesh.addVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);

	//West
	mesh.addVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	mesh.addVertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

	//Right
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);

	//South
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(0.5f, -0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	mesh.addVertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);

	//North
	mesh.addVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);
	mesh.addVertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f);
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f);
	mesh.addVertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f);
	mesh.addVertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f);

	*/

}

void Game::update(float dt) {
	world->update();
}

void Game::render(Shader* currentShader) {
	world->render(currentShader);


	Mesh mesh;

	mesh.addTopFace(1, 1, 1);
	mesh.setupMesh();
	mesh.render(1, glm::vec3(0, 0, 0), currentShader);

}