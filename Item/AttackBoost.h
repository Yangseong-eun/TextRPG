#pragma once
#include "Item.h"

class AttackBoost : public Item
{
private:
	uint32		m_attackIncrease;

public:
	AttackBoost() : Item(ItemType::AttackBoost, "힘의 영약", 15), m_attackIncrease(10) {}

public:
	virtual void use(class Player* player) override;
};

