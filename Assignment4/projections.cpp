const float n = -4.0f; // Near plane
const float f = 12.0f; // Far plane
const float w = 2.0f; // Half width


/**
 * Returns a parallel projection matrix with the specified parameters.
 * 
 * @param n Near plane
 * @param f Far plane
 * @param w Half width
 * @param a Aspect ratio
 * @return The parallel projection matrix.
 */
const glm::mat4 parallelMatrix(const float n, const float f, const float w, const float a) {
	return
		glm::mat4(
			1 / w, 0, 0, 0,
			0, -a / w, 0, 0,
			0, 0, 1 / (n - f), 0,
			0, 0, n / (n - f), 1
		);
}


// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a) {
	return
		parallelMatrix(n, f, w, a) *
		glm::rotate(glm::mat4(1.0f), glm::radians(35.26f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// Create a matrix for Dimnetric projection (alpha = 45 degree) with the given aspect ration a
glm::mat4 PO2(float a) {
	return
		parallelMatrix(n, f, w, a) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree) with the given aspect ration a
glm::mat4 PO3(float a) {
	return
		parallelMatrix(n, f, w, a) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// Create a matrix for Cabinet projection (alpha = 45) with the given aspect ration a
glm::mat4 PO4(float a) {
	return
		parallelMatrix(n, f, w, a) *
		glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			-0.5f * glm::cos(glm::radians(45.0f)), -0.5f * glm::sin(glm::radians(45.0f)), 1, 0,
			0, 0, 0, 1
		);
}

