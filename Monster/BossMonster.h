#pragma once
#include "Monster.h"
#include "Player.h" 

class BossMonster : public Monster
{
public:
    BossMonster(const std::string& name, int playerLevel, MonsterType monsterType);

    void updateStats(int playerLevel) override; // 泥대젰怨?怨듦꺽?μ쓣 1.5諛곕줈 ?ㅼ젙
    void attack(Player& player);               // ?뚮젅?댁뼱 怨듦꺽
    void IfDie();                              // 泥섏튂 ?щ? ?뺤씤 ??硫붿떆吏 異쒕젰

private:
    void specialAttack(Player& player);        // ?뱀닔 怨듦꺽
};
