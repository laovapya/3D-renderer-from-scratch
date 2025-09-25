#include "Sphere.h"
#include "VertexData.h"

Sphere::Sphere(int segmentCount)
	: Object3D()
{
	objectType = sphere;
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
	std::vector<float> texCoords;
	std::vector<int> indices;

	auto pushVertex = [&](const Vector3& pos, const Vector3& norm, float u, float v) {
		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);
		normals.push_back(norm.x);
		normals.push_back(norm.y);
		normals.push_back(norm.z);
		texCoords.push_back(u);
		texCoords.push_back(v);
	};

	for(int i = 0; i <= stacks; ++i)
	{
		float V = (float)i / stacks;
		float phi = V * PI;

		for(int j = 0; j <= slices; ++j)
		{
			float U = (float)j / slices;
			float theta = U * 2.0f * PI;

			Vector3 pos{
				radius * cos(theta) * sin(phi), radius * cos(phi), radius * sin(theta) * sin(phi)};
			Vector3 norm{pos.x / radius, pos.y / radius, pos.z / radius};

			pushVertex(pos, norm, U, 1.0f - V);
		}
	}

	for(int i = 0; i < slices * stacks + slices; ++i)
	{
		indices.push_back(i);
		indices.push_back(i + slices + 1);
		indices.push_back(i + slices);
		indices.push_back(i + slices + 1);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	VBO vbo3(texCoords.data(), sizeof(float) * texCoords.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());

	VAO sphereVAO;
	sphereVAO.Link(vbo1, vbo2, vbo3, ebo);

	indexCount = indices.size();
	return sphereVAO;
}
