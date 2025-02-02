#include "Sphere.h"
#include"VertexData.h"

Sphere::Sphere() : Shape() {
	indexCount = VertexData::GetSphereIndexCount();
	shape = sphere;
}
VAO Sphere::GetVAO() {

	return VertexData::GetSphereVAO();
}
//void Sphere::Bind() {
//	VertexData::GetSphereVAO().Bind();
//}

//int Sphere::GetVertexCount() {
//	return vertexCount;
//}