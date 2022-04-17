#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:
	float Radius;
	bool Stuck;

	Ball();
	Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float dt, unsigned int height);

	void reset(glm::vec2 pos, glm::vec2 velocity);
};
