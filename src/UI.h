#pragma once
#include"Scene.h"

#include"iostream"





//This class manages the UI elements. It is linked to the scene and calls its methods when user input modifies it.

class UI
{
//The object list menu is created using a list of items of this struct. 
//id links the object in the scene to object in the list
private:
	const Window* window;
	ObjectManager* objectManager;

	

	//These buffers store values from the sliders of transform menu 
	int segmentsBuffer[1] = { 12 };
	float positionBuffer[3] = { 0, 0, 0 };
	float rotationBuffer[3] = { 0, 0, 0 };
	float scaleBuffer[3] = { 0, 0, 0 };
	float colorBuffer[4] = { 0, 0, 0, 0 };
	
	int maxObjectCount = 256;
	int objectListMenuHeight = maxObjectCount / 4;

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





