#include "UI.h"
#include"Cube.h"
#include"Cone.h"
#include"Cylinder.h"
#include"Sphere.h"

#include"Controller.h"


UI::UI(const Window* window, ObjectManager* objectManager) {

    this->window = window;
    this->objectManager = objectManager;
   
    



}
void UI::DrawScene() {
    //ImGui::SetNextWindowSize(window->GetWidget1Dimensions(), ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene");

    ImVec2 windowSize = ImGui::GetContentRegionAvail(); //all remaining available space
   
    ImGui::Image((ImTextureID)((intptr_t)(window->GetColorTexture())), windowSize, ImVec2(0, 1), ImVec2(1, 0));
  
    ImGui::End();
}

void UI::DrawComponentMenu() {
    ImVec2 size = ImVec2(100, 100);
    float xOffset = 25;
    float yOffset = 50;
    float xDistance = 150;
   

    if (ImGui::Begin("Component menu", NULL,  ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse)) {//

        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 0, yOffset));
        if (ImGui::Button("cube", size)) {
            int id = objectManager->AddCube();
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 1, yOffset));
        if (ImGui::Button("cylinder", size)) { 
            int id = objectManager->AddCylinder();
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 2, yOffset));
        if (ImGui::Button("cone", size)) {
            int id = objectManager->AddCone();
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 3, yOffset));
        if (ImGui::Button("sphere", size)) {
            int id = objectManager->AddSphere();
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 4, yOffset));
        if (ImGui::Button("light", size)) {
            int id = objectManager->AddLightsource();
        }
        ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 5, yOffset * 1.8f));
        ImGui::SetNextItemWidth(250);
        int min = 4;
        int max = 32;
        if (ImGui::SliderInt("Segment Count", segmentsBuffer, min, max)) {
            objectManager->SetSegmentCount(segmentsBuffer[0]);
        }
    }
    ImGui::End();
}


//loop should go through all the objects in objectmanager, items should be based on object manager
void UI::DrawObjectList() {

    if (ImGui::Begin("Object list", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) { //
        
        ImGui::PushItemWidth(-1);
      
        ImVec2 vec(0, 0);
        
        if (ImGui::BeginListBox("0", ImVec2(-FLT_MIN, objectListMenuHeight * ImGui::GetTextLineHeightWithSpacing())))
        {
            
            for (Object3D* item : objectManager->GetCreatedObjects()) {
                bool isSelected = item->GetIfSelected();
                if (!ImGui::Selectable(item->name.c_str(), isSelected))
                    continue;

                item->SetSelected(!isSelected);

                if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
                    continue;

                for (Object3D* other : objectManager->GetCreatedObjects()) {
                    if (other == item)
                        continue;
                    other->SetSelected(false);
                }
            }
            ImGui::EndListBox();
        }
    }
    ImGui::End();
}


void UI::DrawTransformMenu() {
    
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
            for (Object3D* s : objectManager->GetCreatedObjects()) {
                if (!s->GetIfSelected())
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
        objectManager->RemoveSelectedObjects();
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
    ImGui::SetNextWindowSize(ImVec2(100, 300), ImGuiCond_FirstUseEver); //set dimensions later 
    if (ImGui::Begin("Coloring", NULL,  ImGuiWindowFlags_NoCollapse ))//ImGuiWindowFlags_NoResize |
    {
        ImGui::ColorPicker4("Coloring", colorBuffer);
        //ImVec2 size = ImGui::GetWindowSize();
        //ImGui::SetCursorPos(ImVec2(size.x * 0.75f, size.y * 0.8f));
        if (ImGui::Button("Apply", ImVec2(100, 20))){
            //Controller::SetActiveColor(glm::vec4(colorBuffer[0], colorBuffer[1], colorBuffer[2], colorBuffer[3]))
            for(Object3D* object : objectManager->GetCreatedObjects()){
                if (object->GetIfSelected()){
                    object->SetColor(glm::vec4(colorBuffer[0], colorBuffer[1], colorBuffer[2], colorBuffer[3]));
                    if (object->GetType() == Object3D::type::lightsource)
                    {
                        window->GetLitShader()->Activate();
                        window->GetLitShader()->SetLightColors(objectManager->GetLightsourceColors());
                    }
                }
            }
        }
    }
    ImGui::End();
}

int UI::GetSegmentCount() const {
    return segmentsBuffer[0];
}
//void UI::AddItem(ListedObject& item) {
//    if (currentCount >= maxObjectCount) {
//        std::cout << "max count reached" << std::endl;
//        return;
//    }
//    item.isSelected = true;
//    items[currentCount++] = item;
//
//    objectManager->SelectObject(item.id);
//    for (int i = 0; i < maxObjectCount; ++i) {
//        if (items[i].id == item.id)
//            continue;
//        objectManager->DeselectObject(items[i].id);
//        items[i].isSelected = false;
//    }
//}
//
//void UI::ReInitItems() {
//    ListedObject temp[maxObjectCount];
//    for (int i = 0, j = 0; i < maxObjectCount; ++i) {
//        if (items[i].id != -1)
//            temp[j++] = items[i];
//    }
//    for (int i = 0; i < maxObjectCount; ++i) 
//        items[i] = temp[i];
//
//}
