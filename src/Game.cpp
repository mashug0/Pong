#include "Game.h"
#include <cmath>
#include <glm/gtx/normal.hpp>
SpriteRenderer *Renderer;
GameObject *Player1;
GameObject *Player2;
Ball *ball;

Game::Game(unsigned int width, unsigned int height) : keys()
{
    m_State = GAME_ACTIVATE;
    this->m_Width = width;
    this->m_Height = height;
    // this->init();
}

void Game::init()
{
    ResourceManager::LoadShader("assets/shaders/sprite.vs", "assets/shaders/sprite.fs", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("u_VP", projection);
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("assets/bgfx/paddle.png", true, "Paddle");
    ResourceManager::LoadTexture("assets/bgfx/Ball.png", true, "Ball");

    glm::vec2 Player1Pos = glm::vec2(0, m_Height / 2.0f - PADDLE_SIZE.y / 2.0f);
    Player1 = new GameObject(Player1Pos, PADDLE_SIZE, ResourceManager::GetTexture("Paddle"), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1));
    glm::vec2 Player2Pos = glm::vec2(m_Width - PADDLE_SIZE.x, m_Height / 2.0f - PADDLE_SIZE.y / 2.0f);
    Player2 = new GameObject(Player2Pos, PADDLE_SIZE, ResourceManager::GetTexture("Paddle"), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1));

    glm::vec2 ballPos = glm::vec2(m_Width / 2.0f - BALL_RADIUS / 2.f, m_Height / 2.0f - BALL_RADIUS / 2.f);
    ball = new Ball(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("Ball"));
}
void Game::processInput(float dt)
{
    if (m_State == GAME_ACTIVATE)
    {
        float velocity = 2.0f * PADDLE_VELOCITY * dt;
        if (keys[GLFW_KEY_W])
        {
            if (Player1->Position.y >= 0.0f)
                Player1->Position.y -= velocity;
        }
        if (keys[GLFW_KEY_S])
        {
            if (Player1->Position.y <= m_Height - PADDLE_SIZE.y)
                Player1->Position.y += velocity;
        }
        if (keys[GLFW_KEY_UP])
        {
            if (Player2->Position.y >= 0.0f)
                Player2->Position.y -= velocity;
        }
        if (keys[GLFW_KEY_DOWN])
        {
            if (Player2->Position.y <= m_Height - PADDLE_SIZE.y)
                Player2->Position.y += velocity;
        }
        if (this->keys[GLFW_KEY_SPACE])
            ball->Stuck = false;
    }
}
void Game::render()
{
    if (m_State == GAME_ACTIVATE)
    {
        Player1->Draw(*Renderer);
        Player2->Draw(*Renderer);
        ball->Draw(*Renderer);
    }
}
void Game::update(float dt)
{
    if (m_State == GAME_ACTIVATE)
    {
        DoCollision();
        ball->Move(dt, m_Height);

        if (ball->Position.x <= 0 || ball->Position.x >= m_Width)
        {
            this->ResetBall();
            this->ResetPlayers();
        }
    }
}

void Game::DoCollision()
{
    if (CheckCollision(*Player1, *ball))
    {
        ball->Velocity.x = -ball->Velocity.x;
    }
    if (CheckCollision(*Player2, *ball))
    {
        ball->Velocity.x = -ball->Velocity.x;
    }
}
bool Game::CheckCollision(GameObject &one, GameObject &two)
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
                      two.Position.x + two.Size.x >= one.Position.x;

    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
                      two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}

void Game::ResetPlayers()
{
    Player1->Position = glm::vec2(0, m_Height / 2.0f - PADDLE_SIZE.y / 2.0f);
    Player2->Position = glm::vec2(m_Width - PADDLE_SIZE.x, m_Height / 2.0f - PADDLE_SIZE.y / 2.0f);
}

void Game::ResetBall()
{
    ball->Velocity = glm::vec2(100.f, -35.f);
    ball->reset(glm::vec2(m_Width / 2.0f - BALL_RADIUS, m_Height / 2.0f - BALL_RADIUS), INITIAL_BALL_VELOCITY);
}

Game::~Game()
{
    delete Renderer;
    delete Player1;
    delete Player2;
    delete ball;
}
