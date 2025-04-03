#include "Lightsource.h"
#include"VertexData.h"

Lightsource::Lightsource() : Object3D() {

	indexCount = VertexData::GetCubeIndexCount();
	objectType = lightsource;
	isLit = false;
	color = glm::vec3(1.0f, 0.65f, 0.0f); //bright orange
}

VAO Lightsource::GetVAO() {
	return VertexData::GetCubeVAO(); //temporary as cube 
}

void Lightsource::Scale(glm::vec3 v) { ; }

void Lightsource::Scale(float* v) { ; } //dont scale light icon 
	
