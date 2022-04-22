
std::pair<std::vector<float>, std::vector<uint32_t>> makeCilinder(const int precision) {
	const float unitAngle = (glm::pi<float>() * 2) / precision; // angle of each "slice" of the top and bottom face
	float r = 1.0f; // radius
	float h = 2.0f; // heigth

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
	for (int i = 0, const base = precision * 6; i < precision; ++i) {
		// Bottom
		indices[base + i * 6] = i * 2;
		indices[base + i * 6 + 1] = (i + 1) * 2;
		indices[base + i * 6 + 2] = precision * 2;

		// Top
		indices[base + i * 6 + 3] = i * 2 + 1;
		indices[base + i * 6 + 4] = (i + 1) * 2 + 1;
		indices[base + i * 6 + 5] = precision * 2 + 1;
	}

	return std::pair(vertices, indices);
}


std::pair<std::vector<float>, std::vector<uint32_t>> makeSphere(int precision) {
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

		indices[i * 6 + 3] = precision * (precision / 2 - 2) + i + 2;
		indices[i * 6 + 4] = precision * (precision / 2 - 2) + i + 3;
		indices[i * 6 + 5] = precision * (precision / 2 - 1) + 1;
	}
	// "Close" last face of each shell
	indices[(precision - 1) * 6] = precision; indices[(precision - 1) * 6 + 1] = 1; indices[(precision - 1) * 6 + 2] = 0;
	indices[(precision - 1) * 6 + 3] = precision * (precision / 2 - 1) + 1; indices[(precision - 1) * 6 + 4] = precision * (precision / 2 - 2) + 2; indices[(precision - 1) * 6 + 5] = precision * (precision / 2 - 1) + 1;
	
	// Sides
	for (int i = 1; i < precision / 2 - 1; ++i) {
		for (int j = 0, const base = 1 + (i - 1) * precision; j < precision; ++j) {
			indices[i * precision * 6 + j * 6] = base + j;
			indices[i * precision * 6 + j * 6 + 1] = base + j + precision;
			indices[i * precision * 6 + j * 6 + 2] = base + j + 1;

			indices[i * precision * 6 + j * 6 + 3] = base + j + precision;
			indices[i * precision * 6 + j * 6 + 4] = base + j + 1;
			indices[i * precision * 6 + j * 6 + 5] = base + j + 1 + precision;
		}
	}

	return std::pair(vertices, indices);
}


// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels() {
//// M1 : Cube
M1_vertices.resize(3 * 8);

M1_vertices[0] = -1.0f;
M1_vertices[1] = -1.0f;
M1_vertices[2] = -1.0f;

M1_vertices[3] = 1.0f;
M1_vertices[4] = -1.0f;
M1_vertices[5] = -1.0f;

M1_vertices[6] = 1.0f;
M1_vertices[7] = 1.0f;
M1_vertices[8] = -1.0f;

M1_vertices[9] = -1.0f;
M1_vertices[10] = 1.0f;
M1_vertices[11] = -1.0f;

M1_vertices[12] = -1.0f;
M1_vertices[13] = -1.0f;
M1_vertices[14] = 1.0f;

M1_vertices[15] = 1.0f;
M1_vertices[16] = -1.0f;
M1_vertices[17] = 1.0f;

M1_vertices[18] = 1.0f;
M1_vertices[19] = 1.0f;
M1_vertices[20] = 1.0f;

M1_vertices[21] = -1.0f;
M1_vertices[22] = 1.0f;
M1_vertices[23] = 1.0f;


M1_indices.resize(3 * 12);

M1_indices[0] = 0;
M1_indices[1] = 1;
M1_indices[2] = 2;
   
M1_indices[3] = 0;
M1_indices[4] = 2;
M1_indices[5] = 3;
   
M1_indices[6] = 0;
M1_indices[7] = 4;
M1_indices[8] = 7;
   
M1_indices[9] = 0;
M1_indices[10] = 7;
M1_indices[11] = 3;
   
M1_indices[12] = 4;
M1_indices[13] = 5;
M1_indices[14] = 6;
   
M1_indices[15] = 4;
M1_indices[16] = 6;
M1_indices[17] = 7;
   
M1_indices[18] = 1;
M1_indices[19] = 5;
M1_indices[20] = 6;
   
M1_indices[21] = 1;
M1_indices[22] = 6;
M1_indices[23] = 2;

M1_indices[24] = 0;
M1_indices[25] = 4;
M1_indices[26] = 5;

M1_indices[27] = 0;
M1_indices[28] = 5;
M1_indices[29] = 1;

M1_indices[30] = 2;
M1_indices[31] = 3;
M1_indices[32] = 6;

M1_indices[33] = 3;
M1_indices[34] = 6;
M1_indices[35] = 7;



//// M2 : Cylinder
auto cilinderData = makeCilinder(100);
M2_vertices = cilinderData.first;
M2_indices = cilinderData.second;



//// M3 : Sphere
auto sphereData = makeSphere(10);
M3_vertices = sphereData.first;
M3_indices = sphereData.second;









//// M4 : Spring
// Replace the code below, that creates a simple octahedron, with the one to create a spring.
M4_vertices.resize(3 * 6);

// Vertices definitions
M4_vertices[0]  =  0.0;
M4_vertices[1]  =  1.414;
M4_vertices[2]  = -1.0;
M4_vertices[3]  =  0.0;
M4_vertices[4]  = -1.414;
M4_vertices[5]  = -1.0;
M4_vertices[6]  = -1.0;
M4_vertices[7]  =  0.0;
M4_vertices[8]  = -2.0;
M4_vertices[9]  = -1.0;
M4_vertices[10] =  0.0;
M4_vertices[11] =  0.0;
M4_vertices[12] =  1.0;
M4_vertices[13] =  0.0;
M4_vertices[14] =  0.0;
M4_vertices[15] =  1.0;
M4_vertices[16] =  0.0;
M4_vertices[17] = -2.0;


// Resizes the indices array. Repalce the values with the correct number of
// indices (3 * number of triangles)
M4_indices.resize(3 * 8);

// indices definitions
M4_indices[0]  = 0;
M4_indices[1]  = 2;
M4_indices[2]  = 3;
M4_indices[3]  = 1;
M4_indices[4]  = 3;
M4_indices[5]  = 2;
M4_indices[6]  = 0;
M4_indices[7]  = 3;
M4_indices[8]  = 4;
M4_indices[9]  = 1;
M4_indices[10] = 4;
M4_indices[11] = 3;
M4_indices[12] = 0;
M4_indices[13] = 4;
M4_indices[14] = 5;
M4_indices[15] = 1;
M4_indices[16] = 5;
M4_indices[17] = 4;
M4_indices[18] = 0;
M4_indices[19] = 5;
M4_indices[20] = 2;
M4_indices[21] = 1;
M4_indices[22] = 2;
M4_indices[23] = 5;
}