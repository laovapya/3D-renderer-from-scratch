#pragma once
#include <glad/glad.h> //1
#include <GLFW/glfw3.h> //2

#include "imgui.h" //3
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Controller.h"
#include "Shader.h"

#include "Utility/Vector3.h"

class Window
{
private:
	float width;
	float height;

	float sceneAspectRatio;

	float sceneXpercent = 0.7f;
	float sceneYpercent = 0.8f;

	Vector3 backgroundColor = Vector3(0.4f, 0.4f, 0.4f); //grey

	Shader litShader;
	Shader defaultShader;

	GLFWwindow* window;

	GLuint fbo;
	GLuint rbo;
	GLuint sceneTexture;

	void InitDimensions();

	void InitGLFW();
	void CreateWindow();
	void InitGlad();

	void SetWindowParameters();

	//register keyboard press and window size change events
	void RegisterEvents();

	void InitShaders();

	void InitImGui();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	Window();

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

	GLuint GetSceneTexture() const;
};
