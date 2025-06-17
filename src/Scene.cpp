#include "Scene.h"

#include"VertexData.h"
#include"DeltaTime.h"

Scene::Scene(const Window* window) {
	this->window = window;
	currentCamera = new Camera(); 

	litShader = window->GetLitShader();
	defaultShader = window->GetDefaultShader();

	window->GetLitShader()->Activate();
	litShader->SetLightColors(manager.GetLightsourceColors());
}

Scene::~Scene() {
	VertexData::GetGridVAO().Delete();
	VertexData::GetXaxisVAO().Delete();
	VertexData::GetZaxisVAO().Delete();
}

void Scene::DrawGrid() {

	defaultShader->Activate();
	defaultShader->SetViewMatrix(currentCamera->GetViewMatrix());
	defaultShader->SetLocalMatrix(glm::mat4(1.0f));
	
	defaultShader->SetAlpha(0.7f);
			
	defaultShader->SetRenderColor(glm::vec3(1, 0, 0));
	VertexData::GetXaxisVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	defaultShader->SetRenderColor(glm::vec3(0, 1, 0));
	VertexData::GetZaxisVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	defaultShader->SetAlpha(0.9f);
	defaultShader->SetRenderColor(glm::vec3(0.2f, 0.2f, 0.2f));
	VertexData::GetGridVAO().Bind();
	glDrawArrays(GL_LINES, 0, VertexData::GetGridIndexCount());
}

void Scene::Update() { //goes into main loop
	Controller::MoveCamera(window->GetWindow(), currentCamera);
	
	glm::vec3 v = Controller::GetTransformVector(currentCamera);
	for (const auto& object : manager.GetCreatedObjects()) {
		object->GetVAO().Bind();

		if (object->GetIfSelected()) {
			//transformations
			if (Controller::GetTranslating())
				object->Translate(v * DeltaTime::GetDeltaTime());
			if (Controller::GetScaling())
				object->Scale(v * DeltaTime::GetDeltaTime());
			if (Controller::GetRotating())
				object->Rotate(v * DeltaTime::GetDeltaTime());
	
			
		}
		
		const Shader* shader = object->GetIfLit() ? litShader : defaultShader;
		shader->Activate();
		litShader->SetLightPositions(manager.GetLightsourcePositions()); 
		
		shader->SetViewMatrix(currentCamera->GetViewMatrix()); 
		shader->SetLocalMatrix(object->GetObjectMatrix());
		shader->SetRenderColor(object->GetColor());

		glDrawElements(GL_TRIANGLES, object->GetIndexCount(), GL_UNSIGNED_INT, 0);

		if (object->GetIfSelected()) {

			defaultShader->Activate();
			defaultShader->SetViewMatrix(currentCamera->GetViewMatrix());
			defaultShader->SetLocalMatrix(object->GetObjectMatrix());
			defaultShader->SetRenderColor(Object3D::selectColor);
			glDrawElements(GL_LINES, object->GetIndexCount(), GL_UNSIGNED_INT, 0);
		}
	}

	DrawGrid();
}


ObjectManager* Scene::GetObjectManager(){
	return &manager;
}