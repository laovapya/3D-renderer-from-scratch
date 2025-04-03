#include "Cylinder.h"
Cylinder::Cylinder() : Object3D() {

	indexCount = VertexData::GetCylinderIndexCount();
	objectType = cylinder;
	isLit = true;
}
//int Cylinder::GetVertexCount() {
//	return vertexCount;
//}

//void Cylinder::Bind() {
//	VertexData::GetCylinderVAO().Bind();
//}
VAO Cylinder::GetVAO() {
	return VertexData::GetCylinderVAO();
}