#include "pch.h"
#include "BattleScene.h"
#include "Logger.h"
#include "Monster.h"
#include "ConsoleRender.h"
#include "Player/Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "MonsterArtObject.h"
#include "BattleMenuObject.h"
#include "BattleMessage.h"
#include "MonsterHPBar.h"
#include "FieldScene.h"
#include "../Manager/BattleManager.h"
#include "MainScene.h"
BattleScene::BattleScene() :
	m_Monster(nullptr),
	m_Player(nullptr),
	m_Render(nullptr)
{
	if (m_Player == nullptr)
		m_Player = Player::GetInst();
}
BattleScene::BattleScene(Monster* Monster)
{
	m_Monster = Monster;
}

size_t BattleScene::GetCursorY(EBattleObjectType Obj)
{
	return m_vecObject[(int)Obj]->GetCursorY();
}

void BattleScene::Start()
{
	m_Player = Player::GetInst();
	m_Render = ConsoleRender::GetInst();
	m_vecObject.resize((int)EBattleObjectType::Max);
	m_vecObject[(int)EBattleObjectType::Menu] = std::make_unique<BattleMenuObject>(this);
	m_vecObject[(int)EBattleObjectType::Message] = std::make_unique<BattleMessage>(this);
	m_vecObject[(int)EBattleObjectType::MonsterArt] = std::make_unique<MonsterArtObject>(this);
	m_vecObject[(int)EBattleObjectType::MonsterArt]->SetMonster(m_Monster);
	m_vecObject[(int)EBattleObjectType::MonsterHPBar] = std::make_unique<MonsterHPBar>(this);
	m_vecObject[(int)EBattleObjectType::MonsterHPBar]->SetMonster(m_Monster);
	m_vecObject[(int)EBattleObjectType::MonsterHPBar]->SetCursorPos(CursorPos(0, (SHORT)m_vecObject[(uint32)EBattleObjectType::MonsterArt]->GetCursorY()));
}
void BattleScene::Update(float DeltaTime)
{
	if (m_bChangeFlag)
		m_Time += DeltaTime;

	if (m_Time >= m_TimeMax)
	{
		ConsoleRender::GetInst()->CreateScene<FieldScene>();
		return;
	}

	size_t size = m_vecObject.size();
	m_Player->GetInst()->Update(DeltaTime);
	for (const auto& iter : m_vecObject)
	{
		iter->Update(DeltaTime);
	}
}
void BattleScene::Render(float DeltaTime)
{
	size_t size = m_vecObject.size();
	m_Player->GetInst()->Render(DeltaTime);
	for (const auto& iter : m_vecObject)
	{
		iter->Render(DeltaTime);
	}
}

void BattleScene::SetMonster(Monster* Monster)
{
	m_Monster = Monster;
}


void BattleScene::Fight()
{
	BattleMessage* Message = (BattleMessage*)m_vecObject[(int)EBattleObjectType::Message].get();
	
	std::string MonsterName = m_Monster->getName();
	std::string PlayerName = m_Player->getName();

	Message->m_vecText.push_back(PlayerName + "가 공격합니다.");
	std::string str = MonsterName + "가 " + std::to_string(Player::GetInst()->getAtk()) + "의 피해를 입습니다.";
	Message->m_vecText.push_back(str);
	m_Monster->takeDamage(Player::GetInst()->getAtk());
	if (m_Monster->isDead())
	{
		Message->m_vecText.push_back("몬스터가 죽었습니다.");
		m_bChangeFlag = true;
		return;
	}
	Message->m_vecText.push_back(MonsterName + "가 공격합니다.");
	str = PlayerName + "가 " + std::to_string(m_Monster->getAttackPower()) + "의 피해를 입습니다.";
	Message->m_vecText.push_back(str);
	Player::GetInst()->takeDamage(m_Monster->getAttackPower());
	Message->m_Timer = true;
	if (m_Player->getCurrHealth() <= 0)
	{
		Message->m_vecText.push_back("플레이어가 죽었습니다.");
		Player::GetInst()->Destroy();
	}
}

void BattleScene::useItem()
{
	Player::GetInst()->useItem(m_ItemName);
}

void BattleScene::runAway()
{
	ConsoleRender::GetInst()->CreateScene<FieldScene>();
}
