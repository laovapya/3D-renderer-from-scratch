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
	/*struct ListedObject {

	public:
		bool isSelected;
		int id;
		std::string name;
		Object3D::type shape;
		ListedObject() {
			isSelected = false;
			id = -1;
			name = "null";
			shape = Object3D::type::cube;
		}
		ListedObject(bool isSelected, int ID, std::string name, Object3D::type shape) {
			this->isSelected = isSelected;
			this->id = ID;
			this->name = name;
			this->shape = shape;
		}
	};*/


	const Window* window;
	ObjectManager* objectManager;



	//The object list menu container
	//ListedObject items[maxObjectCount];


	

	//These buffers store values from the sliders of transform menu 
	int segmentsBuffer[1] = { 12 };
	float positionBuffer[3] = { 0, 0, 0 };
	float rotationBuffer[3] = { 0, 0, 0 };
	float scaleBuffer[3] = { 0, 0, 0 };
	float colorBuffer[4] = { 0, 0, 0, 0 };
	
	int objectListMenuHeight = maxObjectCount / 4;


	//void AddItem(ListedObject& item);
	//void ReInitItems();
	//void DeleteItems();
public:
	UI(const Window* window, ObjectManager* objectManager);

	//methods to draw the UI windows
	void DrawScene();
	void DrawComponentMenu();
	
	void DrawObjectList();

	void DrawTransformMenu();

	void DrawColoringMenu();

	int GetSegmentCount() const;
};





