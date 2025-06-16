#pragma once
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h" //before glad

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include"Shader.h"
#include"Controller.h"


//defining application name
#define appName "3D_Renderer"

//This class intializes the window and fires all related events.
class Window 
{
private:
	//Window's width, height 
	float width;
	float height;

	//aspect ratio of the scene subwindow
	float aspectRatio;

	float sceneXpercent = 0.7f;
	float sceneYpercent = 0.8f;


	//window background color
	glm::vec4 color = glm::vec4(0.4f, 0.4f, 0.4f, 1); //grey 
	


	Shader litShader; 
	Shader defaultShader;

	GLFWwindow* window;

	mutable bool hasSetupDocking = false;


	GLuint fbo;
	GLuint rbo;
	GLuint colorTexture;

	void InitDimensions();

	//Init window and libraries
	void InitGLFW();
	void CreateWindow();
	void InitGlad();

	//set the viewport, enable wireframe mode, enable depth testing so backfaces arent rendered, among other things.
	void SetWindowParameters();

	//register keyboard press and window size change events
	void RegisterEvents();


	void InitShaders();

	void InitImGui();



	
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
public:
	Window();

	//terminate all processes
	~Window();


	//Called first in the main loop
	void EarlyUpdate() const;
	void ImGuiEarlyUpdate() const;
	//Called last in the main loop
	void LateUpdate() const;

	void InitFBO(int width, int height);
	void ResizeFBO(int width, int height);

	GLFWwindow* GetWindow() const;
	const Shader* GetDefaultShader() const;
	const Shader* GetLitShader() const;
	bool GetShouldClose() const;

	
	float GetWidth() const;
	float GetHeight() const;
	float GetAspectRatio() const;


	//This function is called every time window's size is changed.
	//It resets the aspect ratio and the projection matrix (which requires it)
	//Also it reset the viewport, which is the area where the Scene is rendered.
	void framebuffer_size_callback(int width, int height);

	//ImGui's functionality to dock the sub windows of UI. 
	void SetUpDocking() const;



	GLuint GetColorTexture() const;
};


