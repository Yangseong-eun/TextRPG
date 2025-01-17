#include <pch.h>
#include "BattleManager.h"
#include "Macro.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "ConsoleRender.h"
#include "TimeManager.h"
#include "MainScene.h"
BattleManager::BattleManager() : 
    m_Player(nullptr),
    m_Monster(nullptr),
    m_Render(nullptr),
    m_RenderObj(nullptr),
    m_battleEnd(false)
{
    m_Player = Player::GetInst();
}

BattleManager::BattleManager(ConsoleRender* Render) :
    m_Player(nullptr),
    m_Monster(nullptr),
    m_Render(nullptr),
    m_RenderObj(nullptr),
    m_battleEnd(false)
{
    m_Render = Render;
}

BattleManager::~BattleManager()
{
}

bool BattleManager::init()
{
    return true;
}
bool BattleManager::init(ConsoleRender* Render)
{
    if (init() == false)
        return false;

    m_Render = Render;
    return true;
}

void BattleManager::Update(float DeltaTime)
{
    ConsoleRender::GetInst()->Update(DeltaTime);
}

void BattleManager::Render(float DeltaTime)
{
    ConsoleRender::GetInst()->Render(DeltaTime);
}

void BattleManager::battle(Monster* Monter)
{
    Monter->updateStats(m_Player->m_level);
    auto ptr = std::make_unique<BattleScene>(Monter);
    ptr->SetMonster(Monter);
    ConsoleRender::GetInst()->CreateScene(std::move(ptr));
}

void BattleManager::battle(std::unique_ptr<class Monster> Monster)
{
    m_Monster = std::move(Monster);
    battle(m_Monster.get());
}
