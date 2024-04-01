#pragma once

#include <glad/glad.h>

#include "vertexBuffer.hpp"

namespace yumi {
	class VertexArray {
	private:
		unsigned int id;


	public:
		VertexArray();
		~VertexArray();

		void linkAttrib(VertexBuffer* buffer, unsigned int index, GLenum type, unsigned int count, unsigned int stride, void* offset);
		void bind();
		void unbind();
		void destroy();
	};
}