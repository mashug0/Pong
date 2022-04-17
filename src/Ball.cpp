#include "Ball.h"

Ball::Ball():GameObject() , Radius(12.5) , Stuck(true)
{
}

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
	:GameObject(pos , glm::vec2(radius * 2.0f ) , sprite , glm::vec3(1.0f) , velocity) , Radius(radius) , Stuck(true)
{
}

glm::vec2 Ball::Move(float dt  , unsigned int height)
{
	if (!this->Stuck)
	{
		this->Position += this->Velocity * dt * 3.0f;

		
		if (this->Position.y <= 0.0f)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = 0.0f;
		}
		else if (this->Position.y + this->Size.y>= height)
		{
			this->Velocity.y = -this->Velocity.y;
			this->Position.y = height - this->Size.y;
		}
	}
	return this->Position;
}

void Ball::reset(glm::vec2 pos, glm::vec2 velocity)
{
	this->Position = pos;
	this->Velocity = velocity;
	this->Stuck = true;
}
