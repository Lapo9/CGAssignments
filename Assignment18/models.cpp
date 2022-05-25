
struct Vertex {
	Vertex() = default;

	Vertex(glm::vec3 pos, glm::vec3 norm) {
		this->pos = pos;
		this->norm = norm;
	}

	glm::vec3 pos;
	glm::vec3 norm;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;
std::vector<Vertex> M3_vertices;
std::vector<Vertex> M4_vertices;


std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeCube(float side = 1.0f) {
	auto forwards = glm::vec3(0.0f, 0.0f, 1.0f);
	auto backwards = glm::vec3(0.0f, 0.0f, -1.0f);
	auto top = glm::vec3(0.0f, 1.0f, 0.0f);
	auto bottom = glm::vec3(0.0f, -1.0f, 0.0f);
	auto right = glm::vec3(1.0f, 0.0f, 0.0f);
	auto left = glm::vec3(-1.0f, 0.0f, 0.0f);

	auto vertices = std::vector<Vertex>(24);
	
	// back face
	vertices[0].pos = glm::vec3(-side, -side, -side);
	vertices[1].pos = glm::vec3(side, -side, -side);
	vertices[2].pos = glm::vec3(side, side, -side);
	vertices[3].pos = glm::vec3(-side, side, -side);
	vertices[0].norm = vertices[1].norm = vertices[2].norm = vertices[3].norm = backwards;

	// front face
	vertices[4].pos = glm::vec3(-side, -side, side);
	vertices[5].pos = glm::vec3(side, -side, side);
	vertices[6].pos = glm::vec3(side, side, side);
	vertices[7].pos = glm::vec3(-side, side, side);
	vertices[4].norm = vertices[5].norm = vertices[6].norm = vertices[7].norm = forwards;

	// top face
	vertices[8].pos = glm::vec3(-side, side, side);
	vertices[9].pos = glm::vec3(side, side, side);
	vertices[10].pos = glm::vec3(side, side, -side);
	vertices[11].pos = glm::vec3(-side, side, -side);
	vertices[8].norm = vertices[9].norm = vertices[10].norm = vertices[11].norm = top;

	// bottom face
	vertices[12].pos = glm::vec3(-side, -side, side);
	vertices[13].pos = glm::vec3(side, -side, side);
	vertices[14].pos = glm::vec3(side, -side, -side);
	vertices[15].pos = glm::vec3(-side, -side, -side);
	vertices[12].norm = vertices[13].norm = vertices[14].norm = vertices[15].norm = bottom;

	// right face
	vertices[16].pos = glm::vec3(side, -side, side);
	vertices[17].pos = glm::vec3(side, -side, -side);
	vertices[18].pos = glm::vec3(side, side, -side);
	vertices[19].pos = glm::vec3(side, side, side);
	vertices[16].norm = vertices[17].norm = vertices[18].norm = vertices[19].norm = right;

	// left face
	vertices[20].pos = glm::vec3(-side, -side, side);
	vertices[21].pos = glm::vec3(-side, -side, -side);
	vertices[22].pos = glm::vec3(-side, side, -side);
	vertices[23].pos = glm::vec3(-side, side, side);
	vertices[20].norm = vertices[21].norm = vertices[22].norm = vertices[23].norm = left;


	auto indices = std::vector<uint32_t>(36);
	// back face
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// front face
	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;

	// top face
	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;

	// bottom face
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;

	// right face
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;
	
	// left face
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;

	return std::pair(vertices, indices);
}

std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeCilinder(int precision, float radius = 1.0f, float height = 2.0f) {
	const float unitAngle = (glm::pi<float>() * 2) / precision; // angle of each "slice" of the top and bottom face
	float r = radius; // radius
	float h = height; // height
	const glm::vec3 centerBottom = glm::vec3(0.0f, -h / 2, 0.0f);
	const glm::vec3 centerTop = glm::vec3(0.0f, h / 2, 0.0f);
	const unsigned int tbfOffset = 2 * precision; // offset for the vertices of the top and bottom faces

	auto vertices = std::vector<Vertex>(precision * 4);

	// Vertices for the sides and for the top/bottom faces
	for (int i = 0; i < precision; ++i) {
		// Bottom
		vertices[i * 2].pos = vertices[i * 2 + tbfOffset].pos = glm::vec3(r * glm::cos(unitAngle * i), -h / 2, r * glm::sin(unitAngle * i));
		vertices[i * 2].norm = vertices[i * 2].pos - centerBottom;
		vertices[i * 2 + tbfOffset].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		// Top
		vertices[i * 2 + 1].pos = vertices[i * 2 + 1 + tbfOffset].pos = glm::vec3(vertices[i * 2].pos.x, -vertices[i *2].pos.y, vertices[i * 2].pos.z);
		vertices[i * 2 + 1].norm = vertices[i * 2 + 1].pos - centerTop;
		vertices[i * 2 + 1 + tbfOffset].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	// Add the center of the top and bottom face vertices
	vertices.push_back(Vertex(centerBottom, glm::vec3(0.0f, -1.0f, 0.0f)));
	vertices.push_back(Vertex(centerTop, glm::vec3(0.0f, 1.0f, 0.0f)));


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
		indices[base + i * 6] = i * 2 + tbfOffset;
		indices[base + i * 6 + 1] = (i + 1) * 2 + tbfOffset;
		indices[base + i * 6 + 2] = precision * 4;

		// Top
		indices[base + i * 6 + 3] = i * 2 + 1 + tbfOffset;
		indices[base + i * 6 + 4] = (i + 1) * 2 + 1 + tbfOffset;
		indices[base + i * 6 + 5] = precision * 4 + 1;
	}
	// "Close" top and bottom faces
	indices[precision * 6 + (precision - 1) * 6] = (precision - 1) * 2 + tbfOffset;
	indices[precision * 6 + (precision - 1) * 6 + 1] = tbfOffset;
	indices[precision * 6 + (precision - 1) * 6 + 2] = precision * 4;

	indices[precision * 6 + (precision - 1) * 6 + 3] = (precision - 1) * 2 + 1 + tbfOffset;
	indices[precision * 6 + (precision - 1) * 6 + 4] = tbfOffset + 1;
	indices[precision * 6 + (precision - 1) * 6 + 5] = precision * 4 + 1;

	return std::pair(vertices, indices);
}

std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeSphere(int precision, float radius = 1.0f) {
	if (precision % 2) {
		precision++;
	}
	const float unitAngle = (glm::pi<float>() * 2) / precision;
	const float R = 1.0f;
	const auto center = glm::vec3(0.0f, 0.0f, 0.0f); // center of the sphere

	auto vertices = std::vector<Vertex>(precision * (precision / 2 - 1) + 1);
	vertices[0] = Vertex(glm::vec3(0.0f, -R, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	vertices.push_back(Vertex(glm::vec3(0.0f, R, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

	for (int i = 1; i < precision / 2; ++i) {
		const float r = R * glm::sin(unitAngle * i);
		const float h = -R * glm::cos(unitAngle * i);

		for (int j = 0, const base = 1 + (i - 1) * precision; j < precision; ++j) {
			vertices[base + j].pos = glm::vec3(r * glm::cos(j * unitAngle), h, r * glm::sin(j * unitAngle));
			vertices[base + j].norm = vertices[base + j].pos - center;
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

std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeSpring(int precision, int spires, float height = 5.0f, float internalRadius = 0.1f, float mainRadius = 1.0f) {
	const float mR = mainRadius;
	const float r = internalRadius;
	const float unitAngle = (glm::pi<float>() * 2) / precision;
	const float unitHeight = height / (spires * precision);

	auto vertices = std::vector<Vertex>(precision * spires * precision);

	for (int i = 0; i < precision; ++i) {
		// Compute the radius and height of the first point of each one of the spirals which, when combined, create the spring
		float h = r * glm::sin(i * unitAngle);
		float R = mR - r * glm::cos(i * unitAngle);

		// Create the spiral
		for (int j = 0, const base = i * precision * spires; j < precision * spires; ++j) {
			glm::vec3 center = glm::vec3(mR * glm::cos(j * unitAngle), unitHeight * j, mR * glm::sin(j * unitAngle)); // center of the current circle

			vertices[base + j].pos = glm::vec3(R * glm::cos(j * unitAngle), h + j * unitHeight, R * glm::sin(j * unitAngle));
			vertices[base + j].norm = vertices[base + j].pos - center;

			// Vertices for the "closing" faces (they will be in position (precision-1) * spires * precision + precision * spires, alternated one for the bottom face and one for the top one)
			if (j == 0 || j == precision * spires - 1) {
				vertices.push_back(Vertex(glm::vec3(R * glm::cos(j * unitAngle), h + j * unitHeight, R * glm::sin(j * unitAngle)), glm::vec3(0.0f, 0.0f, j == 0 ? -1.0f : 1.0f)));
			}
		}
	}
	const int cfOffset = precision * spires * precision; // offste for the vertices of the closing faces (look at loop above to understand why)

	// Add center vertices in order to "close" the spring
	vertices.push_back(Vertex(glm::vec3(mR, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	vertices.push_back(Vertex(glm::vec3(mR * glm::cos(unitAngle * (precision - 1)), height - unitHeight, mR * glm::sin(unitAngle * (precision - 1))), glm::vec3(0.0f, 0.0f, 1.0f)));


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
		indices.push_back(i * 2 + cfOffset); indices.push_back((i + 1) * 2 + cfOffset); indices.push_back(cfOffset + 2 * precision);
		indices.push_back(i * 2 + 1 + cfOffset); indices.push_back((i + 1) * 2 + 1 + cfOffset); indices.push_back(cfOffset + 2 * precision + 1);
	}
	// Last faces
	indices.push_back((precision - 2) * 2 + cfOffset); indices.push_back(cfOffset); indices.push_back(cfOffset + 2 * precision);
	indices.push_back((precision - 2) * 2 + 1 +cfOffset); indices.push_back(cfOffset + 1); indices.push_back(cfOffset + 2 * precision + 1);
	
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
	auto cilinderData = makeCilinder(100, 0.5f, 1.0f);
	M2_vertices = cilinderData.first;
	M2_indices = cilinderData.second;


	//// M3 : Sphere
	auto sphereData = makeSphere(100, 0.5f);
	M3_vertices = sphereData.first;
	M3_indices = sphereData.second;


	//// M4 : Spring
	auto springData = makeSpring(100, 4, 2.0f);
	M4_vertices = springData.first;
	M4_indices = springData.second;
}