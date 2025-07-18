#include "Sphere.h"
#include "VertexData.h"

Sphere::Sphere(int segmentCount)
	: Object3D()
{
	objectType = sphere;
	isLit = true;
	SetVAO(segmentCount);
}
VAO Sphere::GenerateVAO(int& indexCount, int segmentCount) const
{
	int stacks = segmentCount;
	int slices = segmentCount;
	float radius = 0.5f;
	const float PI = 3.14159265358979323846f;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<int> indices;

	// Generate vertices and normals
	for(int i = 0; i <= stacks; ++i)
	{
		float V = (float)i / (float)stacks;
		float phi = V * PI;

		for(int j = 0; j <= slices; ++j)
		{
			float U = (float)j / (float)slices;
			float theta = U * (PI * 2);

			// Vertex position
			float x = radius * cos(theta) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * sin(theta) * sin(phi);

			// Normal (same as position for a unit sphere, just normalized)
			float nx = x / radius;
			float ny = y / radius;
			float nz = z / radius;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);
		}
	}

	// Generate indices
	for(int i = 0; i < slices * stacks + slices; ++i)
	{
		indices.push_back(int(i));
		indices.push_back(int(i + slices + 1));
		indices.push_back(int(i + slices));

		indices.push_back(int(i + slices + 1));
		indices.push_back(int(i));
		indices.push_back(int(i + 1));
	}

	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());
	VAO sphereVAO;
	sphereVAO.Link(vbo1, vbo2, ebo);

	indexCount = indices.size();
	return sphereVAO;
}
