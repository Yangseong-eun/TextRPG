#include "pch.h"
#include "ShopScene.h"
#include "ShopArt.h"
#include "DisplayItems.h"
#include "Player/Player.h"
ShopScene::ShopScene()
{
	
}

ShopScene::~ShopScene()
{
}

void ShopScene::Start()
{
	m_vecObject.push_back(std::make_unique<ShopArt>(this));
	m_Shop = std::make_unique<Shop>();
	m_vecObject.push_back(std::make_unique<DisplayItems>(this));
}

void ShopScene::Update(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& iter : m_vecObject)
		iter->Update(DeltaTime);

	m_Shop->Update(DeltaTime);
}

void ShopScene::Render(float DeltaTime)
{
	if (m_vecObject.empty())
		return;

	for (const auto& iter : m_vecObject)
		iter->Render(DeltaTime);

	m_Shop->Render(DeltaTime);
}

void ShopScene::buyItem(const std::string& ItemName)
{
	m_Shop->buyItem(ItemName,Player::GetInst());
}

void ShopScene::sellItem(const std::string& ItemName)
{
	m_Shop->sellItem(ItemName, Player::GetInst());
}

std::vector<std::shared_ptr<Item>> ShopScene::GetItems() const
{
	return m_Shop->getItems();
}

const short ShopScene::getShopWidth(int ObjectIndex)
{
	return (short)m_vecObject[0]->getWidth();
}

const short ShopScene::getShopHeight(int ObjectIndex)
{
	return (short)m_vecObject[0]->getHeight();
}
