#include "GameObject.h"

GameObject::GameObject() :Position(0, 0), Rotation(0), Color(0, 0, 0),
Size(1, 1), Velocity(0, 0), Sprite(), isSolid(false), Destroyed(false)
{

}
GameObject::GameObject(glm::vec2 Pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity )
	:Position(Pos) , Size(size) , Sprite(sprite) , Color(color) , Velocity(velocity) , isSolid(false), Destroyed(false), Rotation(0)
{

}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->Sprite, Position, Size, Rotation, Color);
}
