#include "Cone.h"
#include "VertexData.h"
Cone::Cone(int segmentCount)
	: Object3D()
{

	objectType = cone;
	SetVAO(segmentCount);
}

VAO Cone::GenerateVAO(int& indexCount, int segmentCount) const
{
	const float PI = 3.14159265359f;
	const float radius = 0.5f;

	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<int> indices;

	auto pushVertex = [&](const Vector3& v, float u, float vv) {
		vertices.push_back(v.x);
		vertices.push_back(v.y);
		vertices.push_back(v.z);
		texCoords.push_back(u);
		texCoords.push_back(vv);
	};

	// bottom center
	pushVertex({0, -0.5f, 0}, 0.5f, 0.5f);
	int bottomCenterIndex = 0;
	int sideStartIndex = 1;

	for(int i = 0; i <= segmentCount; ++i)
	{
		int idx = i % segmentCount;
		float angle = 2 * PI * idx / segmentCount;
		Vector3 bottom{radius * cos(angle), -0.5f, radius * sin(angle)};
		Vector3 top{0.0f, 0.5f, 0.0f};

		float u = (float)i / segmentCount;
		pushVertex(bottom, u, 0.0f);
		pushVertex(top, u, 1.0f);
	}

	for(int i = 0; i < segmentCount; ++i)
	{
		int b0 = sideStartIndex + i * 2;
		int t0 = b0 + 1;
		int b1 = sideStartIndex + (i + 1) * 2;

		indices.push_back(b0);
		indices.push_back(b1);
		indices.push_back(t0);
	}

	for(int i = 0; i < segmentCount; ++i)
	{
		int b0 = sideStartIndex + i * 2;
		int b1 = sideStartIndex + (i + 1) * 2;
		indices.push_back(b1);
		indices.push_back(b0);
		indices.push_back(bottomCenterIndex);
	}

	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	VBO vbo3(texCoords.data(), sizeof(float) * texCoords.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());

	VAO coneVAO;
	coneVAO.Link(vbo1, vbo2, vbo3, ebo);
	indexCount = indices.size();
	return coneVAO;
}
