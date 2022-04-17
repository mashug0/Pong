#ifndef GAME_H
#define GAME_H

#pragma once

#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Ball.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum GameState
{
    GAME_ACTIVATE,
    GAME_MENU,
    GAME_WIN
};

const glm::vec2 PADDLE_SIZE = glm::vec2(25.0f ,150.f);
const float PADDLE_VELOCITY(500.f);

const glm::vec2 INITIAL_BALL_VELOCITY(200.0f,-55.0f);
const float BALL_RADIUS = 13.5;

class Game
{
public:
    bool keys[1024];
    
    Game(unsigned int width , unsigned int height);
    ~Game();
    void init();
    void processInput(float dt);
    void update(float dt);
    void render();
private:
    GameState m_State;
    unsigned int m_Width , m_Height;
    bool CheckCollision(GameObject& one , GameObject& two);
    
    void DoCollision();

    void ResetPlayers();
    void ResetBall();

};

#endif