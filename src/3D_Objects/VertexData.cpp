#include "VertexData.h"

VertexData::VertexData()
{
	SetGridVAO();
}

void VertexData::SetGridVAO()
{
	const float length = 9999.0f;
	const float spacing = gridSpacing;
	const int linesPerAxis = 250;

	std::vector<float> vertices1 = {-length, 0.0f, 0.0f, length, 0.0f, 0.0f};
	VBO vbo1(vertices1.data(), vertices1.size() * sizeof(float));
	axisX.Link(vbo1);

	std::vector<float> vertices2 = {0.0f, 0.0f, -length, 0.0f, 0.0f, length};
	VBO vbo2(vertices2.data(), vertices2.size() * sizeof(float));
	axisZ.Link(vbo2);

	std::vector<float> vertices3;
	for(int i = -linesPerAxis; i <= linesPerAxis; i++)
	{
		float x = i * spacing;
		vertices3.insert(vertices3.end(), {x, 0.0f, -length, x, 0.0f, length});
	}
	for(int i = -linesPerAxis; i <= linesPerAxis; i++)
	{
		float z = i * spacing;
		vertices3.insert(vertices3.end(), {-length, 0.0f, z, length, 0.0f, z});
	}

	VBO vbo3(vertices3.data(), vertices3.size() * sizeof(float));
	grid.Link(vbo3);
}

VAO VertexData::GetXaxisVAO()
{
	return GetInstance().axisX;
}
VAO VertexData::GetZaxisVAO()
{
	return GetInstance().axisZ;
}
VAO VertexData::GetGridVAO()
{
	return GetInstance().grid;
}

int VertexData::GetGridIndexCount()
{
	return GetInstance().maxGridSize; //doesnt use EBO
}
