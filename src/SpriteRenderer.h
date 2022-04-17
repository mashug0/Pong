#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();	
	
	void DrawSprite(Texture2D texture, glm::vec2 Position,
		glm::vec2 size = glm::vec2(10.f, 10.f), float rotation = 0.f,
		glm::vec3 color = glm::vec3(1.0f));

private:
	Shader m_Shader;

	GLuint m_quadVAO;

	void initRenderData();
};

