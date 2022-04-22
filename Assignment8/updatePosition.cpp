// Create the world matrix for the robot
glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	const float speed = 1.0f;

	static glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	static float rotation = 0.0f;
	static auto lastTime = std::chrono::high_resolution_clock::now();

	float deltaTime = std::chrono::duration(lastTime - std::chrono::high_resolution_clock::now()).count();
	lastTime = std::chrono::high_resolution_clock::now();

	const float spaceCovered = speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W)) {
		pos += glm::vec3(spaceCovered * glm::cos(rotation), spaceCovered * glm::sin(rotation), 0.0f);
	}

	return
		glm::translate(glm::mat4(1.0f), pos);
}

