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
    Scene scene(&window);
    UI ui(&window, scene.GetObjectManager());
    


    while (true) { //main loop
        DeltaTime::SetDeltaTime(glfwGetTime());
        window.EarlyUpdate();
        scene.Update();
       

        ui.DrawScene();
        ui.DrawObjectList();
        ui.DrawComponentMenu();
        ui.DrawTransformMenu();
        ui.DrawColoringMenu();

        
        window.LateUpdate();
       

        if (window.GetShouldClose()) {
            //std::cout<<"should close"<<std::endl;
            break;
        }
            
    }
    //std::cin.ignore();
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





