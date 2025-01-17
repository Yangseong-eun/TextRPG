#pragma once

class Item
{
public:
	enum class ItemType
	{
		HealthPotion,
		AttackBoost
	};

private:
	ItemType	m_itemType;
	std::string m_itemName;
	int32		m_itemPrice;

public:
	Item(ItemType type, const std::string& name, int32 price)
		: m_itemType(type), m_itemName(name), m_itemPrice(price) {}

	virtual ~Item() = default;

public:
	std::string getName() const { return m_itemName; }
	int32 getPrice() const { return m_itemPrice; }
	virtual void use(class Player* player) = 0;
};

