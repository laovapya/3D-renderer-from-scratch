#include "Controller.h"
#include "DeltaTime.h"

Controller::Controller() { }

void Controller::SwitchState(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Controller& instance = Controller::GetInstance();

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if(key == GLFW_KEY_X && action == GLFW_PRESS)
		instance.isXaxisEnabled = !instance.isXaxisEnabled;
	if(key == GLFW_KEY_Y && action == GLFW_PRESS)
		instance.isYaxisEnabled = !instance.isYaxisEnabled;
	if(key == GLFW_KEY_Z && action == GLFW_PRESS)
		instance.isZaxisEnabled = !instance.isZaxisEnabled;

	if(key == GLFW_KEY_S && action == GLFW_PRESS)
		instance.isScaling = !instance.isScaling;
	if(key == GLFW_KEY_R && action == GLFW_PRESS)
		instance.isRotating = !instance.isRotating;
	if(key == GLFW_KEY_G && action == GLFW_PRESS)
		instance.isTranslating = !instance.isTranslating;

	if(key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		instance.isXaxisEnabled = false;
		instance.isYaxisEnabled = false;
		instance.isZaxisEnabled = false;

		instance.isTranslating = false;
		instance.isScaling = false;
		instance.isRotating = false;
	}
}

void Controller::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Controller& instance = Controller::GetInstance();
	instance.mouseXoffset = xpos - instance.mouseLastX;
	instance.mouseYoffset = instance.mouseLastY - ypos;
	instance.mouseLastX = xpos;
	instance.mouseLastY = ypos;

	instance.mouseXoffset *= instance.mouseSensitivity;
	instance.mouseYoffset *= instance.mouseSensitivity;
}

bool Controller::GetScaling()
{
	return GetInstance().isScaling;
}
bool Controller::GetRotating()
{
	return GetInstance().isRotating;
}
bool Controller::GetTranslating()
{
	return GetInstance().isTranslating;
}

Vector3 Controller::GetTransformVector(const Camera* currentCamera)
{
	Vector3 v(0, 0, 0);
	Controller& instance = Controller::GetInstance();

	Vector3 mouseVector = currentCamera->GetRight() * instance.mouseXoffset +
						  currentCamera->GetUp() * instance.mouseYoffset;

	if(instance.isXaxisEnabled)
		v += mouseVector.x * Vector3(1, 0, 0);
	if(instance.isYaxisEnabled)
		v += mouseVector.y * Vector3(0, 1, 0);
	if(instance.isZaxisEnabled)
		v += mouseVector.z * Vector3(0, 0, 1);

	return v * (-1.0f * instance.mouseSpeed);
}

void Controller::MoveCamera(GLFWwindow* window, Camera* currentCamera)
{
	Controller& instance = Controller::GetInstance();
	float dt = DeltaTime::GetDeltaTime();

	if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		currentCamera->Pan(Vector3(instance.mouseXoffset, instance.mouseYoffset, 0) * dt);

	if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		currentCamera->Pan(Vector3(0, 0, 1) * instance.zoomSpeed * dt);

	if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		currentCamera->Pan(Vector3(0, 0, -1) * instance.zoomSpeed * dt);

	if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		currentCamera->Orbit(-Vector3(-instance.mouseYoffset, instance.mouseXoffset, 0) * dt);
}

void Controller::ResetMouse()
{
	Controller& instance = GetInstance();
	instance.mouseXoffset = 0;
	instance.mouseYoffset = 0;
}

float Controller::GetRotationSpeed()
{
	return GetInstance().rotationSpeed;
}
