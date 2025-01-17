#include "pch.h"
#include "TitleScene.h"
#include "TitleObj.h"
#include "TitleText.h"
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	m_vecObject.clear();
}

void TitleScene::Start()
{
	m_vecObject.push_back(std::make_unique<TitleObj>(this));
	m_vecObject.push_back(std::make_unique<TitleText>(this));
}

void TitleScene::Update(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& obj : m_vecObject)
	{
		obj->Update(DeltaTime);
	}
}

void TitleScene::Render(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& obj : m_vecObject)
	{
		obj->Render(DeltaTime);
	}
}
