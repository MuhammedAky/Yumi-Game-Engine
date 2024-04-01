#pragma once

#include <glad/glad.h>

#include <vector>

namespace yumi {
	class IndexBuffer {
	private:
		unsigned int id;
		unsigned int count;

	public:
		IndexBuffer(std::vector <unsigned int>& indices);
		~IndexBuffer();

		int getCount();
		void bind();
		void unbind();
		void destroy();
	};
}