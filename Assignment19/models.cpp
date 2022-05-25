// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices

struct Vertex {
	Vertex() = default; // default ctor
	Vertex(const Vertex&) = default; // default copy ctor
	Vertex(Vertex&&) = default; // default move ctor
	~Vertex() = default; // default dtor
	Vertex& operator= (const Vertex&) = default; // default copy assignment
	Vertex& operator= (Vertex&&) = default; // default move assignment

	Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 UV) {
		this->pos = pos;
		this->norm = norm;
		this->UV = UV;
	}

	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 UV;
};

std::vector<Vertex> M1_vertices;
std::vector<Vertex> M2_vertices;


// Overloaded string literal to make it easier to work with the texture
float operator "" _tu(long double x) {
	return x * (1.0f / 8);
}


std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeDice(float side = 1.0f) {
	auto forwards = glm::vec3(0.0f, 0.0f, 1.0f);
	auto backwards = glm::vec3(0.0f, 0.0f, -1.0f);
	auto top = glm::vec3(0.0f, 1.0f, 0.0f);
	auto bottom = glm::vec3(0.0f, -1.0f, 0.0f);
	auto right = glm::vec3(1.0f, 0.0f, 0.0f);
	auto left = glm::vec3(-1.0f, 0.0f, 0.0f);

	float textureUnit = 1.0f / 8;

	auto vertices = std::vector<Vertex>(24);

	// back face
	vertices[0].pos = glm::vec3(-side, -side, -side);	vertices[0].UV = glm::vec2(1.0_tu, 0.0_tu);
	vertices[1].pos = glm::vec3(side, -side, -side);	vertices[1].UV = glm::vec2(2.0_tu, 0.0_tu);
	vertices[2].pos = glm::vec3(side, side, -side);		vertices[2].UV = glm::vec2(2.0_tu, 1.0_tu);
	vertices[3].pos = glm::vec3(-side, side, -side);	vertices[3].UV = glm::vec2(1.0_tu, 1.0_tu);
	vertices[0].norm = vertices[1].norm = vertices[2].norm = vertices[3].norm = backwards;

	// front face
	vertices[4].pos = glm::vec3(-side, -side, side);	vertices[4].UV = glm::vec2(1.0_tu, 3.0_tu);
	vertices[5].pos = glm::vec3(side, -side, side);		vertices[5].UV = glm::vec2(2.0_tu, 3.0_tu);
	vertices[6].pos = glm::vec3(side, side, side);		vertices[6].UV = glm::vec2(2.0_tu, 2.0_tu);
	vertices[7].pos = glm::vec3(-side, side, side);		vertices[7].UV = glm::vec2(1.0_tu, 2.0_tu);
	vertices[4].norm = vertices[5].norm = vertices[6].norm = vertices[7].norm = forwards;

	// top face
	vertices[8].pos = glm::vec3(-side, side, side);	 	vertices[8].UV = glm::vec2(1.0_tu, 2.0_tu);
	vertices[9].pos = glm::vec3(side, side, side);	 	vertices[9].UV = glm::vec2(2.0_tu, 2.0_tu);
	vertices[10].pos = glm::vec3(side, side, -side); 	vertices[10].UV = glm::vec2(2.0_tu, 1.0_tu);
	vertices[11].pos = glm::vec3(-side, side, -side);	vertices[11].UV = glm::vec2(1.0_tu, 1.0_tu);
	vertices[8].norm = vertices[9].norm = vertices[10].norm = vertices[11].norm = top;

	// bottom face
	vertices[12].pos = glm::vec3(-side, -side, side); 	vertices[12].UV = glm::vec2(1.0_tu, 3.0_tu);
	vertices[13].pos = glm::vec3(side, -side, side);  	vertices[13].UV = glm::vec2(2.0_tu, 3.0_tu);
	vertices[14].pos = glm::vec3(side, -side, -side); 	vertices[14].UV = glm::vec2(2.0_tu, 4.0_tu);
	vertices[15].pos = glm::vec3(-side, -side, -side);	vertices[15].UV = glm::vec2(1.0_tu, 4.0_tu);
	vertices[12].norm = vertices[13].norm = vertices[14].norm = vertices[15].norm = bottom;

	// right face
	vertices[16].pos = glm::vec3(side, -side, side); 	vertices[16].UV = glm::vec2(2.0_tu, 3.0_tu);
	vertices[17].pos = glm::vec3(side, -side, -side);	vertices[17].UV = glm::vec2(3.0_tu, 3.0_tu);
	vertices[18].pos = glm::vec3(side, side, -side); 	vertices[18].UV = glm::vec2(3.0_tu, 2.0_tu);
	vertices[19].pos = glm::vec3(side, side, side);	 	vertices[19].UV = glm::vec2(2.0_tu, 2.0_tu);
	vertices[16].norm = vertices[17].norm = vertices[18].norm = vertices[19].norm = right;

	// left face
	vertices[20].pos = glm::vec3(-side, -side, side); 	vertices[20].UV = glm::vec2(1.0_tu, 3.0_tu);
	vertices[21].pos = glm::vec3(-side, -side, -side);	vertices[21].UV = glm::vec2(1.0_tu, 2.0_tu);
	vertices[22].pos = glm::vec3(-side, side, -side); 	vertices[22].UV = glm::vec2(0.0_tu, 2.0_tu);
	vertices[23].pos = glm::vec3(-side, side, side);  	vertices[23].UV = glm::vec2(0.0_tu, 3.0_tu);
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

std::pair<std::vector<Vertex>, std::vector<uint32_t>> makeCoke(int precision, float radius = 1.0f, float height = 2.0f) {
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
		vertices[i * 2].UV = glm::vec2(8.0_tu - ((float)i / precision) * 4.0_tu, 4.0_tu);
		vertices[i * 2 + tbfOffset].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		vertices[i * 2 + tbfOffset].UV = glm::vec2(-1.0_tu * glm::cos(unitAngle * i) + 7.0_tu, -1.0_tu * glm::sin(unitAngle * i) + 1.0_tu);
		// Top
		vertices[i * 2 + 1].pos = vertices[i * 2 + 1 + tbfOffset].pos = glm::vec3(vertices[i * 2].pos.x, -vertices[i * 2].pos.y, vertices[i * 2].pos.z);
		vertices[i * 2 + 1].norm = vertices[i * 2 + 1].pos - centerTop;
		vertices[i * 2 + 1].UV = glm::vec2(8.0_tu - ((float)i / precision) * 4.0_tu, 2.0_tu);
		vertices[i * 2 + 1 + tbfOffset].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i * 2 + 1 +tbfOffset].UV = glm::vec2(-1.0_tu * glm::cos(unitAngle * i) + 5.0_tu, -1.0_tu * glm::sin(unitAngle * i) + 1.0_tu);
	}

	// Add the center of the top and bottom face vertices
	vertices.push_back(Vertex(centerBottom, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(7.0_tu, 1.0_tu)));
	vertices.push_back(Vertex(centerTop, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(5.0_tu, 1.0_tu)));


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


void makeModels() {
	// Dice
	auto cubeData = makeDice(0.5f);
	M1_vertices = cubeData.first;
	M1_indices = cubeData.second;


	// Coke
	auto cilinderData = makeCoke(100, 0.5f, 2.0f);
	M2_vertices = cilinderData.first;
	M2_indices = cilinderData.second;

}