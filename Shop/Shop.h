#pragma once
#include "../Manager/GameManager.h"
#include "../Player/Player.h"
#include "../Item/Item.h"
#include "ShopMessage.h"
class Shop
{
private:
	std::unordered_map<std::string, std::shared_ptr<Item>> items;

public:
	Shop();
	~Shop();
public:
	void Update(float DeltaTime);
	void Render(float DeltaTime);
public:
	void buyItem(const std::string& ItemName, Player* player);
	void sellItem(const std::string& Itemname, Player* player);
	std::vector<std::shared_ptr<Item>> getItems();
	std::unique_ptr<ShopMessage> m_MessageObj;
};

