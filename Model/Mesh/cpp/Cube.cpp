#include "Cube.h"
#include"VertexData.h"

Cube::Cube() : Shape() {
	
	indexCount = VertexData::GetCubeIndexCount();
	shape = cube;
}

//void Cube::Bind() {
//	VertexData::GetCubeVAO().Bind();
//}

//int Cube::GetVertexCount() {
//	return vertexCount;
//}

VAO Cube::GetVAO() {
	return VertexData::GetCubeVAO();
}