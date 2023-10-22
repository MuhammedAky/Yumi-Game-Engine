#pragma once

#include <glad/glad.h>

#include <string>
#include <iostream>

namespace yumi {
	class Shader {
	private:
		unsigned int id;

		void check_program();
		void check_shader(unsigned int shader, const char* type);

	public:
		Shader(std::string vertex_src_string, std::string fragment_src_string);
		~Shader();

		int get_uniform_location(const char* name);
		void use();
		void destroy();
		int get_program_id();
	};
}