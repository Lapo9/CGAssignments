// Create a matrix for Isometric projection with the given aspect ration a
const float n = -4.0f;
const float f = 12.0f;
const float w = 2.0f;


glm::mat4 PO1(float a) {
	glm::mat4 out = 
		glm::mat4(
			1 / w, 0, 0, 0,
			0, -a / w, 0, 0,
			0, 0, 1 / (n - f), n / (n - f),
			0, 0, 0, 1
		) *
		glm::rotate(glm::mat4(1.0f), glm::radians(35.26f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return out;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a) {
	glm::mat4 out = glm::mat4(1.0);
	return out;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a) {
	glm::mat4 out = glm::mat4(1.0);
	return out;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a) {
	glm::mat4 out = glm::mat4(1.0);
	return out;
}

