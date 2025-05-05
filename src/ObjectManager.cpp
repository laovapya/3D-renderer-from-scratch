#include "ObjectManager.h"
#include<iostream>

ObjectManager::ObjectManager() {
	
}
ObjectManager::~ObjectManager() {
	for (Object3D* n : createdObjects) {
		delete(n);
	}
}

void ObjectManager::RemoveObject(int id) {
	auto it1 = createdObjects.begin();
	for (Object3D* object : createdObjects) {
		
		if (object->GetID() == id) {
			//delete object here if nesessary
			delete(*it1);
			createdObjects.erase(it1);
			//storedObjects.erase(it2);
			objectCount--;
			return;
		}
		it1++;
	}
	//throw error couldnt find object to erase
}
void ObjectManager::SelectObject(int id) {
	for (Object3D* object : createdObjects) {
		if (object->GetID() == id) {
			//selectedObjects.push_back(object);
			object->isSelected = true;
			

			return;
		}
	}
	//throw error couldnt find object to push back
}

void ObjectManager::DeselectObject(int id) {
	//auto it = selectedObjects.begin();
	for (Object3D* object : createdObjects) {
		//it++;
		if (object->GetID() == id) {
			//selectedObjects.erase(it);
			object->isSelected = false;
			return;
		}
	}
	//throw error couldnt find object to erase
}

std::vector<Object3D*> ObjectManager::GetCreatedObjects() {
	return createdObjects;
}




void ObjectManager::AddObject(Object3D* object) {
	createdObjects.push_back(object);
	objectCount++;
}


int ObjectManager::AddCube() {
	if (objectCount >= COUNT) {
		//throw error
		std::cout << "object max count reached " << std::endl;
		return 0;
	}
	Cube* cube = new Cube();
	AddObject(cube);
	return cube->GetID();
}


int ObjectManager::AddCone() {
	if (objectCount >= COUNT) {
		//throw error
		std::cout << "object max count reached " << std::endl;
		return 0;
	}
	Cone* cone = new Cone();
	AddObject(cone);
	return cone->GetID();
}


int ObjectManager::AddCylinder() {
	if (objectCount >= COUNT) {
		//throw error
		std::cout << "object max count reached " << std::endl;
		return 0;
	}
	Cylinder* cyl = new Cylinder();
	AddObject(cyl);
	return cyl->GetID();
}

int ObjectManager::AddSphere() {
	if (objectCount >= COUNT) {
		//throw error
		std::cout << "object max count reached " << std::endl;
		return 0;
	}
	Sphere* sphere = new Sphere();
	AddObject(sphere);
	return sphere->GetID();
}

int ObjectManager::AddLightsource() {
	if (objectCount >= COUNT) {
		//throw error
		std::cout << "object max count reached " << std::endl;
		return 0;
	}
	Lightsource* light = new Lightsource();
	AddObject(light);
	return light->GetID();
}

int ObjectManager::AddCamera() {
	std::cout << "camera is not yet object 3D " << std::endl;
	return 0;
}

//
//
//void ObjectManager::AddSphere() {
//	Sphere sphere;
//	storedObjects.push_back(sphere);
//	AddObject(&storedObjects.back());
//}