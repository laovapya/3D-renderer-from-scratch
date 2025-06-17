#include "ObjectManager.h"
#include<iostream>

ObjectManager::ObjectManager() {
	

	int id = AddLightsource();
	createdObjects[0]->Translate({ 6,4,-8 });

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
	
}
void ObjectManager::RemoveObject(int id) {
	auto it1 = createdObjects.begin();
	for (const auto &object : createdObjects) {
		
		if (object->GetID() == id) {
			DeleteObject(object.get());
			createdObjects.erase(it1);

			return;
		}
		it1++;
	}
}

void ObjectManager::RemoveSelectedObjects() {
	
	auto it = createdObjects.begin();
	while (it != createdObjects.end()) {
		if ((*it)->GetIfSelected()) {
			DeleteObject((*it).get());
			it = createdObjects.erase(it); 
		}
		else 
			++it;
	}
}

int ObjectManager::AddObject(std::unique_ptr<Object3D> obj) {
	for (const auto& object : createdObjects)
		object->SetSelected(false);
	createdObjects.push_back(std::move(obj));
	createdObjects.back()->SetSelected(true);
	return createdObjects.back()->GetID();
}


int ObjectManager::AddCube() {
	auto cube = std::make_unique<Cube>();
	cube->name = "cube" + std::to_string(++cubeCount);
	return AddObject(std::move(cube));
}

int ObjectManager::AddCone() {
	auto cone = std::make_unique<Cone>(segmentCount);
	cone->name = "cone" + std::to_string(++coneCount);
	return AddObject(std::move(cone));
}

int ObjectManager::AddCylinder() {
	auto cyl = std::make_unique<Cylinder>(segmentCount);
	cyl->name = "cylinder" + std::to_string(++cylinderCount);
	return AddObject(std::move(cyl));
}

int ObjectManager::AddSphere() {
	auto sphere = std::make_unique<Sphere>(segmentCount);
	sphere->name = "sphere" + std::to_string(++sphereCount);
	return AddObject(std::move(sphere));
}

int ObjectManager::AddLightsource() {
	auto light = std::make_unique<Lightsource>();
	light->name = "lightsource" + std::to_string(++lightsourceCount);
	return AddObject(std::move(light));
}





const std::vector<glm::vec3> ObjectManager::GetLightsourcePositions() const{
	std::vector<glm::vec3> positions;
	for (const auto& object : createdObjects) {
		if (object->GetType() == Object3D::type::lightsource) {
			positions.push_back(object->GetPosition());
		}
	}
	return positions;
}
const std::vector<glm::vec3> ObjectManager::GetLightsourceColors() const{
	std::vector<glm::vec3> colors;
	for (const auto& object : createdObjects) {
		if (object->GetType() == Object3D::type::lightsource) {
			colors.push_back(object->GetColor());
		}
	}
	return colors;
}

void ObjectManager::SetSegmentCount(int count) {
	segmentCount = count;
}

const std::vector<std::unique_ptr<Object3D>>& ObjectManager::GetCreatedObjects() {
	return createdObjects;
}