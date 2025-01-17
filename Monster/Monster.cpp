#include "pch.h"
#include "Player.h"
#include "Monster.h"
#include <cstdlib>
#include <ctime>
#include "Orc.h"
#include "Goblin.h"
#include "Troll.h"
#include "Slime.h"

Monster::Monster(const std::string& name, int playerLevel, MonsterType monsterType)
    : name(name), currhealth(0), maxHealth(0), attackPower(0), type(monsterType)
{
    updateStats(playerLevel);
}

void Monster::updateStats(int playerLevel)
{
    currhealth = playerLevel * 40; // 기존 최소 체력
    maxHealth = playerLevel * 60; // 기존 최대 체력

    // 최소 체력을 플레이어 공격력(예: 30)보다 높게 설정
    if (currhealth < 50) {
        maxHealth = 50; // 최소 체력을 보장
    }

    // 랜덤 체력 설정
    maxHealth = getRandomValue(currhealth, maxHealth);
    currhealth = maxHealth; // 현재 체력은 최대 체력으로 초기화

    // 랜덤 공격력 설정
    attackPower = getRandomValue(playerLevel * 5, playerLevel * 10);
}

void Monster::takeDamage(int damage)
{
    currhealth -= damage;
    if (currhealth <= 0)
    {
        currhealth = 0;
        onDeath(); // 몬스터가 죽었을 때 처리 호출
    }
}

void Monster::onDeath()
{
    std::cout << name << " has been defeated!" << std::endl;

    // 보상 지급
    auto [gold, experience] = dropItem();
    Player* player = Player::GetInst();
    player->addGold(gold);
    player->addExp(experience);
    bDead = true;
    std::cout << "You received " << gold << " gold and " << experience << " experience points!" << std::endl;
}

int Monster::getRandomValue(int min, int max) const
{
    static bool seedSet = false;
    if (!seedSet)
    {
        srand(static_cast<unsigned>(time(0)));
        seedSet = true;
    }
    return min + (rand() % (max - min + 1));
}

void Monster::attack(Player& player)
{
    std::cout << name << " attacks " << player.getName() << " for " << attackPower << " damage!" << std::endl;
    player.takeDamage(attackPower);
}

std::pair<int, int> Monster::dropItem() const
{
    int gold = getRandomValue(10, 30);
    int experience = getRandomValue(20, 60);
    return { gold, experience };
}

Monster* GenerateRandomMonster(int playerLevel)
{
    srand(static_cast<unsigned>(time(0))); // 난수 시드 설정

    int randomValue = rand() % 4; // 0 ~ 3 랜덤 값 생성
    Monster* monster = nullptr;

    switch (randomValue) {
    case 0: {
        monster = new Orc(playerLevel); // Orc 생성
        break;
    }
    case 1: {
        monster = new Goblin(playerLevel); // Goblin 생성
        break;
    }
    case 2: {
        monster = new Troll(playerLevel); // Troll 생성
        break;
    }
    case 3: {
        monster = new Slime(playerLevel); // Slime 생성
        break;
    }
    default: {
        monster = nullptr; // 예외 처리
        break;
    }
    }

    // 디버그 출력 (몬스터 이름 확인)
    if (monster != nullptr) {
        std::cout << "Generated Monster: " << monster->getName() << std::endl;
    }
    else {
        std::cout << "Failed to generate a monster!" << std::endl;
    }

    return monster;
}
