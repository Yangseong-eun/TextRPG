#pragma once

#include "./Scene/Scene.h"
#include "Monster.h"
#include "../Player/Player.h"
#include "ConsoleRender.h"

class MonsterScene : public Scene {
public:
    MonsterScene(Player* player, Monster* monster);
    virtual ~MonsterScene();

    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;

private:
    Player* m_Player;     
    Monster* m_Monster;  
    bool m_IsBattleEnd;   
};
