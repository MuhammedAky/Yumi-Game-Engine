#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include "color.hpp"
#include "input.hpp"

#include <iostream>
#include <cstdint>
#include <string>

namespace yumi {
	class EngineWindow {
	private:
		GLFWwindow* window;
		Color backgroundColor;
		std::string title, iconPath;
		int32_t width, height;
		bool resizable, vsync;
		float lastTime;

	public:
		Input* input;
		float currentTime, deltaTime;

		EngineWindow(int32_t width, int32_t height, const char* title, const char* iconPath = "res/icon/icon.png", \
			Color backgroundColor = { 0, 0,0,255 }, bool fullscreen = false, bool resizable = true, bool vsync = true);
	
		~EngineWindow();

		bool shouldClose();
		int32_t checkErrors(bool log = true);
		void destroy();
		void clear();
		void swapBuffers();
		void pollEvents();
		void setIcon(const char* filePath);
		const std::string& getIconPath();
		void setTitle(const char* title);
		const std::string& getTitle();
		void setSize(int32_t width, int32_t height);
		void getSize(int32_t* width, int32_t* height);
		void setBackgroundColor(Color background_color);
		Color* getBackgroundColor();
		void setVsync(bool vsync);
		bool getVsync();
		GLFWwindow* get();
	};
}