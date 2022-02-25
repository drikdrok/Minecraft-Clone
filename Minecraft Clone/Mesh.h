#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Mesh {
public:
    unsigned int VBO, VAO;

    bool initialized = false;

    std::vector<float> vertices;

    void addVertex(float x, float y, float z, float t1, float t2, int type) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(t1);
        vertices.push_back(t2);
        vertices.push_back(type);
    }

    void addNorthFace(int x, int y, int z, int type) {
        addVertex(x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z + 0.5f, 0.0f, 1.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, type);
    }

    void addSouthFace(int x, int y, int z, int type) {
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z - 0.5f, 1.0f, 0.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, type);
    }

    void addWestFace(int x, int y, int z, int type) {
        addVertex(x - 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
    }

    void addEastFace(int x, int y, int z, int type) {
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
    }

    void addTopFace(int x, int y, int z, int type) {
        addVertex(x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z + 0.5f, 0.0f, 0.0f, type);
        addVertex(x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 1.0f, type);
    }

    void addBottomFace(int x, int y, int z, int type) {
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z - 0.5f, 1.0f, 1.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x + 0.5f, y - 0.5f, z + 0.5f, 1.0f, 0.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, type);
        addVertex(x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, type);

    }

    void addFullBlock(int x, int y, int z, int type) {
        addNorthFace(x, y, z, type);
        addSouthFace(x, y, z, type);
        addWestFace(x, y, z, type);
        addEastFace(x, y, z, type);
        addBottomFace(x, y, z, type);
        addTopFace(x, y, z, type);
    }

    void initialize() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        initialized = true;
    }

    void setupMesh() {
        if (!initialized) {
            initialize();
            return;
        }

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void render(glm::vec3 position, Shader* currentShader) {
        glBindVertexArray(VAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        currentShader->setMat4("model", model);

        currentShader->setInt("texture1", 0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
    }

    void render(glm::vec3 position, Shader* currentShader, float scale, float yaw, float pitch) {
        glBindVertexArray(VAO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, glm::vec3(scale));
        model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(pitch), glm::vec3(0.0f, 0.0f, 1.0f));

        currentShader->setMat4("model", model);

        // bind textures on corresponding texture units
        currentShader->setInt("texture1", 0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
    }


    void reset() {
        vertices.clear();
    }

};