#pragma once

#include <glm/glm.hpp>

#include <vector>

namespace yumi {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 tex_uv;

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color, glm::vec2 tex_uv)
			: position(position), normal(normal), color(color), tex_uv(tex_uv) {}

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color)
			: position(position), normal(normal), color(color) {}

		Vertex(glm::vec3 position, glm::vec3 normal)
			: position(position), normal(normal) {}

		Vertex(glm::vec3 position)
			: position(position) {}

		Vertex() {}
	};
}