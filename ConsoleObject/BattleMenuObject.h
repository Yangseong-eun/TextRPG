#pragma once
#include "ConsoleObject.h"
class BattleMenuObject :
    public ConsoleObject
{
public:
    BattleMenuObject(class Scene* Scene);
public:
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    float m_currTime;
    float m_maxTime;
};

