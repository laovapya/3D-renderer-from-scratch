#include "Cone.h"
#include"VertexData.h"
Cone::Cone(int segmentCount) : Object3D() {
	
	objectType = cone;
	isLit = true;
    SetVAO(segmentCount);
}

VAO Cone::GenerateVAO(int& indexCount, int segmentCount) const {
    const float PI = 3.14159265359f;
    std::vector<float> vertices;
    std::vector<int> indices;

    // add top and bottom center points
    vertices.insert(vertices.end(), { 0, 0.5f, 0 });  // top vertex
    vertices.insert(vertices.end(), { 0, -0.5f, 0 }); // bottom center

    // add side vertices for bottom, up face normals
    for (int i = 0; i < segmentCount; ++i) {
        float angle = i * 2 * PI / segmentCount;  // radians
        float x = 0.5f * cos(angle);
        float y = -0.5f;
        float z = 0.5f * sin(angle);
        vertices.insert(vertices.end(), { x, y, z });
    }

    // add side vertices again, for side normals
    for (int i = 0; i < segmentCount; ++i) {
        float angle = i * 2 * PI / segmentCount;  // radians
        float x = 0.5f * cos(angle);
        float y = -0.5f;
        float z = 0.5f * sin(angle);
        vertices.insert(vertices.end(), { x, y, z });
    }

    // indices for top triangles
    for (int i = 2; i < 2 + segmentCount; ++i)
        indices.insert(indices.end(), { 0, i, (i + 1 == 2 + segmentCount) ? 2 : i + 1 });

    // indices for bottom triangles
    for (int i = 2 + segmentCount; i < 2 + 2 * segmentCount; ++i)
        indices.insert(indices.end(), { (i + 1 == 2 + 2 * segmentCount) ? 2 + segmentCount : i + 1, i, 1 });

    VBO vbo1(vertices.data(), sizeof(float) * vertices.size());
    std::vector<float> normals = CalculateNormals(vertices, indices);
    VBO vbo2(normals.data(), sizeof(float) * normals.size());
    EBO ebo(indices.data(), sizeof(int) * indices.size());
    VAO coneVAO;
    coneVAO.Link(vbo1, vbo2, ebo);

    indexCount = indices.size();
    return coneVAO;
}