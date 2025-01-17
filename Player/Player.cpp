#include "pch.h"
#include "Player.h"
#include "Manager/GameManager.h"
#include "PlayerStatusObject.h"
#include "PlayerProfile.h"
#include "ConsoleRender.h"
#include "Logger.h"
Player::Player() :
	m_name(),
	m_level(1),
	m_currHealth(0),
	m_maxHealth(200),
	m_atk(30),
	m_currExperience(0),
	m_gold(0)
{
	m_currHealth = m_maxHealth;
}

Player::~Player()
{
    GameManager::GetInst()->GameEnd();
    CLogger::GetInst()->Log(LOG_CATEGORY::Nomal,"플레이어가 죽었습니다 꾸엑.");
}

bool Player::init()
{
    m_mapPlayerStatus["Profile"] = std::make_shared<PlayerProfile>();
    m_mapPlayerStatus["Status"] = std::make_shared<PlayerStatusObject>();
    
    for (uint32 i = 1; i <= 100; ++i)
    {
        m_mapExpTable[i] = (uint32)pow(((i+2 - 1) * 50 / 49.f), 2.5f);
    }
    m_maxExperience = m_mapExpTable[1];
    m_FieldPos = {0,};

    std::cout << "이름을 입력해 주세요 : ";
    std::cin >> m_name;
	return true;
}

void Player::levelUp()
{
	++m_level;
	m_atk = m_atk +  m_level * 5;

    if(m_mapExpTable[m_level] != 0)
        m_maxExperience = m_mapExpTable[m_level];

	m_maxHealth = m_level * 20;
	m_currHealth = m_maxHealth;
}

void Player::addItem(std::shared_ptr<Item> Item)
{
    if (m_mapItem[Item->getName()] == nullptr)
    {
        m_mapItem[Item->getName()] = Item;
    }
}

void Player::removeItem(const std::string& ItemName)
{
    if (m_mapItem[ItemName] != nullptr)
        m_mapItem[ItemName].reset();
}

void Player::removeItem(std::shared_ptr<Item> Item)
{
    if (m_mapItem[Item->getName()] != nullptr)
        m_mapItem[Item->getName()].reset();
}

std::shared_ptr<Item> Player::getItem(const std::string& ItemName)
{
    if(m_mapItem[ItemName] != nullptr)
        return m_mapItem[ItemName];

    return nullptr;
}

std::shared_ptr<Item> Player::getItem(std::shared_ptr<Item> Item)
{
    if (m_mapItem[Item->getName()] != nullptr)
        return m_mapItem[Item->getName()];

    return nullptr;
}

const int32& Player::takeDamage(const int32 Damage)
{
    if (m_currHealth - Damage <= 0)
        Destroy();

    m_currHealth -= Damage;
    return m_currHealth;
}

CursorPos Player::getFieldPos() const
{
    return CursorPos(m_FieldPos.X, m_FieldPos.Y);
}

void Player::SetFieldPos(const CursorPos& pos)
{
    m_FieldPos = pos;
}

void Player::addHealth(const int& Health)
{
    m_currHealth = m_currHealth + Health >= m_maxHealth ? m_maxHealth : m_currHealth + Health;
}

void Player::Update(float DeltaTime)
{
    if (m_Scene == nullptr)
    {
        m_Scene = ConsoleRender::GetInst()->GetScene();
    }
    for (const auto& iter : m_mapPlayerStatus)
    {
        iter.second->Update(DeltaTime);
    }
}

void Player::Render(float DeltaTime)
{
    for (const auto& iter : m_mapPlayerStatus)
    {
        iter.second->Render(DeltaTime);
    }
}

void Player::showPlayer()
{
    //TODO : 상태창보여주기
}

void Player::addExp(const int32 exp)
{
    if (m_currExperience + exp < m_maxExperience)
    {
        m_currExperience += exp;
        return;
    }
    m_currExperience += exp;
    while (m_currExperience > m_maxExperience)
    {
        m_currExperience -= m_maxExperience;
        levelUp();
    }

}

void Player::useItem(std::string ItemName)
{
    if(m_mapItem[ItemName] != nullptr)
        m_mapItem[ItemName]->use(this);
}

void Player::useItem(std::shared_ptr<Item> Item)
{
    if (m_mapItem[Item->getName()] != nullptr)
        m_mapItem[Item->getName()]->use(this);
}
