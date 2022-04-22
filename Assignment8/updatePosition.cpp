// Create the world matrix for the robot
using namespace std::chrono_literals;

glm::mat4 getRobotWorldMatrix(GLFWwindow* window) {
	static float speed = 1.0f; // Linear speed of the robot
	const float rotSpeed = 1.0f; // Rotational speed of the robot
	static auto runCooldown = std::chrono::high_resolution_clock::now(); // Moment in time when the run ability is available again. This has been added in order for the user to be able to perform a "click" action with the R key

	static glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f); // Current position of the robot
	static float rotation = 0.0f; // Current angle of the robot
	static auto lastTime = std::chrono::high_resolution_clock::now(); // Moment in time of the last frame

	float deltaTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - lastTime).count(); // Calcluate the elapsed time from the last frame
	lastTime = std::chrono::high_resolution_clock::now(); // Get the current time, which will be the last time in the next frame

	const float spaceCovered = speed * deltaTime; // Calcluate the space covered by the robot since the last frame

	// Move/rotate the robot
	if (glfwGetKey(window, GLFW_KEY_W)) {
		pos += glm::vec3(spaceCovered * glm::cos(rotation), 0.0f, spaceCovered * glm::sin(rotation));
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		pos += glm::vec3(-spaceCovered * glm::cos(rotation), 0.0f, -spaceCovered * glm::sin(rotation));
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		pos += glm::vec3(spaceCovered * glm::cos(rotation + glm::pi<float>() / 2), 0.0f, spaceCovered * glm::sin(rotation + glm::pi<float>() / 2));
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		pos += glm::vec3(spaceCovered * glm::cos(rotation - glm::pi<float>() / 2), 0.0f, spaceCovered * glm::sin(rotation - glm::pi<float>() / 2));
	}
	if (glfwGetKey(window, GLFW_KEY_E)) {
		rotation += rotSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Q)) {
		rotation -= rotSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_R) && lastTime > runCooldown) {
		speed = speed == 1.0f ? 3.0f : 1.0f;
		runCooldown = lastTime + 200ms;
		std::cout << speed << std::endl;
	}

	return
		glm::translate(glm::mat4(1.0f), pos) *
		glm::rotate(glm::mat4(1.0f), -rotation, glm::vec3(0.0f, 1.0f, 0.0f));
}

