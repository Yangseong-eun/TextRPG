#pragma once
#include "Item.h"

class HealthPotion : public Item
{
private:
	uint32 m_healthRestore;

public:
	HealthPotion() : Item(ItemType::HealthPotion, "체력 포션", 10), m_healthRestore(50) {}

public:
	virtual void use(class Player* player) override;
};

