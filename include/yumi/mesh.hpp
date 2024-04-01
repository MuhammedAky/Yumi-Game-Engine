#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "vertexArray.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "camera.hpp"
#include "transform.hpp"

#include <vector>

namespace yumi {
	class Mesh {
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;

		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* ibo;

	public:
		Transform transform;
		Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture*>& textures);
		~Mesh();

		void render(Shader* shader, Camera* camera, glm::mat4 matrix = glm::mat4(1.0f));
		void destroy();
	};
}