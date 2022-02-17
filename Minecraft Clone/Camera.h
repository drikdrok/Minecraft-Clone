#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"

#include "Cube.h"

#include <vector>

#include <iostream>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Game* game;


    glm::vec3 lookingAt = glm::vec3(0, 0, 0);
    glm::vec3 placeBlockAt = glm::vec3(0, 0, 0);

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();




    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();

    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += glm::vec3(1.0f, 0.0f, 1.0f) * Front * velocity;
        if (direction == BACKWARD)
            Position -= glm::vec3(1.0f, 0.0f, 1.0f) * Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;

        if (direction == UP)
            Position += WorldUp * velocity;
        if (direction == DOWN)
            Position -= WorldUp * velocity;

        game->player->setPosition(Position);
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
        //std::cout << "Looking At: " << lookingAt.x << ", " << lookingAt.y << ", " << lookingAt.z << std::endl;

    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }


    void placeBlock() {
        game->world->setBlock(placeBlockAt, game->player->blockInHand);
    }
    void removeBlock() {
        game->world->setBlock(lookingAt, 0);
    }



    //Locate the block the player is looking at
    void findBlockInfront(Shader* shader) {
        glm::vec3 ray = glm::vec3(Position.x, Position.y, Position.z);
        placeBlockAt = glm::vec3(floorf(ray.x), floorf(ray.y), floorf(ray.z));

        for (int i = 0; i < 1000; i++) {
            ray += Front * glm::vec3(0.01f, 0.01f, 0.01f);

            int block = game->world->getBlock(glm::vec3(floorf(ray.x + 0.5f), floorf(ray.y + 0.5f), floorf(ray.z + 0.5f)));

            if (block == -1) {
                lookingAt = glm::vec3(1, 1, 1);
                return;
            }
            else if (block > 0) {
                lookingAt = glm::vec3(floorf(ray.x + 0.5f), floorf(ray.y + 0.5f), floorf(ray.z + 0.5f));

                return;
            }
            placeBlockAt = glm::vec3(floorf(ray.x + 0.5f), floorf(ray.y + 0.5f), floorf(ray.z + 0.5f));
        }
        lookingAt = glm::vec3(1, 1, 1);
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
