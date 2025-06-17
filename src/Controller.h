#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include"Camera.h"

class Controller
{
private:

	float mouseSpeed = 30;
	float zoomSpeed = 1;



	float mouseLastX = 400;
	float mouseLastY = 300;
	float mouseXoffset;
	float mouseYoffset; 


	const float mouseSensitivity = 0.1f;

	float panSpeed = 10;



	Controller();
public:

	Controller(const Controller&) = delete;
	static Controller& GetInstance() {
		static Controller instance;
		return instance;
	}


	static bool GetScaling();
	static bool GetRotating();
	static bool GetTranslating();

	static glm::vec3 GetTransformVector(const Camera* currentCamera);



	static void MoveCamera(GLFWwindow* window, Camera* currentCamera);


	static void SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

	bool isScaling = false;
	bool isRotating = false;
	bool isTranslating = false;

	bool isXaxisEnabled = false;
	bool isYaxisEnabled = false;
	bool isZaxisEnabled = false;

	static void ResetMouse();
};

