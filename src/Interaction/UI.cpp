#include "UI.h"
#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"

#include "Controller.h"

UI::UI(const Window* window, ObjectManager* objectManager)
{

	this->window = window;
	this->objectManager = objectManager;
}
void UI::DrawScene()
{
	ImGui::Begin("Scene");

	ImVec2 windowSize = ImGui::GetContentRegionAvail(); //all remaining available space

	ImGui::Image((ImTextureID)((intptr_t)(window->GetSceneTexture())),
				 windowSize,
				 ImVec2(0, 1),
				 ImVec2(1, 0));

	ImGui::End();
}

void UI::DrawComponentMenu()
{
	ImVec2 size = ImVec2(100, 100);
	float xOffset = 25;
	float yOffset = 50;
	float xDistance = 150;

	if(ImGui::Begin(
		   "Component menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		int count = objectManager->GetCreatedObjects().size();

		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 0, yOffset));
		if(ImGui::Button("cube", size) && count < maxObjectCount)
		{
			objectManager->AddCube();
		}
		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 1, yOffset));
		if(ImGui::Button("cylinder", size) && count < maxObjectCount)
		{
			objectManager->AddCylinder();
		}
		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 2, yOffset));
		if(ImGui::Button("cone", size) && count < maxObjectCount)
		{
			objectManager->AddCone();
		}
		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 3, yOffset));
		if(ImGui::Button("sphere", size) && count < maxObjectCount)
		{
			objectManager->AddSphere();
		}
		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 4, yOffset));
		if(ImGui::Button("light", size) && count < maxObjectCount)
		{
			objectManager->AddLightsource();
		}
		ImGui::SetCursorPos(ImVec2(xOffset + xDistance * 5, yOffset * 1.8f));
		ImGui::SetNextItemWidth(250);
		int min = 4;
		int max = 32;
		if(ImGui::SliderInt("Segment Count", segmentsBuffer, min, max))
		{
			objectManager->SetSegmentCount(segmentsBuffer[0]);
		}
	}
	ImGui::End();
}

void UI::DrawObjectList()
{

	if(ImGui::Begin("Object list", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{ //

		ImGui::PushItemWidth(-1);

		ImVec2 vec(0, 0);

		if(ImGui::BeginListBox(
			   "0", ImVec2(-FLT_MIN, objectListMenuHeight * ImGui::GetTextLineHeightWithSpacing())))
		{

			for(const auto& item : objectManager->GetCreatedObjects())
			{
				bool isSelected = item->GetIfSelected();
				if(!ImGui::Selectable(item->name.c_str(), isSelected))
					continue;

				item->SetSelected(!isSelected);

				if(ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
					continue;

				for(const auto& other : objectManager->GetCreatedObjects())
				{
					if(other == item)
						continue;
					other->SetSelected(false);
				}
			}
			ImGui::EndListBox();
		}
	}
	ImGui::End();
}

void UI::DrawTransformMenu()
{

	if(ImGui::Begin(
		   "Transform menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{ //

		ImGui::Text("       X              Y               Z");
		float max = 10;
		ImGui::SliderFloat3("Translate", positionBuffer, -max, max);

		max = 360;
		ImGui::SliderFloat3("Rotate", rotationBuffer, 0, max);

		max = 10;
		ImGui::SliderFloat3("Scale", scaleBuffer, -max, max);

		if(ImGui::Button("Transform", ImVec2(100, 20)))
		{
			for(const auto& s : objectManager->GetCreatedObjects())
			{
				if(!s->GetIfSelected())
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

	if(ImGui::Button("Delete", ImVec2(100, 20)) || ImGui::IsKeyPressed(ImGuiKey_Delete))
	{
		objectManager->RemoveSelectedObjects();
	}

	Controller& instance = Controller::GetInstance();

	ImGui::SetCursorPos(ImVec2(5, 180));

	ImGui::Text("Mouse controls");
	ImGui::Checkbox("X", &instance.isXaxisEnabled);

	ImGui::Checkbox("Y", &instance.isYaxisEnabled);

	ImGui::Checkbox("Z", &instance.isZaxisEnabled);

	ImGui::Checkbox("Translation", &instance.isTranslating);

	ImGui::Checkbox("Rotation", &instance.isRotating);

	ImGui::Checkbox("Scale", &instance.isScaling);

	if(ImGui::Button("Reset", ImVec2(100, 20)) || ImGui::IsMouseClicked(1))
	{
		instance.isXaxisEnabled = false;
		instance.isYaxisEnabled = false;
		instance.isZaxisEnabled = false;

		instance.isTranslating = false;
		instance.isRotating = false;
		instance.isScaling = false;
	}

	ImGui::End();
}

void UI::DrawColoringMenu()
{ //update this
	ImGui::SetNextWindowSize(ImVec2(100, 300), ImGuiCond_FirstUseEver);
	if(ImGui::Begin("Material constructor", NULL, ImGuiWindowFlags_NoCollapse))
	{
		ImGui::BeginChild("ColorPickerRegion", ImVec2(300, 300), true);
		ImGui::ColorPicker4("##Coloring", colorBuffer, ImGuiColorEditFlags_NoSidePreview);
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("TexturePreviewRegion", ImVec2(300, 300), true);
		if(textureIDbuffer >= 0 && textureIDbuffer < (int)TextureManager::textures.size())
		{
			ImGui::Text("Preview:");
			ImGui::Image((ImTextureID)(intptr_t)TextureManager::textures[textureIDbuffer],
						 ImVec2(128, 128),
						 ImVec2(0, 1),
						 ImVec2(1, 0));
		}
		if(ImGui::Button("Load Texture"))
		{
			std::string path = GetTextureFilePath(); //time freezes
			if(!path.empty())
			{

				textureIDbuffer = TextureManager::LoadTexture(path);
				std::cout << textureIDbuffer;
			}

			else
			{
				std::cout << " empty!!!";
				textureIDbuffer = 0;
			}
		}
		ImGui::EndChild();
		//std::cout << TextureManager::textures.size();

		if(ImGui::Button("Apply", ImVec2(100, 20)))
		{

			for(const auto& object : objectManager->GetCreatedObjects())
			{
				if(object->GetIfSelected())
				{
					Material& material = object->GetMaterial();
					material.SetColor(
						colorBuffer[0], colorBuffer[1], colorBuffer[2], colorBuffer[3]);

					if(object->GetType() == Object3D::type::lightsource)
					{
						window->GetLitShader()->Activate();
						window->GetLitShader()->SetLightColors(
							objectManager->GetLightsourceColors());
					}
					else
						material.SetTexture(textureIDbuffer);
				}
			}
		}
	}
	ImGui::End();
}

int UI::GetSegmentCount() const
{
	return segmentsBuffer[0];
}

std::string UI::GetTextureFilePath()
{
	nfdu8char_t* outPath = nullptr;

	nfdu8filteritem_t filters[2];
	filters[0].name = (nfdu8char_t*)"Images";
	filters[0].spec = (nfdu8char_t*)"png";
	filters[1].name = (nfdu8char_t*)"Photos";
	filters[1].spec = (nfdu8char_t*)"jpg,jpeg";

	nfdresult_t result = NFD_OpenDialogU8(&outPath, filters, 2, nullptr);
	if(result == NFD_OKAY)
	{
		std::string filePath = outPath;
		NFD_FreePath(outPath);
		return filePath;
	}
	return "";
}
