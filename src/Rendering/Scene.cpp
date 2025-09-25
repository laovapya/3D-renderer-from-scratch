#include "Scene.h"

Scene::Scene(const Window* window)
{
	this->window = window;
	// initialCamera = std::make_unique<Camera>();
	// currentCamera = initialCamera.get();
	litShader = window->GetLitShader();
	defaultShader = window->GetDefaultShader();

	window->GetLitShader()->Activate();
	litShader->SetLightColors(manager.GetLightsourceColors());

	TextureManager::GetInstance();
}

Scene::~Scene()
{
	VertexData::GetGridVAO().Delete();
	VertexData::GetXaxisVAO().Delete();
	VertexData::GetZaxisVAO().Delete();
	//manager.DeleteAllObjects();
	TextureManager::UnloadAllTextures();
}

void Scene::DrawGrid()
{
	defaultShader->Activate();
	defaultShader->SetViewMatrix(currentCamera->GetViewMatrix());
	defaultShader->SetModelMatrix(Matrix4()); // use identity matrix

	defaultShader->SetAlpha(0.7f);

	defaultShader->SetRenderColor(Vector3(1, 0, 0));
	VertexData::GetXaxisVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	defaultShader->SetRenderColor(Vector3(0, 1, 0));
	VertexData::GetZaxisVAO().Bind();
	glDrawArrays(GL_LINES, 0, 2);

	defaultShader->SetAlpha(0.9f);
	defaultShader->SetRenderColor(Vector3(0.2f, 0.2f, 0.2f));
	VertexData::GetGridVAO().Bind();
	glDrawArrays(GL_LINES, 0, VertexData::GetGridIndexCount());
}

void Scene::Update()
{
	Controller::MoveCamera(window->GetWindow(), initialCamera.get());

	Vector3 v = Controller::GetTransformVector(initialCamera.get());
	for(const auto& object : manager.GetCreatedObjects())
	{
		object->GetVAO().Bind();

		if(object->GetIfSelected())
		{
			// transformations
			if(Controller::GetTranslating())
				object->Translate(v * DeltaTime::GetDeltaTime());
			if(Controller::GetScaling())
				object->Scale(v * DeltaTime::GetDeltaTime());
			if(Controller::GetRotating())
				object->Rotate(v * Controller::GetRotationSpeed() * DeltaTime::GetDeltaTime());
		}
		Material& material = object->GetMaterial();

		const Shader* shader = material.GetIfLit() ? litShader : defaultShader;
		shader->Activate();
		if(material.GetIfLit())
		{
			litShader->ActivateTexture(material.GetTextureID(), 0);
			litShader->SetLightPositions(manager.GetLightsourcePositions());
		}

		shader->SetViewMatrix(currentCamera->GetViewMatrix());
		shader->SetModelMatrix(object->GetModelMatrix());
		shader->SetRenderColor(object->GetMaterial().GetColor());

		glDrawElements(GL_TRIANGLES, object->GetIndexCount(), GL_UNSIGNED_INT, 0);

		if(object->GetIfSelected())
		{
			defaultShader->Activate();
			defaultShader->SetViewMatrix(currentCamera->GetViewMatrix());
			defaultShader->SetModelMatrix(object->GetModelMatrix());
			defaultShader->SetRenderColor(Material::selectColor);
			glDrawElements(GL_LINES, object->GetIndexCount(), GL_UNSIGNED_INT, 0);
		}
	}

	DrawGrid();
}

ObjectManager* Scene::GetObjectManager()
{
	return &manager;
}
