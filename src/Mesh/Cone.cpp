#include "Cone.h"
#include"VertexData.h"
Cone::Cone() : Object3D() {
	
	indexCount = VertexData::GetConeIndexCount();
	objectType = cone;
	isLit = true;
}


VAO Cone::GetVAO() const {
	return VertexData::GetConeVAO();
}