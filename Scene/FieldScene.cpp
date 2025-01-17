#include "pch.h"
#include "FieldScene.h"
#include "PrintMap.h"
#include "BattleManager.h"
#include "Player.h"
#include "Orc.h"
#include "Goblin.h"
#include "Troll.h"
#include "Slime.h"
#include "BossMonster.h"
#include "Player.h"
void FieldScene::Start()
{
	m_vecObject.push_back(std::make_unique<PrintMap>(this));
    CursorPos pos = Player::GetInst()->getFieldPos();

    if (pos.X != 0)
        SetFiledPos(pos);
}

void FieldScene::SetFiledPos(const CursorPos& pos)
{
    dynamic_cast<PrintMap*>(m_vecObject[0].get())->SetPlayerPos(pos);
}

void FieldScene::RandomCreateMonster()
{
    Player* player = Player::GetInst();

    RandomMaanger::GetInst()->setRange(0, (int)MonsterType::Max - 1);
    int Select = RandomMaanger::GetInst()->getRandom<int>();
    switch ((MonsterType)Select)
    {
    case MonsterType::None:
        break;
    case MonsterType::Goblin:
        BattleManager::GetInst()->battle(std::make_unique<Goblin>(player->getLevel()));
        break;
    case MonsterType::Orc:
        BattleManager::GetInst()->battle(std::make_unique<Orc>(player->getLevel()));
        break;
    case MonsterType::Troll:
        BattleManager::GetInst()->battle(std::make_unique<Troll>(player->getLevel()));
        break;
    case MonsterType::Slime:
        BattleManager::GetInst()->battle(std::make_unique<Slime>(player->getLevel()));
        break;
    case MonsterType::Dragon:
        //BattleManager::GetInst()->battle(std::make_unique<Dragon>(Player::GetInst()->getLevel()));
        break;
    case MonsterType::Max:
        break;
    default:
        break;
    }
}

void FieldScene::RandomCreateBossMonster()
{
    RandomMaanger::GetInst()->setRange(0, (int)MonsterType::Max);
    BattleManager::GetInst()->battle(std::make_unique<BossMonster>("킹왕짱 드래곤", Player::GetInst()->getLevel(),
        MonsterType::Dragon));
}
