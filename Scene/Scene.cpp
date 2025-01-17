#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	m_vecObject.clear();
}

void Scene::Update(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& iter : m_vecObject)
		iter->Update(DeltaTime);
}

void Scene::Render(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& iter : m_vecObject)
		iter->Render(DeltaTime);
}

