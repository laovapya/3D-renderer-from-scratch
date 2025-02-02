#include "Window.h"

#include"Camera.h"
Window::Window() {
	//window = nullptr;

	//window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	InitGLFW();
	CreateWindow();
	InitGlad();
	SetWindowParameters();
	UseShaders();

	RegisterEvents();

	InitImGui();

}
Window::~Window() {
	shaderProgram.Delete();
	glfwTerminate();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}




void Window::InitGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void Window::CreateWindow() {
	window = glfwCreateWindow(width, height, appName, NULL, NULL);
	if (window == NULL)
	{
		//std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	//return bool?
	
}
void Window::InitGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Window::SetWindowParameters() {
	glViewport(lowerLeft.x, lowerLeft.y, upperRight.x, upperRight.y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //enable alpha values;

	glEnable(GL_DEPTH_TEST); //to prevent rendering back vertices
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

	glClearColor(color.x, color.y, color.z, color.w);
}
void Window::RegisterEvents() {
	glfwSetFramebufferSizeCallback(window, Window::framebuffer_size_callback);
	glfwSetKeyCallback(window, Controller::SwitchState); //keyboard
	glfwSetCursorPosCallback(window, Controller::MouseCallback); //mouse 
}

void Window::UseShaders() {
    shaderProgram = Shader("default.vert", "default.frag");
    shaderProgram.Activate();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), Window::GetAspectRatio(), 0.1f, 100.0f);
    shaderProgram.SetProjectionMatrix(projection);
    shaderProgram.SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Window::InitImGui() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	

	io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	
	//imgui stuff
	ImVec4 color = ImVec4(0.25f, 0.25f, 0.25f, 1); //darker grey
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = color;
	style.Colors[ImGuiCol_MenuBarBg] = color;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	upperRight = glm::vec2(width - XRightOffset, height);
	aspectRatio = ((upperRight.x - lowerLeft.x)) / ((upperRight.y));
	glViewport(lowerLeft.x, lowerLeft.y, upperRight.x, upperRight.y);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), Window::GetAspectRatio(), 0.1f, 100.0f);
	shaderProgram.SetProjectionMatrix(projection);
}








void Window::EarlyUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	SetUpDocking();
}

void Window::LateUpdate() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //before swapping buffers
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}




	glfwSwapBuffers(window);
	Controller::ResetMouse(); //before polling events
	glfwPollEvents();

	shouldClose = glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetWindow() {
	return window;
}
Shader Window::GetShaderProgram() {
	return shaderProgram;
}
bool Window::GetShouldClose() {
	return shouldClose;
}


float Window::GetWidth() {
	return width;
}
float Window::GetHeight() {
	return height;
}
float Window::GetAspectRatio() {
	return aspectRatio;
}




void Window::SetUpDocking()
{

    //static bool opt_fullscreen = true;
    //static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoUndocking;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
   // if (opt_fullscreen)
    //{
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		
    //}
    //else
    //{ 
       // dockspace_flags &= ImGuiDockNodeFlags_PassthruCentralNode;
    //}


    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

	bool a = true;
    //if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &a, window_flags);
    //if (!opt_padding)
        ImGui::PopStyleVar();

    //if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }


    //if (ImGui::BeginMenuBar())
    //{
    //    if (ImGui::BeginMenu("Options"))
    //    {

    //        //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
    //        //ImGui::MenuItem("Padding", NULL, &opt_padding);
    //        ImGui::Separator();

    //        if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
    //        if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
    //        if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
    //        if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
    //        if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
    //        if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, true)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
    //        ImGui::Separator();
			
			

    //        /*if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
    //            *p_open = false;*/
    //        ImGui::EndMenu();
    //    }

    //    ImGui::EndMenuBar();
    //}

    ImGui::End();
}


ImVec2 Window::GetWidget1Dimensions() {
	return ImVec2(width - XRightOffset, yDownOffset);
}
ImVec2 Window::GetWidget2Dimensions() {
	return ImVec2(XRightOffset, height * 0.4f);
}
ImVec2 Window::GetWidget3Dimensions() {
	return ImVec2(XRightOffset, height * 0.6f);
}



float Window::width = 2000;
float Window::height = 1200;


float Window::yDownOffset = 200;
float Window::XRightOffset = 500;

glm::vec2 Window::lowerLeft = glm::vec2(0, yDownOffset);
glm::vec2 Window::upperRight = glm::vec2(width - XRightOffset, height);

float Window::aspectRatio = ((upperRight.x - lowerLeft.x)) / ((upperRight.y));


Shader Window::shaderProgram = Shader();