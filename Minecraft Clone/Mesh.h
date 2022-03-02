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

    float shadeAmount = 0.2f;

    void addVertex(float x, float y, float z, float t1, float t2, int type, float brightness) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(t1);
        vertices.push_back(t2);
        vertices.push_back(type);
        vertices.push_back(brightness);
    }

    void addNorthFace(int x, int y, int z, int type, int brightness) {
        addVertex(x, y, z + 1.0f, 0.0f, 0.0f, type, brightness);
        addVertex(x + 1.0f, y, z + 1.0f, 1.0f, 0.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 1.0f, type, brightness);
        addVertex(x, y + 1.0f, z + 1.0f, 0.0f, 1.0f, type, brightness);
        addVertex(x, y, z + 1.0f, 0.0f, 0.0f, type, brightness);
    }

    void addSouthFace(int x, int y, int z, int type, int brightness) {
        addVertex(x, y, z, 0.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y, z, 1.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y + 1.0f, z, 1.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y + 1.0f, z, 1.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x, y + 1.0f, z, 0.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x, y, z, 0.0f, 0.0f, type, brightness - shadeAmount);
    }

    void addWestFace(int x, int y, int z, int type, int brightness) {
        addVertex(x, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x, y + 1.0f, z, 1.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x, y, z, 0.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x, y, z, 0.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x, y, z + 1.0f, 0.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness - shadeAmount);
    }

    void addEastFace(int x, int y, int z, int type, int brightness) {
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z, 1.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y, z, 0.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y, z, 0.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y, z + 1.0f, 0.0f, 0.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness);
    }

    void addTopFace(int x, int y, int z, int type, int brightness) {
        addVertex(x, y + 1.0f, z, 0.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z, 1.0f, 1.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness);
        addVertex(x + 1.0f, y + 1.0f, z + 1.0f, 1.0f, 0.0f, type, brightness);
        addVertex(x, y + 1.0f, z + 1.0f, 0.0f, 0.0f, type, brightness);
        addVertex(x, y + 1.0f, z, 0.0f, 1.0f, type, brightness);
    }

    void addBottomFace(int x, int y, int z, int type, int brightness) {
        addVertex(x, y, z, 0.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y, z, 1.0f, 1.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y, z + 1.0f, 1.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x + 1.0f, y, z + 1.0f, 1.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x, y, z + 1.0f, 0.0f, 0.0f, type, brightness - shadeAmount);
        addVertex(x, y, z, 0.0f, 1.0f, type, brightness - shadeAmount);

    }

    void addFullBlock(int x, int y, int z, int type, int brightness) {
        addNorthFace(x, y, z, type, brightness);
        addSouthFace(x, y, z, type, brightness);
        addWestFace(x, y, z, type, brightness);
        addEastFace(x, y, z, type, brightness);
        addBottomFace(x, y, z, type, brightness);
        addTopFace(x, y, z, type, brightness);
    }

    void initialize() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //block attribute
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        //brightness attribute
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);

        initialized = true;
    }

    void setupMesh() {
        if (vertices.size() == 0)
            return;

        if (!initialized) {
            initialize();
            return;
        }

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //block attribute
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
        //brightness attribute
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
    }

    void render(glm::vec3 position, Shader* currentShader) {
        if (vertices.size() == 0)
            return;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);

        currentShader->setMat4("model", model);

        //currentShader->setInt("texture1", 0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
    }

    void render(glm::vec3 position, Shader* currentShader, float scale, float yaw, float pitch) {
        if (vertices.size() == 0)
            return;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, glm::vec3(scale));
        model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(pitch), glm::vec3(0.0f, 0.0f, 1.0f));

        currentShader->setMat4("model", model);

        // bind textures on corresponding texture units
       // currentShader->setInt("texture1", 0);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
    }


    void reset() {
        vertices.clear();
    }

};