#include "Cylinder.h"
#include "VertexData.h"
Cylinder::Cylinder() : Object3D() {

	indexCount = VertexData::GetCylinderIndexCount();
	objectType = cylinder;
	isLit = true;
}

VAO Cylinder::GetVAO() const{
	return VertexData::GetCylinderVAO();
}