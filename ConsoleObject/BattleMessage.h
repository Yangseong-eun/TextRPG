#pragma once
#include "ConsoleObject.h"
class BattleMessage :
    public ConsoleObject
{
    friend class BattleScene;
public:
    BattleMessage(class Scene* Scene);
public:
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    float m_currTime;
    float m_maxTime;
    bool m_Timer;
};

