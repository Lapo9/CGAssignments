// Create a world matrix using position, Euler angles, and size
// Euler angles are passed in YPR parameter:
// YPR.x : Yaw
// YPR.y : Pitch
// YPR.z : Roll
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size) {
	return
		glm::translate(glm::mat4(1.0f), pos) *
		glm::eulerAngleXYX(glm::radians(YPR.x), glm::radians(YPR.y), glm::radians(YPR.z)) *
		glm::scale(glm::mat4(1.0f), size);
}

// Create a world matrix using position, quaternion angles, and size
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size) {
	return
		glm::translate(glm::mat4(1.0f), pos) *
		glm::mat4(rQ) *
		glm::scale(glm::mat4(1.0f), size);
}

