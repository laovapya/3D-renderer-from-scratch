#include "ObjectManager.h"
#include<iostream>

ObjectManager::ObjectManager() {
	

	int id = AddLightsource();
	createdObjects[0]->Translate({ 6,4,-8 });

}
ObjectManager::~ObjectManager() {
	for (Object3D* n : createdObjects) {
		delete(n);
	}
}

void ObjectManager::DeleteObject(Object3D* object) {
	
	objectCount--;

	switch (object->GetType()) {
	case Object3D::type::cube:
		cubeCount--; break;
	case Object3D::type::cone:
		coneCount--; break;
	case Object3D::type::cylinder:
		cylinderCount--; break;
	case Object3D::type::sphere:
		sphereCount--; break;
	case Object3D::type::lightsource:
		lightsourceCount--; break;
	case Object3D::type::camera:
		cameraCount--; break;
	default:
		break;
	}
	delete(object);
}
void ObjectManager::RemoveObject(int id) {
	auto it1 = createdObjects.begin();
	for (Object3D* object : createdObjects) {
		
		if (object->GetID() == id) {
			DeleteObject(object);
			createdObjects.erase(it1);

			return;
		}
		it1++;
	}
	//throw error couldnt find object to erase
}

void ObjectManager::RemoveSelectedObjects() {
	
	auto it = createdObjects.begin();
	while (it != createdObjects.end()) {
		if ((*it)->GetIfSelected()) {
			DeleteObject(*it);
			it = createdObjects.erase(it); //next valid iterator
		}
		else 
			++it;
		
	}
}


std::vector<Object3D*> ObjectManager::GetCreatedObjects() {
	return createdObjects;
}




void ObjectManager::AddObject(Object3D* object) {
	if (objectCount++ >= COUNT) {

		std::cout << "object max count reached " << std::endl;
		delete(object);
		return;
	}
	for (Object3D* object : createdObjects) 
		object->SetSelected(false);
	
	createdObjects.push_back(object);
	object->SetSelected(true);
	
}


int ObjectManager::AddCube() {

	Cube* cube = new Cube();
	cube->name = "cube" + std::to_string(cubeCount++);
	AddObject(cube);
	return cube->GetID();
}


int ObjectManager::AddCone() {

	Cone* cone = new Cone(segmentCount);
	cone->name = "cone" + std::to_string(coneCount++);
	AddObject(cone);
	return cone->GetID();
}


int ObjectManager::AddCylinder() {
	

	Cylinder* cyl = new Cylinder(segmentCount);
	cyl->name = "cylinder" + std::to_string(cylinderCount++);
	AddObject(cyl);
	return cyl->GetID();
}

int ObjectManager::AddSphere() {

	Sphere* sphere = new Sphere(segmentCount);
	sphere->name = "sphere" + std::to_string(sphereCount++);
	AddObject(sphere);
	return sphere->GetID();
}

int ObjectManager::AddLightsource() {

	Lightsource* light = new Lightsource();
	light->name = "lightsource" + std::to_string(lightsourceCount++);
	AddObject(light);
	return light->GetID();
}

int ObjectManager::AddCamera() {
	std::cout << "camera is not yet object 3D " << std::endl;
	return 0;
}



const std::vector<glm::vec3> ObjectManager::GetLightsourcePositions() const{
	std::vector<glm::vec3> positions;
	for (Object3D* object : createdObjects) {
		if (object->GetType() == Object3D::type::lightsource) {
			positions.push_back(object->GetPosition());
		}
	}
	return positions;
}
const std::vector<glm::vec3> ObjectManager::GetLightsourceColors() const{
	std::vector<glm::vec3> colors;
	for (Object3D* object : createdObjects) {
		if (object->GetType() == Object3D::type::lightsource) {
			colors.push_back(object->GetColor());
		}
	}
	return colors;
}

void ObjectManager::SetSegmentCount(int count) {
	segmentCount = count;
}