#pragma once
#include"Scene.h"

#include"iostream"

#define maxObjectCount 32




//This class manages the UI elements. It is linked to the scene and calls its methods when user input modifies it.

class UI
{
//The object list menu is created using a list of items of this struct. 
//id links the object in the scene to object in the list
private:
	struct ListedObject {

	public:
		bool isSelected;
		int id;
		std::string name;
		Shape::Shapes shape;
		ListedObject() {
			isSelected = false;
			id = -1;
			name = "null";
			shape = Shape::Shapes::cube;
		}
		ListedObject(bool isSelected, int ID, std::string name, Shape::Shapes shape) {
			this->isSelected = isSelected;
			this->id = ID;
			this->name = name;
			this->shape = shape;
		}
	};


	Scene* scene;

	//The object list menu container
	ListedObject items[maxObjectCount];


	int currentCount = 0;

	//current count of shapes (used to create names in the object menu list)
	int cubeCount = 0;
	int coneCount = 0;
	int cylinderCount = 0;
	int sphereCount = 0;

	//These buffers store values from the sliders of transform menu 
	float positionBuffer[3] = { 0, 0, 0 };
	float rotationBuffer[3] = { 0, 0, 0 };
	float scaleBuffer[3] = { 0, 0, 0 };

	
	int objectListMenuHeight = maxObjectCount;

	//methods managing the object list menu container
	void AddItem(ListedObject& item);
	void ReInitItems();
	void DeleteItems();
public:
	UI(Scene* scene);

	//methods to draw the UI windows
	void DrawObjectMenu();
	
	void DrawObjectList();

	void DrawTransformMenu();

};





