const float n = 0.1f;
const float f = 9.9f;


/**
 * Specifies which constraints are passed to the overload of the perspectiveMatrix function.
 */
enum class FrustumConstraints {
	LEFT, RIGHT, TOP, BOTTOM,
	TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
};


/**
 * Builds the perspective matrix given the fov on the y axis, the aspect ratio and the near and far planes.
 * 
 * @param fovY Field of view on the y axis
 * @param a Aspect ratio
 * @param n Near plane
 * @param f Far plane
 * @return The perspective matrix.
 */
const glm::mat4 perspectiveMatrix(const float fovY, const float a, const float n, const float f) {
	return glm::mat4(
		1/(a * glm::tan(glm::radians(fovY/2))), 0, 0, 0,
		0, -1/glm::tan(glm::radians(fovY/2)), 0, 0,
		0, 0, f/(n-f), -1,
		0, 0, (n*f)/(n-f), 0
	);
}


/**
 * Builds the perspective matrix given the frustum constraints on the near plane.
 * 
 * @param l Left constraint
 * @param r Right constraint
 * @param t	Top constraint
 * @param b	Bottom constraint
 * @param n	Near plane constraint
 * @param f	Far plane constraint
 * @return The perspective matrix.
 */
const glm::mat4 perspectiveMatrix(const float l, const float r, const float b, const float t, const float n, const float f) {
	return glm::mat4(
		(2 * n) / (r - l), 0, 0, 0,
		0, (2 * n) / (b - t), 0, 0,
		(r + l) / (r - l), (b + t) / (b - t), f / (n - f), -1,
		0, 0, (n * f) / (n - f), 0
	);
}


/**
 * Builds the perspective matrix given the fov on the y axis, the aspect ratio, the near and far plane and the position of the left/right and/or top/bottom constraints on the near plane of the frustum.
 * 
 * @param fovY Field of view on the y axis
 * @param a Aspect ratio
 * @param n Near plane
 * @param f Far plane
 * @param lr Left or right constraint
 * @param tb Top or bottom constraint
 * @param constrs Which constraints are given in the previous 2 parameters (left or right and/or top or bottom). If the constraint is single (LEFT, RIGHT, TOP, BOTTOM), one of the 2 previous parameters won't be considered.
 * @return The perspective matrix.
 */
const glm::mat4 perspectiveMatrix(const float fovY, const float a, const float n, const float f, const float lr, const float tb, const FrustumConstraints constrs) {
	float l, r, t, b;
	float fov = glm::radians(fovY);

	switch (constrs) {
	case FrustumConstraints::LEFT: 
		l = lr;
		t = n * glm::tan(fov / 2);
		b = -t;
		r = a * (t - b) + l;
		break;
	case FrustumConstraints::RIGHT:
		r = lr;
		t = n * glm::tan(fov / 2);
		b = -t;
		l = -(a * (t - b) - r);
		break;
	case FrustumConstraints::BOTTOM:
		b = tb;
		r = a * n * glm::tan(fov / 2);
		l = -r;
		t = (r - l + a * b) / a;
		break;
	case FrustumConstraints::TOP:
		t = tb;
		r = a * n * glm::tan(fov / 2);
		l = -r;
		b = -(r - l - a * t) / a;
		break;
	case FrustumConstraints::BOTTOM_LEFT:
		l = lr;
		b = tb;
		t = n * glm::tan(fov - glm::atan(b / n));
		r = a * (t - b) + l;
		break;
	case FrustumConstraints::TOP_LEFT:
		l = lr;
		t = tb;
		b = -n * glm::tan(fov - glm::atan(t / n));
		r = a * (t - b) + l;
		break;
	case FrustumConstraints::BOTTOM_RIGHT:
		r = lr;
		b = tb;
		t = n * glm::tan(fov - glm::atan(b / n));
		l = -(a * (t - b) - r);
		break;
	case FrustumConstraints::TOP_RIGHT:
		r = lr;
		t = tb;
		b = -n * glm::tan(fov - glm::atan(t / n));
		l = -(a * (t - b) - r);
		break;
	}

	return perspectiveMatrix(l, r, b, t, n, f);
}



// Create a matrix for Perspecrtive projection with the given aspect ratio a, and a FovY = 90o
glm::mat4 PO1(float a) {
	return perspectiveMatrix(90.0f, a, n, f);
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a, and a FovY = 120o
glm::mat4 PO2(float a) {
	return perspectiveMatrix(120.0f, a, n, f);
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a, and a FovY = 30o
glm::mat4 PO3(float a) {
	return perspectiveMatrix(30.0f, a, n, f);
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view with a FovY = 90o. Here r=0, and l, t and b should be computed to match both the aspect ratio and the FovY
glm::mat4 PO4(float a) {
	return perspectiveMatrix(90.0f, a, n, f, 0.0f, NULL, FrustumConstraints::RIGHT);
}

