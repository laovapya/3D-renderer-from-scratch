#pragma once
#include "Scene.h"
#include "iostream"

#define NFD_CHAR char
#include "nfd.h"
//#include "nfd_gtk_extended.h"

class UI
{

private:
	const Window* window;
	ObjectManager* objectManager;

	int segmentsBuffer[1] = {12};
	float positionBuffer[3] = {0, 0, 0};
	float rotationBuffer[3] = {0, 0, 0};
	float scaleBuffer[3] = {0, 0, 0};
	float colorBuffer[4] = {0, 0, 0, 0};

	int maxObjectCount = 256;
	int objectListMenuHeight = maxObjectCount / 4;

	unsigned int textureIDbuffer = 0;
	std::string GetTextureFilePath();

public:
	UI(const Window* window, ObjectManager* objectManager);

	void DrawScene();
	void DrawComponentMenu();

	void DrawObjectList();

	void DrawTransformMenu();

	void DrawColoringMenu();

	int GetSegmentCount() const;
};
