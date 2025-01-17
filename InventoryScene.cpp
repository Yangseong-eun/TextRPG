#include "pch.h"
#include "InventoryScene.h"
#include "ConsoleObject.h"
#include "ConsoleRender.h"
#include "MainScene.h"

// 1. 아이템을 볼 수 있어야한다.
InventoryScene::InventoryScene() : m_Player(Player::GetInst()) {}

InventoryScene::~InventoryScene() {}

void InventoryScene::Start()
{

}

void InventoryScene::Update(float DeltaTime)
{
    if (m_vecObject.empty())
        return;
    for (const auto& iter : m_vecObject)
        iter->Update(DeltaTime);
}

void InventoryScene::Render(float DeltaTime)
{
    if (m_vecObject.empty())
        return;

    for (const auto& iter : m_vecObject)
        iter->Update(DeltaTime);
}