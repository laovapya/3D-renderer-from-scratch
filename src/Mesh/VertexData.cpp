#include "VertexData.h"


VertexData::VertexData() { 
	SetGridVAO();
}



void VertexData::SetGridVAO() {
	const float length = 9999.0f;
	const float spacing = gridSpacing;
	const int amount = maxGridSize;

	// X-axis line (red)
	std::vector<float> vertices1 = {
		-length, 0.0f, 0.0f,
		 length, 0.0f, 0.0f
	};
	VBO vbo1(vertices1.data(), vertices1.size() * sizeof(float));
	axisX.Link(vbo1);

	// Z-axis line (blue)
	std::vector<float> vertices2 = {
		0.0f, 0.0f, -length,
		0.0f, 0.0f,  length
	};
	VBO vbo2(vertices2.data(), vertices2.size() * sizeof(float));
	axisZ.Link(vbo2);

	// Grid lines
	std::vector<float> vertices3;
	vertices3.reserve(amount); // Pre-allocate memory for better performance

	// Vertical grid lines (parallel to Z-axis)
	for (int i = 0; i < amount / 2; i += 6) {
		float zPos = spacing * (i / 6 - 125);
		vertices3.insert(vertices3.end(), {
			-length, 0.0f, zPos,
			 length, 0.0f, zPos
			});
	}

	// Horizontal grid lines (parallel to X-axis)
	for (int i = amount / 2; i < amount; i += 6) {
		float xPos = spacing * ((i - amount / 2) / 6 - 125);
		vertices3.insert(vertices3.end(), {
			xPos, 0.0f, -length,
			xPos, 0.0f,  length
			});
	}

	VBO vbo3(vertices3.data(), vertices3.size() * sizeof(float));
	grid.Link(vbo3);
}

VAO VertexData::GetXaxisVAO() {
	return GetInstance().axisX;
}
VAO VertexData::GetZaxisVAO() {
	return GetInstance().axisZ;
}
VAO VertexData::GetGridVAO() {
	return GetInstance().grid;
}




int VertexData::GetGridIndexCount() {
	return GetInstance().maxGridSize; //doesnt use EBO 
}






