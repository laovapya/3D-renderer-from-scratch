#include "Cylinder.h"
#include "VertexData.h"
Cylinder::Cylinder(int segmentCount)
	: Object3D()
{

	objectType = cylinder;
	SetVAO(segmentCount);
}
VAO Cylinder::GenerateVAO(int& indexCount, int segmentCount) const
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

	// centers
	pushVertex({0, -0.5f, 0}, 0.5f, 0.5f);
	pushVertex({0, 0.5f, 0}, 0.5f, 0.5f);

	int sideStartIndex = 2;

	// side vertices with duplicate for seam fix
	for(int i = 0; i <= segmentCount; ++i)
	{
		int idx = i % segmentCount;
		float angle = 2 * PI * idx / segmentCount;
		Vector3 bottom{radius * cos(angle), -0.5f, radius * sin(angle)};
		Vector3 top{radius * cos(angle), 0.5f, radius * sin(angle)};
		float u = (float)i / segmentCount;
		pushVertex(bottom, u, 0.0f);
		pushVertex(top, u, 1.0f);
	}

	int bottomOffset = sideStartIndex + 2 * (segmentCount + 1);
	int topOffset = bottomOffset + segmentCount;

	// unique bottom vertices
	for(int i = 0; i < segmentCount; ++i)
	{
		float angle = 2 * PI * i / segmentCount;
		Vector3 v{radius * cos(angle), -0.5f, radius * sin(angle)};
		pushVertex(v, cos(angle) * 0.5f + 0.5f, sin(angle) * 0.5f + 0.5f);
	}

	// unique top vertices
	for(int i = 0; i < segmentCount; ++i)
	{
		float angle = 2 * PI * i / segmentCount;
		Vector3 v{radius * cos(angle), 0.5f, radius * sin(angle)};
		pushVertex(v, cos(angle) * 0.5f + 0.5f, sin(angle) * 0.5f + 0.5f);
	}

	// side indices
	for(int i = 0; i < segmentCount; ++i)
	{
		int b0 = sideStartIndex + i * 2;
		int t0 = b0 + 1;
		int b1 = sideStartIndex + (i + 1) * 2;
		int t1 = b1 + 1;

		indices.push_back(b0);
		indices.push_back(b1);
		indices.push_back(t0);
		indices.push_back(t0);
		indices.push_back(b1);
		indices.push_back(t1);
	}

	for(int i = 0; i < segmentCount; ++i)
	{
		int next = (i + 1) % segmentCount;
		indices.push_back(0); // bottom center
		indices.push_back(bottomOffset + next);
		indices.push_back(bottomOffset + i);

		indices.push_back(1); // top center
		indices.push_back(topOffset + i);
		indices.push_back(topOffset + next);
	}

	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	VBO vbo3(texCoords.data(), sizeof(float) * texCoords.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());

	VAO cylinderVAO;
	cylinderVAO.Link(vbo1, vbo2, vbo3, ebo);
	indexCount = indices.size();
	return cylinderVAO;
}
