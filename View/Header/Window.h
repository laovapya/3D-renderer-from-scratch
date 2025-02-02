#pragma once
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h" //before glad

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include"Shader.h"
#include"Controller.h"


//defining application name
#define appName "Project"

//This class intializes the window and fires all related events.
class Window 
{
private:
	//Window's width, height and aspect ratio.
	static float width;
	static float height;
	static float aspectRatio;

	//values determining the position of viewport and UI elements
	static glm::vec2 lowerLeft;
	static glm::vec2 upperRight;
	static float yDownOffset;
	static float XRightOffset;

	//window background color
	glm::vec4 color = glm::vec4(0.4f, 0.4f, 0.4f, 1); //grey 
	
	
	//shaderProgram we use (check Shader class)
	static Shader shaderProgram; 

	GLFWwindow* window;
	 
	//Close the application when this value is true
	bool shouldClose = 0;

	//Init window and libraries
	void InitGLFW();
	void CreateWindow();
	void InitGlad();

	//here we set the viewport, enable wireframe mode, enable depth testing so backfaces arent rendered, among other things.
	void SetWindowParameters();

	//register keyboard press and window size change events
	void RegisterEvents();

	//enable shaders
	void UseShaders();

	//init ImGui
	void InitImGui();
public:
	Window();

	//terminate all processes
	~Window();


	//Called first in the main loop
	void EarlyUpdate();
	
	//Called last in the main loop
	void LateUpdate();

	

	GLFWwindow* GetWindow();
	static Shader GetShaderProgram();
	bool GetShouldClose();

	
	float GetWidth();
	float GetHeight();
	static float GetAspectRatio();

	//This function is called every time window's size is changed.
	//It resets the aspect ratio and the projection matrix (which requires it)
	//Also it reset the viewport, which is the area where the Scene is rendered.
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	//ImGui's functionality to dock the sub windows of UI. 
	void SetUpDocking();

	//Getting sub windows dimensions
	ImVec2 GetWidget1Dimensions();
	ImVec2 GetWidget2Dimensions();
	ImVec2 GetWidget3Dimensions();
};


