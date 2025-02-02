#include <iostream>

#pragma commment(lib,"opengl32.lib") 


#include<vector>;

#include"Cube.h"
#include"Window.h"
#include"Scene.h"
#include"DeltaTime.h"
#include"UI.h"
void DisplayKeys();





int main()
{
	DisplayKeys(); 

    Window window;
    ObjectManager manager;
    Scene scene(&window);
    UI ui(&scene);



    ////imgui stuff
    //ImVec4 color = ImVec4(0.25f, 0.25f, 0.25f, 1); //darker grey
    //ImGuiStyle& style = ImGui::GetStyle();
    //style.Colors[ImGuiCol_WindowBg] = color;
    //style.Colors[ImGuiCol_MenuBarBg] = color;

    while (true) { //main loop
        DeltaTime::SetDeltaTime(glfwGetTime());
        window.EarlyUpdate();


        ui.DrawObjectList();
        ui.DrawObjectMenu();
        ui.DrawTransformMenu();


        scene.Update();
        window.LateUpdate();

        if (window.GetShouldClose()) 
            break;
    }
    return 0;
}

void DisplayKeys() {
    std::cout << " Translate G" << std::endl;
    std::cout << " Rotate R" << std::endl;
    std::cout << " Scale S" << std::endl;

    std::cout << " X Axis - X" << std::endl;
    std::cout << " Y Axis - Y" << std::endl;
    std::cout << " Z Axis - Z" << std::endl;

    std::cout << " Zoom + -" << std::endl;
    std::cout << " Pan P + Mouse" << std::endl;
    std::cout << " Orbit O + Mouse" << std::endl;

    std::cout << " Transform object - Mouse" << std::endl;
}





