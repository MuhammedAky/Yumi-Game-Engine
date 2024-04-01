#pragma once

#include <glad/glad.h>

#include "vertex.hpp"

namespace yumi {
	class VertexBuffer {
	private:
		unsigned int id;

	public:
		VertexBuffer(std::vector<Vertex>& vertices);
		~VertexBuffer();

		void bind();
		void unbind();
		void destroy();
	};
}