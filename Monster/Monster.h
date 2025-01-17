#pragma once

#include <string>
#include <utility> // for std::pair

class Player; // 전방 선언

class Monster {
protected:
    std::string name;       // 몬스터 이름
    int currhealth;             // 현재 체력
    int maxHealth;          // 최대 체력 (생성 시의 초기 체력)
    int attackPower;        // 공격력
    MonsterType type;       // 몬스터 타입
    bool bDead = false;
public:

    Monster(const std::string& name, int playerLevel, MonsterType monsterType);
    virtual ~Monster() = default;

    virtual void updateStats(int playerLevel);
    void takeDamage(int damage);
    void onDeath();
    void attack(Player& player);
    virtual std::pair<int, int> dropItem() const;

    std::string getName() const { return name; }
    int getHealth() const { return currhealth; }
    int getMaxHealth() const { return maxHealth; } // 최대 체력 반환
    int getAttackPower() const { return attackPower; }
    MonsterType getType() const { return type; }
    bool isDead() const { return bDead; }
protected:
    int getRandomValue(int min, int max) const;
};

// 랜덤 몬스터 생성 함수 선언
Monster* GenerateRandomMonster(int playerLevel);
