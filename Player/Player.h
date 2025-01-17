#pragma once
#include "Item.h"
class Player : public Singleton<Player>
{
	friend class BattleManager;
public:
	Player();
	virtual ~Player() override;

public:
	bool init();

private:
	std::string                                                           m_name;
	int32                                                                 m_level=1;
	int32                                                                 m_currHealth=200;
	int32                                                                 m_maxHealth=200;
	int32                                                                 m_atk=30;
	int32                                                                 m_maxExperience=0;
	int32                                                                 m_currExperience=0;
	int32                                                                 m_gold=0;
	std::unordered_map<std::string, std::shared_ptr<Item>>                m_mapItem;
	std::unordered_map<uint32, uint32>                                    m_mapExpTable;
	class Scene*                                                          m_Scene = nullptr;
	std::unordered_map<std::string, std::shared_ptr<class ConsoleObject>> m_mapPlayerStatus;
	bool                                                                  m_bDead=false;
	EStageType                                                            m_StageType;
	CursorPos m_FieldPos = {};
public:
	EStageType GetType() const { return m_StageType; }
	const std::string& getName() const { return m_name; }
	const int32& getLevel()const { return m_level; }
	const int32& getCurrHealth() const { return m_currHealth; }
	const int32& getMaxHealth() const { return m_maxHealth; }
	const int32& getAtk() const { return m_atk; }
	const int32& getGold() const { return m_gold; }
	const int32& takeDamage(const int32 Damage);
	bool isDead() const { return m_bDead; }
	CursorPos getFieldPos() const;
public:
	void SetFieldPos(const CursorPos& pos);
	void SetName(const std::string& Name) { m_name = Name; }
	void SetGold(const int32& Gold) { m_gold = Gold; }
	void SetCurrentHealth(const int32& Health) { m_currHealth = Health; }
	void SetStage(const EStageType Type) { m_StageType = Type; }
public:
	void addAtk(const int& Atk) { m_atk += Atk; }
	void addHealth(const int& Health);
public:
	void Update(float DeltaTime);
	void Render(float DeltaTime);

	void showPlayer();
	void levelUp();

	void addGold(int gold) { m_gold += gold; }
	void addExp(const int32 exp);

	void useItem(std::string ItemName);
	void useItem(std::shared_ptr<Item> Item);

	void addItem(std::shared_ptr<Item> Item);
	void removeItem(const std::string& ItemName);
	void removeItem(std::shared_ptr<Item> Item);

	const std::unordered_map<std::string, std::shared_ptr<Item>>& getAllItems() const { return m_mapItem; }
	std::shared_ptr<Item> getItem(const std::string& ItemName);
	std::shared_ptr<Item> getItem(std::shared_ptr<Item> Item);
};

