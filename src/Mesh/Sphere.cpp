#include "Sphere.h"
#include"VertexData.h"

Sphere::Sphere() : Object3D() {
	indexCount = VertexData::GetSphereIndexCount();
	objectType = sphere;
	isLit = true;
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