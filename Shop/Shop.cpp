#include "pch.h"
#include "Shop.h"
#include "../Item/AttackBoost.h"
#include "../Item/HealthPotion.h"
#include <memory>


Shop::Shop()
{
	items["힘의 영약"] = std::make_shared<AttackBoost>();
	items["체력 포션"] = std::make_shared<HealthPotion>();
	m_MessageObj = std::make_unique<ShopMessage>();
}

Shop::~Shop()
{
	items.clear();
}

void Shop::Update(float DeltaTime)
{
	m_MessageObj->Update(DeltaTime);
}

void Shop::Render(float DeltaTime)
{
	m_MessageObj->Render(DeltaTime);
}

void Shop::buyItem(const std::string& ItemName, Player* player)
{
	// player 유효성 검사
	if (player == nullptr)
	{
		return;
	}

	// index 유효성 검사
	if (items[ItemName].get() == nullptr)
	{
		m_MessageObj->m_listText.push_back("구매할 아이템이 존재하지 않습니다..");
		return;
	}

	// 구매할 아이템 정보
	std::shared_ptr<Item> BuyItem = items[ItemName];
	int32 BuyPrice = BuyItem->getPrice();

	// player의 소지 골드 검사
	if (player->getGold() >= BuyPrice)
	{
		// player 아이템 목록에 구매한 아이템 추가
		player->addItem(BuyItem);

		// 상점 아이템 목록에서 구매한 아이템 제거
		items.erase(items.find(ItemName));

		m_MessageObj->m_listText.push_back("구매완료.");
		// player 골드 감소
		player->addGold(-BuyPrice);
	}
	else
	{
		m_MessageObj->m_listText.push_back("골드가 부족합니다.");
		return;
	}
}

void Shop::sellItem(const std::string& ItemName, Player* player)
{
	// player 유효성 검사
	if (player == nullptr)
	{
		return;
	}
	auto item = player->getItem(ItemName);
	// index 유효성 검사
	if (item == nullptr)
	{
		m_MessageObj->m_listText.push_back("판매할 아이템이 존재하지 않습니다..");
		return;
	}
	uint32 SellPrice = item->getPrice() * 0.6;

	// 판매 여부 확인
	m_MessageObj->m_listText.push_back(item->getName() + "을(를) 판매합니다.]");
	// player 아이템 목록에서 판매한 아이템 제거
	player->removeItem(item);
	// player 골드 증가
	player->addGold(SellPrice);
}

std::vector<std::shared_ptr<Item>> Shop::getItems()
{
	std::vector<std::shared_ptr<Item>> vecItem;

	auto iter = items.begin();
	auto iter_end = items.end();

	for (; iter != iter_end ; ++iter)
	{
		vecItem.push_back(iter->second);
	}
	return vecItem;
}
