#include "Cube.h"
#include"VertexData.h"

Cube::Cube() : Object3D() {
	
	indexCount = VertexData::GetCubeIndexCount();
	objectType = cube;
	isLit = true;
}


VAO Cube::GetVAO() const {
	return VertexData::GetCubeVAO();
}