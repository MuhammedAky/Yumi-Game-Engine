# YUMI - A Simple 3D Game Engine

YUMI is a lightweight and user-friendly 3D game engine designed for creating 3D games. This repository provides the basic setup code for the YUMI game engine.

## Requirements

To build and run the YUMI game engine, you will need the following:

- C++ Compiler (e.g., g++ or Visual Studio)
- [GLFW](https://www.glfw.org/): A multi-platform library for creating windows with OpenGL contexts.
- [GLAD](https://glad.dav1d.de/): OpenGL function loader.
- [ImGui](https://github.com/ocornut/imgui): A graphical user interface library.
- A 3D graphics library (e.g., OpenGL) for rendering.
- [CMake](https://cmake.org/): A build system generator.

## Installation

1. Clone this repository or download it as a ZIP file.

2. Build the project using CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
