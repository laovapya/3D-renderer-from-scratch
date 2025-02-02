#include "Scene.h"

#include"VertexData.h"
#include"DeltaTime.h"

Scene::Scene(Window* window) {
	this->window = window;
}

Scene::~Scene() {
	VertexData::GetConeVAO().Delete();
	VertexData::GetCubeVAO().Delete();
	VertexData::GetCylinderVAO().Delete();
	VertexData::GetSphereVAO().Delete();
	VertexData::GetGridVAO().Delete();
	VertexData::GetXVAO().Delete();
	VertexData::GetZVAO().Delete();
}

void Scene::DrawGrid() {
	Shader shaderProgram = window->GetShaderProgram();
	shaderProgram.SetMatrix(Camera::GetViewMatrix());
	shaderProgram.SetAlpha(0.7f);

	shaderProgram.SetColor(glm::vec3(1, 0, 0));
	VertexData::GetXVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	shaderProgram.SetColor(glm::vec3(0, 1, 0));
	VertexData::GetZVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	shaderProgram.SetAlpha(0.9f);
	shaderProgram.SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
	VertexData::GetGridVAO().Bind();
	glDrawArrays(GL_LINES, 0, VertexData::GetGridIndexCount());
}

void Scene::Update() { // into main loop
	Controller::MoveCamera(window->GetWindow());

	Shader shaderProgram = window->GetShaderProgram();
	shaderProgram.SetAlpha(1.0f);

	glm::vec3 v = Controller::GetTransformVector();

	int i = 0;
	for (Shape* object : manager.GetCreatedObjects()) {
		shaderProgram.SetColor(object->GetColor());
		if (object->isSelected) {

			if (Controller::GetTranslating())
				object->Translate(v * DeltaTime::GetDeltaTime());
			if (Controller::GetScaling())
				object->Scale(v * DeltaTime::GetDeltaTime());
			if (Controller::GetRotating())
				object->Rotate(v * DeltaTime::GetDeltaTime());
		}

		shaderProgram.SetMatrix(Camera::GetViewMatrix() * Shape::GetObjectMatrix(object)); // projection * view * local * vector; 
		object->GetVAO().Bind();
		glDrawElements(GL_TRIANGLES, object->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}

	DrawGrid();
}

Window* Scene::GetWindow() {
	return window;
}

ObjectManager* Scene::GetObjectManager() {
	return &manager;
}