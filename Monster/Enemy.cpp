#include "pch.h"
#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

// Enemy ??밴쉐??
Enemy::Enemy(int level): name(GenerateRandomName()), level(level) {
    health = GetRandomValue(level * 20, level * 30); // 筌ｋ?????쇱젟
    attackPower = GetRandomValue(level * 5, level * 10); // ?⑤벀爰????쇱젟
    goldReward = GetRandomValue(10, 50); // ?ⓥ뫀諭?癰귣똻湲???뺣쑁 (10 ~ 50)
    expReward = GetRandomValue(20, 50); // 野껋?肉뺟㎉?癰귣똻湲???뺣쑁 (20 ~ 50)
}

// ??뺣쑁 ??已???밴쉐 ??λ땾
std::string Enemy::GenerateRandomName() {
    std::vector<std::string> monsterNames = { "Goblin", "Skeleton", "Orc", "Zombie" }; //??곗뺘筌???已?4揶?餓???롪돌嚥???뺣쑁??띿쓺 ?곗뮆???띿쓺 ??
    int randomIndex = rand() % monsterNames.size();
    return monsterNames[randomIndex];
}

// ??뺣쑁 揶???밴쉐 ??λ땾
int Enemy::GetRandomValue(int min, int max) const {
    return min + (rand() % (max - min + 1));
}

// ????已?獄쏆꼹??
std::string Enemy::GetName() const {
    return name;
}

// ?怨몄뵠 ??노퉸????낅뮉 ??λ땾
void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// ?怨몄뵠 ?⑤벀爰??롫뮉 ??λ땾
int Enemy::Attack() {
    return attackPower;
}

// ?怨몄뵠 ??彛??덈뮉筌왖 ?類ㅼ뵥
bool Enemy::IsDead() const {
    return health <= 0;
}

// ???怨밴묶 ?곗뮆????λ땾
void Enemy::PrintStatus() const {
    std::cout << "Enemy ~ " << name << "\n";
    PrintHPBar();
    std::cout << " (" << health << "/" << level * 30 << ")\n";
    std::cout << "Attack Power: " << attackPower << "\n";
}

// 筌ｋ??계쳸??곗뮆????λ땾
void Enemy::PrintHPBar() const {
    const int barWidth = 20;
    int filledWidth = (health * barWidth) / (level * 30);

    std::cout << "HP [";
    for (int i = 0; i < filledWidth; ++i) {   //筌ｋ??계쳸?
        std::cout << "??";
    }
    for (int i = filledWidth; i < barWidth; ++i) { //筌ｋ???筌?쑴?숋쭪?筌왖 ??? ?봔???⑤벉媛?筌ｌ꼶??
        std::cout << " ";
    }
    std::cout << "]";
}

// 癰귣똻湲?獄쏆꼹??
int Enemy::GetGoldReward() const {
    return goldReward;
}

int Enemy::GetExpReward() const {
    return expReward;
}
