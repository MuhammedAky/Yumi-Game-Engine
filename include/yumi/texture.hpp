#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace yumi {
	class Texture {
	private:
		unsigned int id;
		unsigned int unit;
		const char* type;

	public:
		Texture(const char* file, const char* type, unsigned int unit);
		~Texture();

		void texUnit(unsigned int id, unsigned int unit);
		void bind();
		void unbind();
		void destroy();
		const char* getType();
	};
}