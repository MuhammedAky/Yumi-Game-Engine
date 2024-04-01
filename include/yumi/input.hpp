#pragma once

#include <GLFW/glfw3.h>

#include "yumi/window.hpp"

namespace yumi {
	class Input {
	private:
		GLFWwindow* window;

	public:
		Input(GLFWwindow* window);
		~Input();

		bool getKey(int key);
		bool getMouseButton(int button);
		void getMousePosition(double* x, double* y);
		void setMousePosition(double x, double y);
		void setMouseVisible(bool visible);
	};
}