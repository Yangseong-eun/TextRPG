#include "pch.h"
#include "BossMonster.h"
#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

// ?앹꽦??
BossMonster::BossMonster(const std::string& name, int playerLevel, MonsterType monsterType)
    : Monster("Dragon", playerLevel, MonsterType::Dragon)
{
    updateStats(playerLevel); // 蹂댁뒪 紐ъ뒪???λ젰移??낅뜲?댄듃
    srand(static_cast<unsigned>(time(0))); // ?쒕뜡 ?쒕뱶 珥덇린??
}

// 泥대젰/怨듦꺽??1.5諛??ㅼ젙
void BossMonster::updateStats(int playerLevel)
{
    Monster::updateStats(playerLevel);
    currhealth = static_cast<int>(currhealth * 3);
    attackPower = static_cast<int>(attackPower * 3);
}

// ?뚮젅?댁뼱 怨듦꺽
void BossMonster::attack(Player& player)
{
    std::cout << "Boss attacks " << player.getName() << " for " << attackPower << " damage!" << std::endl;

    // ?뚮젅?댁뼱?먭쾶 湲곕낯 ?곕?吏 ?곸슜
    uint32 currHealth = player.getCurrHealth();
    currHealth = (currHealth > (uint32)attackPower) ? currHealth - attackPower : 0;
    std::cout << player.getName() << " takes " << attackPower << " damage! Remaining health: " << currHealth << std::endl;

    // 50% ?뺣쪧濡??뱀닔 怨듦꺽 ?ㅽ뻾
    if (rand() % 2 == 0) // 50% ?뺣쪧
    {
        specialAttack(player);
    }
}

// ?뱀닔 怨듦꺽
void BossMonster::specialAttack(Player& player)
{
    int special = rand() % 2; // 0 ?먮뒗 1 以??섎굹 ?좏깮
    if (special == 0)
    {
        // ?곗냽 怨듦꺽: 怨듦꺽??2諛곕줈 異붽? 怨듦꺽
        std::cout << "Boss performs a special double attack!" << std::endl;

        uint32 currHealth = player.getCurrHealth();
        currHealth = (currHealth > static_cast<uint32>(attackPower * 2)) ? static_cast<uint32>(currHealth - attackPower * 2) : 0;
        std::cout << player.getName() << " takes " << attackPower * 2 << " damage! Remaining health: " << currHealth << std::endl;
    }
    else if (special == 1)
    {
        // ?뚮젅?댁뼱 怨듦꺽 諛섏궗: ?뚮젅?댁뼱媛 諛쏆? ?곕?吏???쇰?瑜?諛섏궗
        int reflectedDamage = attackPower / 2;
        std::cout << "Boss reflects " << reflectedDamage << " damage back to Player!" << std::endl;

        uint32 currHealth = player.getCurrHealth();
        currHealth = (currHealth > reflectedDamage) ? currHealth - reflectedDamage : 0;
        std::cout << player.getName() << " takes " << reflectedDamage << " damage! Remaining health: " << currHealth << std::endl;
    }
}

// 泥섏튂 ?щ? ?뺤씤
void BossMonster::IfDie()
{
    if (getHealth() <= 0)
    {
        std::cout << "異뺥븯?⑸땲?? 寃뚯엫 ?붾뵫??蹂댁뀲?듬땲??" << std::endl;
    }
}
