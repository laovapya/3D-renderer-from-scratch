#include "UI.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"

#include"Controller.h"


UI::UI(Scene* scene) {

    this->scene = scene;
    AddFirstLightsource();

    



}
void UI::AddFirstLightsource() {//temporary, this should be in scene or object manager. 
    int id = scene->GetObjectManager()->AddLightsource();
    scene->GetObjectManager()->GetCreatedObjects()[0]->Translate({6,4,-8});
    
    std::string name = "lightsource" + std::to_string(lightsourceCount++);

    ListedObject item(false, id, name, Object3D::type::lightsource);

    AddItem(item);
}
void UI::DrawObjectMenu() {
    ImVec2 size = ImVec2(100, 100);
    float xOffset = 25;
    float yOffset = 50;
    float xDistance = 150;
   
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget1Dimensions(), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Component menu", NULL,  ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse)) {//

        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 0, yOffset));
        if (ImGui::Button("cube", size)) {
            int id = scene->GetObjectManager()->AddCube();
            //const char* name = ("cube" + char(cubeCount++));
            std::string name = "cube" + std::to_string(cubeCount++);

            ListedObject item(false, id, name, Object3D::type::cube);

            AddItem(item);

        }

        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 1, yOffset));
        if (ImGui::Button("cylinder", size)) { 
            int id = scene->GetObjectManager()->AddCylinder();
            std::string name = "cylinder" + std::to_string(cylinderCount++);

   
            ListedObject item(false, id, name, Object3D::type::cylinder);

            AddItem(item);
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 2, yOffset));
        if (ImGui::Button("cone", size)) {
            int id = scene->GetObjectManager()->AddCone();
            std::string name = "cone" + std::to_string(coneCount++);

           
            ListedObject item(false, id, name, Object3D::type::cone);
           
            AddItem(item);
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 3, yOffset));
        if (ImGui::Button("sphere", size)) {
            int id = scene->GetObjectManager()->AddSphere();
            std::string name = "sphere" + std::to_string(sphereCount++);


            ListedObject item(false, id, name, Object3D::type::sphere);

            AddItem(item);
        }

    }
    ImGui::End();
}


//loop should go through all the objects in objectmanager, items should be based on object manager
void UI::DrawObjectList() {
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget2Dimensions(), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Object list", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) { //
        
        ImGui::PushItemWidth(-1);
      
        ImVec2 vec(0, 0);
        
        if (ImGui::BeginListBox("   0", ImVec2(-FLT_MIN, objectListMenuHeight * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int i = 0; i < maxObjectCount; i++)
            {
                if (items[i].id == -1)
                    continue;
              
                if (!ImGui::Selectable(items[i].name.c_str(), items[i].isSelected))
                    continue;
                    
                items[i].isSelected = !items[i].isSelected;

                if (items[i].isSelected)
                    scene->GetObjectManager()->SelectObject(items[i].id);
                else
                    scene->GetObjectManager()->DeselectObject(items[i].id);


                if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
                    continue;
                for (int j = 0; j < maxObjectCount; ++j) {
                    if (items[i].id == -1 || i == j)
                        continue;
                    items[j].isSelected = false;
                    scene->GetObjectManager()->DeselectObject(items[j].id);
                }
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();
}
void UI::DeleteItems() {
    for (int i = 0; i < maxObjectCount; ++i) {
        if (!items[i].isSelected)
            continue;
        scene->GetObjectManager()->RemoveObject(items[i].id);

        if (items[i].shape == Object3D::type::cube) 
            cubeCount--; 
        if (items[i].shape == Object3D::type::cone) 
            coneCount--;
        if (items[i].shape == Object3D::type::cylinder) 
            cylinderCount--;
        if (items[i].shape == Object3D::type::sphere)
            sphereCount--;
        if (items[i].shape == Object3D::type::lightsource)
            lightsourceCount--;
        if (items[i].shape == Object3D::type::camera)
            cameraCount--;
        

        items[i] = ListedObject();
        currentCount--;
    }
    ReInitItems();
}

void UI::DrawTransformMenu() {
    
    ImGui::SetNextWindowSize(scene->GetWindow()->GetWidget3Dimensions(), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Transform menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) { //
        //ImVec4 v(0,0, 0, 0);
        ImGui::Text("       X              Y               Z");
        float max = 10;
        ImGui::SliderFloat3("Translate", positionBuffer, -max, max);

        max = 360;
        ImGui::SliderFloat3("Rotate", rotationBuffer, 0, max);

        max = 10;
        ImGui::SliderFloat3("Scale", scaleBuffer, -max, max);
        

        if (ImGui::Button("Transform", ImVec2(100, 20))) {
            for (Object3D* s : scene->GetObjectManager()->GetCreatedObjects()) {
                if (!s->isSelected)
                    continue;
                s->Translate(positionBuffer);
                s->Rotate(rotationBuffer);
                s->Scale(scaleBuffer);
            }
            positionBuffer[0] = 0;
            positionBuffer[1] = 0;
            positionBuffer[2] = 0;

            rotationBuffer[0] = 0;
            rotationBuffer[1] = 0;
            rotationBuffer[2] = 0;

            scaleBuffer[0] = 0;
            scaleBuffer[1] = 0;
            scaleBuffer[2] = 0;
        }
    }
   
    if (ImGui::Button("Delete", ImVec2(100, 20)) || ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        DeleteItems();
    }

    Controller& instance = Controller::GetInstance();

    /*float xOffset = 50;
    float yOffset = 300;
    float xDistance = 180;*/

    ImGui::SetCursorPos(ImVec2(5, 180));

    ImGui::Text("Mouse controls");
    ImGui::Checkbox("X", &instance.isXaxisEnabled);
    //ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 1, yOffset));
    ImGui::Checkbox("Y", &instance.isYaxisEnabled);
    //ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 2, yOffset));
    ImGui::Checkbox("Z", &instance.isZaxisEnabled);


    ImGui::Checkbox("Translation", &instance.isTranslating);

    ImGui::Checkbox("Rotation", &instance.isRotating);

    ImGui::Checkbox("Scale", &instance.isScaling);

    if (ImGui::Button("Reset", ImVec2(100, 20)) || ImGui::IsMouseClicked(1)) {
        instance.isXaxisEnabled = false;
        instance.isYaxisEnabled = false;
        instance.isZaxisEnabled = false;

        instance.isTranslating = false;
        instance.isRotating = false;
        instance.isScaling = false;
    }

    ImGui::End();

}

void UI::DrawColoringMenu(){ //update this 
    ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver); //set dimensions later 
    if (ImGui::Begin("Coloring", NULL,  ImGuiWindowFlags_NoCollapse))//ImGuiWindowFlags_NoResize |
    {
        ImGui::ColorPicker4("Coloring", colorBuffer);
        if (ImGui::Button("Apply color", ImVec2(100, 20))){
            //Controller::SetActiveColor(glm::vec4(colorBuffer[0], colorBuffer[1], colorBuffer[2], colorBuffer[3]))
            for(Object3D* object : scene->GetObjectManager()->GetCreatedObjects()){
                if (object->isSelected){
                    object->SetColor(glm::vec4(colorBuffer[0], colorBuffer[1], colorBuffer[2], colorBuffer[3]));
                    if (object->GetType() == Object3D::type::lightsource)
                    {
                        scene->GetWindow()->GetLitShader()->Activate();
                        scene->GetWindow()->GetLitShader()->SetLightColor(glm::vec3(colorBuffer[0], colorBuffer[1], colorBuffer[2]));
                    }
                }
            }
        }
    }
    ImGui::End();
}
void UI::AddItem(ListedObject& item) {
    if (currentCount >= maxObjectCount) {
        std::cout << "max count reached" << std::endl;
        return;
    }
    item.isSelected = true;
    items[currentCount++] = item;

    scene->GetObjectManager()->SelectObject(item.id);
    for (int i = 0; i < maxObjectCount; ++i) {
        if (items[i].id == item.id)
            continue;
        scene->GetObjectManager()->DeselectObject(items[i].id);
        items[i].isSelected = false;
    }
}

void UI::ReInitItems() {
    ListedObject temp[32];
    for (int i = 0, j = 0; i < maxObjectCount; ++i) {
        if (items[i].id != -1)
            temp[j++] = items[i];
    }
    for (int i = 0; i < maxObjectCount; ++i) 
        items[i] = temp[i];

}
