#include "Cone.h"
#include"VertexData.h"
Cone::Cone() : Shape() {
	
	indexCount = VertexData::GetConeIndexCount();
	shape = cone;
}


VAO Cone::GetVAO() {
	return VertexData::GetConeVAO();
}

