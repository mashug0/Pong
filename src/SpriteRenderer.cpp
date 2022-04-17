#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
{
	this->m_Shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->m_quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D texture, glm::vec2 Position, glm::vec2 size, float rotation, 
					glm::vec3 color)
{
	m_Shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(Position, 0));
	model = glm::translate(model, glm::vec3(0.5 * size.x , 0.5*size.y, 0.0));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_Shader.SetMatrix4("u_Model", model);
	m_Shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(m_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;

	float Vertices[] =
	{
		0.0f , 1.0f , 0.0f , 1.0f,
		1.0f , 0.0f , 1.0f , 0.0f,
		0.0f , 0.0f , 0.0f , 0.0f,

		0.0f , 1.0f , 0.0f , 1.0f,
		1.0f , 1.0f , 1.0f , 1.0f,
		1.0f , 0.0f , 1.0f , 0.0f
	};

	glGenVertexArrays(1, &m_quadVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}
