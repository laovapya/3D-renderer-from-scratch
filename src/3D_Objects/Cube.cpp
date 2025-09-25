#include "Cube.h"
#include "VertexData.h"

Cube::Cube()
	: Object3D()
{

	objectType = cube;
	SetVAO(0);
}
VAO Cube::GenerateVAO(int& indexCount, int segmentCount) const
{
	float vertices[] = {
		// Positions
		-0.5f, -0.5f, -0.5f, // 0
		0.5f,  -0.5f, -0.5f, // 1
		0.5f,  0.5f,  -0.5f, // 2
		-0.5f, 0.5f,  -0.5f, // 3

		-0.5f, -0.5f, 0.5f, // 4
		0.5f,  -0.5f, 0.5f, // 5
		0.5f,  0.5f,  0.5f, // 6
		-0.5f, 0.5f,  0.5f, // 7

		-0.5f, -0.5f, -0.5f, // 8
		-0.5f, 0.5f,  -0.5f, // 9
		-0.5f, 0.5f,  0.5f, // 10
		-0.5f, -0.5f, 0.5f, // 11

		0.5f,  -0.5f, -0.5f, // 12
		0.5f,  0.5f,  -0.5f, // 13
		0.5f,  0.5f,  0.5f, // 14
		0.5f,  -0.5f, 0.5f, // 15

		-0.5f, -0.5f, -0.5f, // 16
		0.5f,  -0.5f, -0.5f, // 17
		0.5f,  -0.5f, 0.5f, // 18
		-0.5f, -0.5f, 0.5f, // 19

		-0.5f, 0.5f,  -0.5f, // 20
		0.5f,  0.5f,  -0.5f, // 21
		0.5f,  0.5f,  0.5f, // 22
		-0.5f, 0.5f,  0.5f // 23
	};
	float normals[] = {
		// Back face (0-3) - Negative Z
		0.0f,
		0.0f,
		-1.0f, // 0
		0.0f,
		0.0f,
		-1.0f, // 1
		0.0f,
		0.0f,
		-1.0f, // 2
		0.0f,
		0.0f,
		-1.0f, // 3

		// Front face (4-7) - Positive Z
		0.0f,
		0.0f,
		1.0f, // 4
		0.0f,
		0.0f,
		1.0f, // 5
		0.0f,
		0.0f,
		1.0f, // 6
		0.0f,
		0.0f,
		1.0f, // 7

		// Left face (8-11) - Negative X
		-1.0f,
		0.0f,
		0.0f, // 8
		-1.0f,
		0.0f,
		0.0f, // 9
		-1.0f,
		0.0f,
		0.0f, // 10
		-1.0f,
		0.0f,
		0.0f, // 11

		// Right face (12-15) - Positive X
		1.0f,
		0.0f,
		0.0f, // 12
		1.0f,
		0.0f,
		0.0f, // 13
		1.0f,
		0.0f,
		0.0f, // 14
		1.0f,
		0.0f,
		0.0f, // 15

		// Bottom face (16-19) - Negative Y
		0.0f,
		-1.0f,
		0.0f, // 16
		0.0f,
		-1.0f,
		0.0f, // 17
		0.0f,
		-1.0f,
		0.0f, // 18
		0.0f,
		-1.0f,
		0.0f, // 19

		// Top face (20-23) - Positive Y
		0.0f,
		1.0f,
		0.0f, // 20
		0.0f,
		1.0f,
		0.0f, // 21
		0.0f,
		1.0f,
		0.0f, // 22
		0.0f,
		1.0f,
		0.0f // 23
	};
	int indices[] = {// Back face
					 0,
					 1,
					 2,
					 2,
					 3,
					 0,

					 // Front face
					 4,
					 5,
					 6,
					 6,
					 7,
					 4,

					 // Left face
					 8,
					 9,
					 10,
					 10,
					 11,
					 8,

					 // Right face
					 12,
					 13,
					 14,
					 14,
					 15,
					 12,

					 // Bottom face
					 16,
					 17,
					 18,
					 18,
					 19,
					 16,

					 // Top face
					 20,
					 21,
					 22,
					 22,
					 23,
					 20};
	float texCoords[] = {// back face
						 0.0f,
						 0.0f, // bottom-left
						 1.0f,
						 0.0f, // bottom-right
						 1.0f,
						 1.0f, // top-right
						 0.0f,
						 1.0f, // top-left

						 // front face
						 0.0f,
						 0.0f,
						 1.0f,
						 0.0f,
						 1.0f,
						 1.0f,
						 0.0f,
						 1.0f,

						 // left face
						 0.0f,
						 0.0f,
						 1.0f,
						 0.0f,
						 1.0f,
						 1.0f,
						 0.0f,
						 1.0f,

						 // right face
						 0.0f,
						 0.0f,
						 1.0f,
						 0.0f,
						 1.0f,
						 1.0f,
						 0.0f,
						 1.0f,

						 // bottom face
						 0.0f,
						 0.0f,
						 1.0f,
						 0.0f,
						 1.0f,
						 1.0f,
						 0.0f,
						 1.0f,

						 // top face
						 0.0f,
						 0.0f,
						 1.0f,
						 0.0f,
						 1.0f,
						 1.0f,
						 0.0f,
						 1.0f};
	VBO vbo1(vertices, sizeof(float) * 24 * 3);
	//std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals, sizeof(float) * 24 * 3);
	VBO vbo3(texCoords, sizeof(float) * 24 * 2); //2 floats per UV

	indexCount = 3 * 2 * 6;
	EBO ebo(indices, sizeof(int) * indexCount);

	VAO cubeVAO;
	cubeVAO.Link(vbo1, vbo2, vbo3, ebo);

	return cubeVAO;
}
