#include "VertexData.h"



const float pi = 3.14159265358979323846;
float DegToRad(float angle) {
	return angle * pi / 180;
}
float VertexData::degToRad = pi / 180;
//float  VertexData::cubeVertices[36];
//float  VertexData::cubeIndices[12];
//VAO  VertexData::cubeVAO;
//const int VertexData::CUBE_VERTEX_COUNT = 36;
//const int VertexData::CUBE_INDEX_COUNT = 12;
VertexData::VertexData() {
	if (polygonAmount < 1) polygonAmount = 1;
	if (polygonAmount > 10) polygonAmount = 10;
	SetCubeVAO();
	SetConeVAO();
	SetCylinderVAO();
	SetSphereVAO();
	SetGridVAO();
}
VAO VertexData::GetCubeVAO() {
	return GetInstance().cubeVAO;
}
VAO VertexData::GetConeVAO() {
	return GetInstance().coneVAO;
}
VAO VertexData::GetCylinderVAO() {
	return GetInstance().cylinderVAO;
}
VAO VertexData::GetSphereVAO() {
	return GetInstance().sphereVAO;
}
void VertexData::SetCubeVAO() {

	float vertices[] = {
		// Positions           
		-0.5f, -0.5f, -0.5f,  // 0
		 0.5f, -0.5f, -0.5f,  // 1
		 0.5f,  0.5f, -0.5f,  // 2
		-0.5f,  0.5f, -0.5f,  // 3

		-0.5f, -0.5f,  0.5f,  // 4
		 0.5f, -0.5f,  0.5f,  // 5
		 0.5f,  0.5f,  0.5f,  // 6
		-0.5f,  0.5f,  0.5f,  // 7

		-0.5f, -0.5f, -0.5f,  // 8
		-0.5f,  0.5f, -0.5f,  // 9
		-0.5f,  0.5f,  0.5f,  // 10
		-0.5f, -0.5f,  0.5f,  // 11

		 0.5f, -0.5f, -0.5f,  // 12
		 0.5f,  0.5f, -0.5f,  // 13
		 0.5f,  0.5f,  0.5f,  // 14
		 0.5f, -0.5f,  0.5f,  // 15

		-0.5f, -0.5f, -0.5f,  // 16
		 0.5f, -0.5f, -0.5f,  // 17
		 0.5f, -0.5f,  0.5f,  // 18
		-0.5f, -0.5f,  0.5f,  // 19

		-0.5f,  0.5f, -0.5f,  // 20
		 0.5f,  0.5f, -0.5f,  // 21
		 0.5f,  0.5f,  0.5f,  // 22
		-0.5f,  0.5f,  0.5f  // 23
	};
	float normals[] = {
		// Back face (0-3) - Negative Z
		0.0f,  0.0f, -1.0f,  // 0
		0.0f,  0.0f, -1.0f,  // 1
		0.0f,  0.0f, -1.0f,  // 2
		0.0f,  0.0f, -1.0f,  // 3

		// Front face (4-7) - Positive Z
		0.0f,  0.0f,  1.0f,  // 4
		0.0f,  0.0f,  1.0f,  // 5
		0.0f,  0.0f,  1.0f,  // 6
		0.0f,  0.0f,  1.0f,  // 7

		// Left face (8-11) - Negative X
		-1.0f,  0.0f,  0.0f,  // 8
		-1.0f,  0.0f,  0.0f,  // 9
		-1.0f,  0.0f,  0.0f,  // 10
		-1.0f,  0.0f,  0.0f,  // 11

		// Right face (12-15) - Positive X
		1.0f,  0.0f,  0.0f,  // 12
		1.0f,  0.0f,  0.0f,  // 13
		1.0f,  0.0f,  0.0f,  // 14
		1.0f,  0.0f,  0.0f,  // 15

		// Bottom face (16-19) - Negative Y
		0.0f, -1.0f,  0.0f,  // 16
		0.0f, -1.0f,  0.0f,  // 17
		0.0f, -1.0f,  0.0f,  // 18
		0.0f, -1.0f,  0.0f,  // 19

		// Top face (20-23) - Positive Y
		0.0f,  1.0f,  0.0f,  // 20
		0.0f,  1.0f,  0.0f,  // 21
		0.0f,  1.0f,  0.0f,  // 22
		0.0f,  1.0f,  0.0f   // 23
	};
	int indices[] = {
		// Back face
		0, 1, 2,  2, 3, 0,

		// Front face
		4, 5, 6,  6, 7, 4,

		// Left face
		8, 9, 10,  10, 11, 8,

		// Right face
		12, 13, 14,  14, 15, 12,

		// Bottom face
		16, 17, 18,  18, 19, 16,

		// Top face
		20, 21, 22,  22, 23, 20
	};
	VBO vbo1(vertices, sizeof(float) * 24 * 3);
	//std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals, sizeof(float) * 24 * 3);
	EBO ebo(indices, sizeof(int) * 3 * 6 * 2);
	cubeVAO.Link(vbo1, vbo2, ebo);
	cubeIndexCount = 36;
}

void VertexData::SetConeVAO() {
	int angle = 360 / (360 / (100 / polygonAmount));
	int triangleCount = 360 / angle;

	std::vector<float> vertices;
	std::vector<int> indices;

	// add top and bottom center points
	vertices.insert(vertices.end(), { 0, 0.5f, 0 });  // top vertex
	vertices.insert(vertices.end(), { 0, -0.5f, 0 }); // bottom center

	// add side vertices for bottom, up face normals
	for (int i = 0; i < 360; i += angle) {
		float x = 0.5f * cos(DegToRad(i));
		float y = -0.5f;
		float z = 0.5f * sin(DegToRad(i));
		vertices.insert(vertices.end(), { x, y, z });
	}

	// add side vertices again, for side normals
	for (int i = 0; i < 360; i += angle) {
		float x = 0.5f * cos(DegToRad(i));
		float y = -0.5f;
		float z = 0.5f * sin(DegToRad(i));
		vertices.insert(vertices.end(), { x, y, z });
	}

	// indices for top triangles
	for (int i = 2; i < 2 + triangleCount; ++i) 
		indices.insert(indices.end(), { 0, i, (i + 1 == 2 + triangleCount) ? 2 : i + 1 });
	

	// indices for bottom triangles
	for (int i = 2 + triangleCount; i < 2 + 2 * triangleCount; ++i) 
		indices.insert(indices.end(), { (i + 1 == 2 + 2 * triangleCount) ? 2 + triangleCount : i + 1, i, 1 });
	

	
	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());
	coneVAO.Link(vbo1, vbo2, ebo);
	ConeIndexCount = indices.size();
}



void VertexData::SetCylinderVAO() {
	int angle = (int)(360 / (360 / (100 / polygonAmount)));
	std::vector<float> vertices;
	int planeTriangleCount = 360 / angle;

	// Center points for top and bottom
	vertices.insert(vertices.end(), { 0.0f, -0.5f, 0.0f }); // Bottom center
	vertices.insert(vertices.end(), { 0.0f,  0.5f, 0.0f }); // Top center

	// Generate perimeter vertices
	for (int i = 0; i < 360; i += angle) {
		float x = 0.5f * cos(DegToRad(i));
		float z = 0.5f * sin(DegToRad(i));

		// Bottom vertex
		vertices.push_back(x);
		vertices.push_back(-0.5f);
		vertices.push_back(z);

		// Top vertex (added later after all bottom vertices)
	}

	// Add top vertices (after all bottom vertices are added)
	for (int i = 0; i < planeTriangleCount; i++) {
		int bottomVertexPos = 6 + i * 3;
		vertices.push_back(vertices[bottomVertexPos]);    
		vertices.push_back(0.5f);                         
		vertices.push_back(vertices[bottomVertexPos + 2]); 
	}
	//repeat for unique normals
	for (int i = 0; i < planeTriangleCount; i++) {
		int bottomVertexPos = 6 + i * 3;
		vertices.push_back(vertices[bottomVertexPos]);    
		vertices.push_back(-0.5f);                         
		vertices.push_back(vertices[bottomVertexPos + 2]); 
	}
	for (int i = 0; i < planeTriangleCount; i++) {
		int bottomVertexPos = 6 + i * 3;
		vertices.push_back(vertices[bottomVertexPos]);     
		vertices.push_back(0.5f);                         
		vertices.push_back(vertices[bottomVertexPos + 2]); 
	}
	//----------

	std::vector<int> indices;


	// Side triangles
	for (int i = 0; i < planeTriangleCount; i++) {
		int next = (i + 1) % planeTriangleCount;
		indices.push_back(2 + i);
		indices.push_back(2 + next);
		indices.push_back(2 + i + planeTriangleCount);

		indices.push_back(2 + i + planeTriangleCount);
		indices.push_back(2 + next);
		indices.push_back(2 + next + planeTriangleCount);
	}


	// Bottom face triangles
	for (int i = 2 * planeTriangleCount; i < 3 * planeTriangleCount; i++) {
		indices.push_back(0);
		indices.push_back(2 + (i + 1) % planeTriangleCount + 2 * planeTriangleCount);
		indices.push_back(2 + i);
	}

	// Top face triangles
	for (int i = 3 * planeTriangleCount; i < 4 * planeTriangleCount; i++) {
		indices.push_back(1);
		indices.push_back(2 + i );
		indices.push_back(2 + (i + 1) % planeTriangleCount + 3 * planeTriangleCount);
	}

	





	VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
	std::vector<float> normals = CalculateNormals(vertices, indices);
	VBO vbo2(normals.data(), sizeof(float) * normals.size());
	EBO ebo(indices.data(), sizeof(int) * indices.size());
	cylinderVAO.Link(vbo1, vbo2, ebo);
	CylinderIndexCount = indices.size();
	
}


void VertexData::SetSphereVAO() {
	int stacks = 15;
	int slices = 15;
	float radius = 0.5f;
	const float PI = 3.14159265358979323846f;

	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<int> indices;

	// Generate vertices and normals
	for (int i = 0; i <= stacks; ++i) {
		float V = (float)i / (float)stacks;
		float phi = V * PI;

		for (int j = 0; j <= slices; ++j) {
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
	for (int i = 0; i < slices * stacks + slices; ++i) {
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

	sphereVAO.Link(vbo1, vbo2, ebo);
	SphereIndexCount = indices.size();
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
int VertexData::GetCubeIndexCount() {
	return GetInstance().cubeIndexCount;//36;
}
int VertexData::GetConeIndexCount() {
	return GetInstance().ConeIndexCount;//(360 / GetInstance().polygonAmount) * 3 * 2; 
}
int VertexData::GetCylinderIndexCount() {
	return GetInstance().CylinderIndexCount;//4 * (360 / GetInstance().polygonAmount) * 3; 
}
int VertexData::GetSphereIndexCount() {
	return GetInstance().SphereIndexCount;//2400;
}










// Calculates normals for a triangle mesh using cross products
std::vector<float> VertexData::CalculateNormals(const std::vector<float>& vertices, const std::vector<int>& indices)
{
	std::vector<glm::vec3> normalsVec3(vertices.size() / 3, glm::vec3(0.0f));

	// each triangle
	for (size_t i = 0; i < indices.size(); i += 3) {
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		glm::vec3 v0(vertices[i0 * 3], vertices[i0 * 3 + 1], vertices[i0 * 3 + 2]);
		glm::vec3 v1(vertices[i1 * 3], vertices[i1 * 3 + 1], vertices[i1 * 3 + 2]);
		glm::vec3 v2(vertices[i2 * 3], vertices[i2 * 3 + 1], vertices[i2 * 3 + 2]);

		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;

		glm::vec3 faceNormal = -glm::normalize(glm::cross(edge1, edge2));

		normalsVec3[i0] += faceNormal;
		normalsVec3[i1] += faceNormal;
		normalsVec3[i2] += faceNormal;
	}

	std::vector<float> normals;
	normals.reserve(vertices.size()); 

	for (auto& normal : normalsVec3) {
		glm::vec3 normalized = glm::normalize(normal);
		normals.push_back(normalized.x);
		normals.push_back(normalized.y);
		normals.push_back(normalized.z);
	}

	return normals;
}


//
//std::vector<float> VertexData::CombineVerticesNormals(const std::vector<float>& vertices, const std::vector<glm::vec3>& normals, const std::vector<int>& indices)
//{
//	// Validate input sizes
//	if (vertices.size() / 3 != normals.size()) {
//		throw std::runtime_error("Vertex and normal counts must match");
//	}
//	if (indices.size() % 3 != 0) {
//		throw std::runtime_error("Indices must represent complete triangles");
//	}
//
//	std::vector<float> combinedData;
//	combinedData.reserve(indices.size() * 6); // 6 floats per vertex (3 position + 3 normal)
//
//	// Expand indexed data into non-indexed interleaved buffer
//	for (auto index : indices) {
//		// Add vertex position (x,y,z)
//		combinedData.push_back(vertices[index * 3]);
//		combinedData.push_back(vertices[index * 3 + 1]);
//		combinedData.push_back(vertices[index * 3 + 2]);
//
//		// Add corresponding normal (nx,ny,nz)
//		combinedData.push_back(normals[index].x);
//		combinedData.push_back(normals[index].y);
//		combinedData.push_back(normals[index].z);
//	}
//
//	return combinedData;
//}