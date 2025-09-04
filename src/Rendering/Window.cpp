#include "Window.h"

Window::Window()
{

	InitDimensions();

	InitGLFW();

	CreateWindow();

	InitGlad();

	SetWindowParameters();

	InitFBO(width, height);

	InitShaders();

	RegisterEvents();

	InitImGui();
}

Window::~Window()
{
	litShader.Delete();
	glfwTerminate();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Window::InitDimensions()
{
	width = 2000;
	height = 1200;

	aspectRatio = width * sceneXpercent / (height * sceneYpercent);
}

void Window::InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void Window::CreateWindow()
{
	window = glfwCreateWindow(width, height, "3D_Renderer", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window,
							 this); //use the pointer to switch from static glfw to instances
	glfwMakeContextCurrent(window);
}
void Window::InitGlad()
{
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Window::SetWindowParameters()
{
	glViewport(0, 0, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enable alpha values;

	glEnable(GL_DEPTH_TEST); //to prevent rendering back vertices
	glPolygonMode(GL_FILL, GL_FILL);
	glClearColor(color.x, color.y, color.z, 1);

	//Matrix4 projection = Matrix4::Perspective(0.785f, Window::GetAspectRatio(), 0.1f, 1000.0f);
}

void Window::InitFBO(int width, int height)
{
	glGenFramebuffers(1, &fbo);
	ResizeFBO(width, height);
}

void Window::ResizeFBO(int width, int height)
{
	if(colorTexture)
	{
		glDeleteTextures(1, &colorTexture);
		colorTexture = 0;
	}
	if(rbo)
	{
		glDeleteRenderbuffers(1, &rbo);
		rbo = 0;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer is not complete" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Window::RegisterEvents()
{

	glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback); //
	glfwSetKeyCallback(window, Controller::SwitchState); //keyboard
	glfwSetCursorPosCallback(window, Controller::MouseCallback); //mouse
}

void Window::InitShaders()
{
	Matrix4 projection = Matrix4::Perspective(0.785f, Window::GetAspectRatio(), 0.1f, 1000.0f);

	//SHADER_DIR is defined in CMakeLists.txt
	litShader = Shader(SHADER_DIR "lit.vert", SHADER_DIR "lit.frag");
	litShader.Activate();
	litShader.SetProjectionMatrix(projection);
	litShader.SetViewMatrix(Matrix4());
	litShader.SetLocalMatrix(Matrix4());

	litShader.SetAlpha(1.0f);
	litShader.SetRenderColor(Vector3(1.0f, 0.4f, 0.8f)); //pink init

	defaultShader = Shader(SHADER_DIR "default.vert", SHADER_DIR "default.frag");
	defaultShader.Activate();
	defaultShader.SetProjectionMatrix(projection);
	defaultShader.SetViewMatrix(Matrix4());
	defaultShader.SetLocalMatrix(Matrix4());
	defaultShader.SetAlpha(1.0f);
	defaultShader.SetRenderColor(Vector3(1.0f, 0.4f, 0.8f)); //pink init
}

void Window::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//imgui stuff
	ImVec4 color = ImVec4(0.25f, 0.25f, 0.25f, 1); //darker grey
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = color;
	style.Colors[ImGuiCol_MenuBarBg] = color;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Window::framebuffer_size_callback(int width, int height) //by instance
{
	ResizeFBO(width, height);
	aspectRatio = width * sceneXpercent / (height * sceneYpercent);
	glViewport(0, 0, width, height);
	Matrix4 projection = Matrix4::Perspective(0.785f, Window::GetAspectRatio(), 0.1f, 1000.0f);

	litShader.Activate();
	litShader.SetProjectionMatrix(projection);
	defaultShader.Activate();
	defaultShader.SetProjectionMatrix(projection);
}

void Window::framebuffer_size_callback(GLFWwindow* win, int width, int height) //static
{
	Window* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
	if(self != nullptr)
		self->framebuffer_size_callback(width, height);
}

void Window::EarlyUpdate() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	SetUpDocking();
}
void Window::LateUpdate() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //before swapping buffers
	if(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(window);
	Controller::ResetMouse(); //before polling events
	glfwPollEvents();
}

GLFWwindow* Window::GetWindow() const
{
	return window;
}
const Shader* Window::GetDefaultShader() const
{
	return &defaultShader;
}
const Shader* Window::GetLitShader() const
{
	return &litShader;
}
bool Window::GetShouldClose() const
{
	return glfwWindowShouldClose(window);
	;
}

float Window::GetWidth() const
{
	return width;
}
float Window::GetHeight() const
{
	return height;
}
float Window::GetAspectRatio() const
{
	return aspectRatio;
}

void Window::SetUpDocking() const
{
	static bool hasSetupDocking = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode |
												ImGuiDockNodeFlags_NoResize |
												ImGuiDockNodeFlags_NoUndocking;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
					ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if(dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	bool a = true;
	ImGui::Begin("DockSpace Demo", &a, window_flags);

	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGuiIO& io = ImGui::GetIO();

	if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		if(!hasSetupDocking)
		{
			hasSetupDocking = true;

			ImGui::DockBuilderRemoveNode(dockspace_id); // clear previous
			ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags);
			ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

			// split main dockspace into left (70%) and right (30%)
			ImGuiID dock_left, dock_right;
			ImGui::DockBuilderSplitNode(
				dockspace_id, ImGuiDir_Right, 1 - sceneXpercent, &dock_right, &dock_left);

			// split left vertically into top (scene) and bottom (component menu)
			ImGuiID dock_left_top, dock_left_bottom;
			ImGui::DockBuilderSplitNode(
				dock_left, ImGuiDir_Down, 1 - sceneYpercent, &dock_left_bottom, &dock_left_top);

			// split right vertically into three parts
			ImGuiID dock_right_top, dock_right_middle, dock_right_bottom;
			ImGui::DockBuilderSplitNode(
				dock_right, ImGuiDir_Down, 1.0f / 5, &dock_right_top, &dock_right_middle);
			ImGui::DockBuilderSplitNode(
				dock_right_middle, ImGuiDir_Down, 0.4f, &dock_right_middle, &dock_right_bottom);

			// dock windows
			ImGui::DockBuilderDockWindow("Scene", dock_left_top);
			ImGui::DockBuilderDockWindow("Component menu", dock_left_bottom);

			ImGui::DockBuilderDockWindow("Object list", dock_right_top);
			ImGui::DockBuilderDockWindow("Transform menu", dock_right_middle);
			ImGui::DockBuilderDockWindow("Coloring", dock_right_bottom);

			ImGui::DockBuilderFinish(dockspace_id);
		}
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

GLuint Window::GetColorTexture() const
{
	return colorTexture;
}
