#pragma once
#include <string>

class Enemy {
public:
    Enemy(int level);
    void TakeDamage(int damage);
    int Attack();
    bool IsDead() const;
    void PrintStatus() const;
    int GetGoldReward() const;
    int GetExpReward() const;
    std::string GetName() const; // ???대쫫 諛섑솚

private:
    std::string name;
    int level;
    int health;
    int attackPower;
    int goldReward;
    int expReward;

    static std::string GenerateRandomName();
    int GetRandomValue(int min, int max) const;
    void PrintHPBar() const;
};
