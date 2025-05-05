#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include"Camera.h"
//Manages inputs related to modifying the scene without using UI. It is a singleton.
class Controller
{
private:
	//this value controls object transformation and panning speed.
	float mouseSpeed = 30;
	float zoomSpeed = 3;


	//values to get mouse delta.
	float mouseLastX = 400;
	float mouseLastY = 300;
	float mouseXoffset;
	float mouseYoffset; 

	//mouse sensitivity
	const float mouseSensitivity = 0.1f;

	float panSpeed = 10;

	//glm::vec4 activeColor;

	Controller();
public:
	//singleton init
	Controller(const Controller&) = delete;
	static Controller& GetInstance() {
		static Controller instance;
		return instance;
	}

	//get whether object transformation is enabled
	static bool GetScaling();
	static bool GetRotating();
	static bool GetTranslating();
	//static glm::vec4 GetActiveColor();
	//static void SetActiveColor(glm::vec4 color);
	
	//vector determining the transformation amount and its axises. Depends on mouse movement.
	static glm::vec3 GetTransformVector(Camera* currentCamera);


	
	//pan and orbit camera
	static void MoveCamera(GLFWwindow* window, Camera* currentCamera);

	//listens to keyboard inputs
	static void SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods);

	//fires on mouse movement, sets the mouse delta values
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	//whether transformations are enabled
	bool isScaling = false;
	bool isRotating = false;
	bool isTranslating = false;

	//whether axis is enabled 
	bool isXaxisEnabled = false;
	bool isYaxisEnabled = false;
	bool isZaxisEnabled = false;


	//the mouse values gained from glfw events are not updated when mouse is not moving. So we have to reset them.
	static void ResetMouse();
};

