#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 Pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0));
	virtual void Draw(SpriteRenderer& renderer);

	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool isSolid;
	bool Destroyed;
	Texture2D Sprite;

private:


};

