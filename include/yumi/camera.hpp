#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.hpp"
#include "window.hpp"

namespace yumi {
	class Camera {
	private:
		EngineWindow* window;
		float fov, near, far, sensitivity;
		float speed, normalSpeed, sprintSpeed;
		float yaw, pitch;

		glm::vec3 position;
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	public:
		Camera(EngineWindow* window, float fox, float near, float far, float sensitivity = 100.f, \
			float normalSpeed = 2.0f, float sprintSpeed = 5.0f, glm::vec3 position = glm::vec3(0.0f));

		~Camera();

		void updateMatrices(Shader* shader);
		void processInputs();
		glm::vec3& getPosition();
	};
}
