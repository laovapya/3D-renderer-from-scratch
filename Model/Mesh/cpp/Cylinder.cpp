#include "Cylinder.h"
Cylinder::Cylinder() : Shape() {

	indexCount = VertexData::GetCylinderIndexCount();
	shape = cylinder;
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