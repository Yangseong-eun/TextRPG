#pragma once
#include "ConsoleObject.h"
class MonsterHPBar :
    public ConsoleObject
{
public:
    MonsterHPBar(class Scene* Scene);
public:
    virtual void Update(float DeltaTime);
    virtual void Render(float DeltaTime);
public:
    void SetCursorPosY(const int& y);
    float m_Frac;
    uint32 m_progress;
    uint32 m_BarCount;
};

