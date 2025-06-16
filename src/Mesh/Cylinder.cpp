#include "Cylinder.h"
#include "VertexData.h"
Cylinder::Cylinder(int segmentCount) : Object3D() {

	objectType = cylinder;
	isLit = true;
    SetVAO(segmentCount);
}
VAO Cylinder::GenerateVAO(int& indexCount, int segmentCount) const {
    const float PI = 3.14159265359f;

    std::vector<float> vertices;

    // center points for bottom and top
    vertices.insert(vertices.end(), { 0.0f, -0.5f, 0.0f }); // bottom center
    vertices.insert(vertices.end(), { 0.0f,  0.5f,  0.0f }); // top center

    // perimeter bottom vertices
    for (int i = 0; i < segmentCount; ++i) {
        float angle = (2 * PI * i) / segmentCount;  
        float x = 0.5f * cos(angle);
        float z = 0.5f * sin(angle);

        vertices.push_back(x);
        vertices.push_back(-0.5f);
        vertices.push_back(z);
    }

    // perimeter top vertices
    for (int i = 0; i < segmentCount; ++i) {
        float angle = (2 * PI * i) / segmentCount;
        float x = 0.5f * cos(angle);
        float z = 0.5f * sin(angle);

        vertices.push_back(x);
        vertices.push_back(0.5f);
        vertices.push_back(z);
    }

    // unique vertices for normals (bottom)
    for (int i = 0; i < segmentCount; ++i) {
        float angle = (2 * PI * i) / segmentCount;
        float x = 0.5f * cos(angle);
        float z = 0.5f * sin(angle);

        vertices.push_back(x);
        vertices.push_back(-0.5f);
        vertices.push_back(z);
    }

    // unique vertices for normals (top)
    for (int i = 0; i < segmentCount; ++i) {
        float angle = (2 * PI * i) / segmentCount;
        float x = 0.5f * cos(angle);
        float z = 0.5f * sin(angle);

        vertices.push_back(x);
        vertices.push_back(0.5f);
        vertices.push_back(z);
    }

    std::vector<int> indices;

    // side triangles
    for (int i = 0; i < segmentCount; ++i) {
        int next = (i + 1) % segmentCount;
        indices.push_back(2 + i);                      // bottom current
        indices.push_back(2 + next);                   // bottom next
        indices.push_back(2 + i + segmentCount);      // top current

        indices.push_back(2 + i + segmentCount);      // top current
        indices.push_back(2 + next);                   // bottom next
        indices.push_back(2 + next + segmentCount);   // top next
    }

    // bottom face triangles
    for (int i = 0; i < segmentCount; ++i) {
        int next = (i + 1) % segmentCount;
        indices.push_back(0);                          // bottom center
        indices.push_back(2 + next + 2 * segmentCount); // unique bottom next
        indices.push_back(2 + i + 2 * segmentCount);  // unique bottom current
    }

    // top face triangles
    for (int i = 0; i < segmentCount; ++i) {
        int next = (i + 1) % segmentCount;
        indices.push_back(1);                          // top center
        indices.push_back(2 + i + 3 * segmentCount);  // unique top current
        indices.push_back(2 + next + 3 * segmentCount); // unique top next
    }

    VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
    std::vector<float> normals = CalculateNormals(vertices, indices);
    VBO vbo2(normals.data(), sizeof(float) * normals.size());
    EBO ebo(indices.data(), sizeof(int) * indices.size());
    VAO cylinderVAO;
    cylinderVAO.Link(vbo1, vbo2, ebo);

    indexCount = indices.size();
    return cylinderVAO;
}
