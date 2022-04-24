
std::pair<std::vector<float>, std::vector<uint32_t>> makeCube(float side = 1.0f) {
	auto vertices = std::vector<float>(24);
	
	vertices[0] = -side;
	vertices[1] = -side;
	vertices[2] = -side;

	vertices[3] = side;
	vertices[4] = -side;
	vertices[5] = -side;

	vertices[6] = side;
	vertices[7] = side;
	vertices[8] = -side;

	vertices[9] = -side;
	vertices[10] = side;
	vertices[11] = -side;

	vertices[12] = -side;
	vertices[13] = -side;
	vertices[14] = side;

	vertices[15] = side;
	vertices[16] = -side;
	vertices[17] = side;

	vertices[18] = side;
	vertices[19] = side;
	vertices[20] = side;

	vertices[21] = -side;
	vertices[22] = side;
	vertices[23] = side;


	auto indices = std::vector<uint32_t>(36);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	indices[6] = 0;
	indices[7] = 4;
	indices[8] = 7;

	indices[9] = 0;
	indices[10] = 7;
	indices[11] = 3;

	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 6;

	indices[15] = 4;
	indices[16] = 6;
	indices[17] = 7;

	indices[18] = 1;
	indices[19] = 5;
	indices[20] = 6;

	indices[21] = 1;
	indices[22] = 6;
	indices[23] = 2;

	indices[24] = 0;
	indices[25] = 4;
	indices[26] = 5;

	indices[27] = 0;
	indices[28] = 5;
	indices[29] = 1;

	indices[30] = 2;
	indices[31] = 3;
	indices[32] = 6;

	indices[33] = 3;
	indices[34] = 6;
	indices[35] = 7;

	return std::pair(vertices, indices);
}

std::pair<std::vector<float>, std::vector<uint32_t>> makeCilinder(int precision, float radius = 1.0f, float height = 2.0f) {
	const float unitAngle = (glm::pi<float>() * 2) / precision; // angle of each "slice" of the top and bottom face
	float r = radius; // radius
	float h = height; // height

	auto vertices = std::vector<float>(precision * 2 * 3);
	for (int i = 0; i < precision; ++i) {
		vertices[i * 6 + 0] = r * glm::cos(unitAngle * i); // x bottom
		vertices[i * 6 + 1] = -h / 2; // y bottom
		vertices[i * 6 + 2] = r * glm::sin(unitAngle * i); // z bottom

		vertices[i * 6 + 3] = vertices[i * 6 + 0]; // x top
		vertices[i * 6 + 4] = -vertices[i * 6 + 1]; // y top
		vertices[i * 6 + 5] = vertices[i * 6 + 2]; // z top
	}
	// Add the center of the top and bottom face vertices
	vertices.push_back(0.0f); vertices.push_back(-h / 2); vertices.push_back(0.0f);
	vertices.push_back(0.0f); vertices.push_back(h / 2); vertices.push_back(0.0f);


	auto indices = std::vector<uint32_t>(precision * 4 * 3);
	// Side faces
	for (int i = 0; i < precision * 2 - 2; ++i) {
		indices[i * 3] = i;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = i + 2;
	}
	// Connect last vertices
	indices[(precision * 2 - 2) * 3] = precision * 2 - 2; indices[(precision * 2 - 2) * 3 + 1] = precision * 2 - 1; indices[(precision * 2 - 2) * 3 + 2] = 0;
	indices[(precision * 2 - 1) * 3] = precision * 2 - 1; indices[(precision * 2 - 1) * 3 + 1] = 0; indices[(precision * 2 - 1) * 3 + 2] = 1;
	// Top/bottom faces
	for (int i = 0, const base = precision * 6; i < precision - 1; ++i) {
		// Bottom
		indices[base + i * 6] = i * 2;
		indices[base + i * 6 + 1] = (i + 1) * 2;
		indices[base + i * 6 + 2] = precision * 2;

		// Top
		indices[base + i * 6 + 3] = i * 2 + 1;
		indices[base + i * 6 + 4] = (i + 1) * 2 + 1;
		indices[base + i * 6 + 5] = precision * 2 + 1;
	}
	// "Close" top and bottom faces
	indices[precision * 6 + (precision - 1) * 6] = (precision - 1) * 2;
	indices[precision * 6 + (precision - 1) * 6 + 1] = 0;
	indices[precision * 6 + (precision - 1) * 6 + 2] = precision * 2;

	indices[precision * 6 + (precision - 1) * 6 + 3] = (precision - 1) * 2 + 1;
	indices[precision * 6 + (precision - 1) * 6 + 4] = 1;
	indices[precision * 6 + (precision - 1) * 6 + 5] = precision * 2 + 1;

	return std::pair(vertices, indices);
}

std::pair<std::vector<float>, std::vector<uint32_t>> makeSphere(int precision, float radius = 1.0f) {
	if (precision % 2) {
		precision++;
	}
	const float unitAngle = (glm::pi<float>() * 2) / precision;
	const float R = 1.0f;

	auto vertices = std::vector<float>((precision * (precision / 2 - 1) + 1) * 3);
	vertices[0] = 0.0f; vertices[1] = -R; vertices[2] = 0.0f;
	vertices.push_back(0.0f); vertices.push_back(R); vertices.push_back(0.0f);

	for (int i = 1; i < precision / 2; ++i) {
		const float r = R * glm::sin(unitAngle * i);
		const float h = -R * glm::cos(unitAngle * i);

		for (int j = 0, const base = 3 + (i-1) * precision * 3; j < precision; ++j) {
			vertices[base + j * 3] = r * glm::cos(j * unitAngle);
			vertices[base + j * 3 + 1] = h;
			vertices[base + j * 3 + 2] = r * glm::sin(j * unitAngle);
		}
	}

	// Top/bottom shells
	auto indices = std::vector<uint32_t>((precision * 2 * (precision / 2)) * 3);
	for (int i = 0; i < precision - 1; ++i) {
		indices[i * 6] = i + 1;
		indices[i * 6 + 1] = i + 2;
		indices[i * 6 + 2] = 0;

		indices[i * 6 + 3] = precision * (precision / 2 - 2) + i + 1;
		indices[i * 6 + 4] = precision * (precision / 2 - 2) + i + 2;
		indices[i * 6 + 5] = precision * (precision / 2 - 1) + 1;
	}
	// "Close" last face of each shell
	indices[(precision - 1) * 6] = precision; indices[(precision - 1) * 6 + 1] = 1; indices[(precision - 1) * 6 + 2] = 0;
	indices[(precision - 1) * 6 + 3] = precision * (precision / 2 - 1); indices[(precision - 1) * 6 + 4] = precision * (precision / 2 - 2) + 1; indices[(precision - 1) * 6 + 5] = precision * (precision / 2 - 1) + 1;
	
	// Sides
	for (int i = 1; i < precision / 2 - 1; ++i) {
		for (int j = 0, const base = 1 + (i - 1) * precision; j < precision - 1; ++j) {
			indices[i * precision * 6 + j * 6] = base + j;
			indices[i * precision * 6 + j * 6 + 1] = base + j + precision;
			indices[i * precision * 6 + j * 6 + 2] = base + j + 1;

			indices[i * precision * 6 + j * 6 + 3] = base + j + precision;
			indices[i * precision * 6 + j * 6 + 4] = base + j + 1;
			indices[i * precision * 6 + j * 6 + 5] = base + j + 1 + precision;
		}
		// "Close" last face of each "circle"
		indices[i * precision * 6 + (precision - 1) * 6] = 1 + (i - 1) * precision + precision - 1;
		indices[i * precision * 6 + (precision - 1) * 6 + 1] = 1 + (i - 1) * precision + precision + precision - 1;
		indices[i * precision * 6 + (precision - 1) * 6 + 2] = 1 + (i - 1) * precision;

		indices[i * precision * 6 + (precision - 1) * 6 + 3] = 1 + (i - 1) * precision + precision + precision - 1;
		indices[i * precision * 6 + (precision - 1) * 6 + 4] = 1 + (i - 1) * precision;
		indices[i * precision * 6 + (precision - 1) * 6 + 5] = 1 + (i - 1) * precision + precision;

	}

	return std::pair(vertices, indices);
}

std::pair<std::vector<float>, std::vector<uint32_t>> makeSpring(int precision, int spires, float height = 5.0f, float internalRadius = 0.1f, float mainRadius = 1.0f) {
	const float mR = mainRadius;
	const float r = internalRadius;
	const float unitAngle = (glm::pi<float>() * 2) / precision;
	const float unitheight = height / (spires * precision);

	auto vertices = std::vector<float>(precision * spires * precision * 3);

	for (int i = 0; i < precision; ++i) {
		// Compute the radius and height of the first point of each one of the spirals which, when combined, create the spring
		float h = r * glm::sin(i * unitAngle);
		float R = mR - r * glm::cos(i * unitAngle);

		// Create the spiral
		for (int j = 0, const base = i * precision * spires; j < precision * spires; ++j) {
			vertices[(base + j) * 3 + 0] = R * glm::cos(j * unitAngle);
			vertices[(base + j) * 3 + 1] = h + j * unitheight;
			vertices[(base + j) * 3 + 2] = R * glm::sin(j * unitAngle);
		}
	}

	// Add center vertices in order to "close" the spring
	vertices.push_back(mR); vertices.push_back(0); vertices.push_back(0);
	vertices.push_back(mR * glm::cos(unitAngle * (precision-1))); vertices.push_back(height - unitheight); vertices.push_back(mR * glm::sin(unitAngle * (precision - 1)));


	auto indices = std::vector<uint32_t>((precision * 2 * (precision * spires - 1)) * 3);

	for (int i = 0; i < precision * spires - 1; ++i) {
		for (int j = 0, const base = precision * i; j < precision - 1; ++j) {
			indices[(base + j) * 6 + 0] = j * precision * spires + i;
			indices[(base + j) * 6 + 1] = j * precision * spires + i + 1;
			indices[(base + j) * 6 + 2] = (j + 1) * precision * spires + i;

			indices[(base + j) * 6 + 3] = j * precision * spires + i + 1;
			indices[(base + j) * 6 + 4] = (j + 1) * precision * spires + i;
			indices[(base + j) * 6 + 5] = (j + 1) * precision * spires + i + 1;
		}

		// "Close" last face of the ring
		indices[(precision * i + precision - 1) * 6 + 0] = (precision - 1) * precision * spires + i;
		indices[(precision * i + precision - 1) * 6 + 1] = (precision - 1) * precision * spires + i + 1;
		indices[(precision * i + precision - 1) * 6 + 2] = i;

		indices[(precision * i + precision - 1) * 6 + 3] = (precision - 1) * precision * spires + i + 1;
		indices[(precision * i + precision - 1) * 6 + 4] = i;
		indices[(precision * i + precision - 1) * 6 + 5] = i + 1;
	}

	// "Close" the top and bottom of the sping
	for (int i = 0; i < precision - 1; ++i) {
		indices.push_back(i*precision*spires); indices.push_back((i+1)*precision*spires); indices.push_back(precision * precision * spires);
		indices.push_back(i * precision * spires + precision * spires - 1); indices.push_back((i + 1) * precision * spires + precision * spires - 1); indices.push_back(precision * precision * spires + 1);
	}
	// Last faces
	indices.push_back((precision - 1) * precision * spires); indices.push_back(0); indices.push_back(precision * precision * spires);
	indices.push_back((precision - 1) * precision * spires + precision * spires - 1); indices.push_back(precision * spires - 1); indices.push_back(precision * precision * spires + 1);

	return std::pair(vertices, indices);
}


// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
	//// M1 : Cube
	auto cubeData = makeCube(0.5f);
	M1_vertices = cubeData.first;
	M1_indices = cubeData.second;


	//// M2 : Cylinder
	auto cilinderData = makeCilinder(300, 0.5f, 1.0f);
	M2_vertices = cilinderData.first;
	M2_indices = cilinderData.second;


	//// M3 : Sphere
	auto sphereData = makeSphere(200, 0.5f);
	M3_vertices = sphereData.first;
	M3_indices = sphereData.second;


	//// M4 : Spring
	auto springData = makeSpring(150, 4, 2.0f);
	M4_vertices = springData.first;
	M4_indices = springData.second;
}