#pragma once
#include "ConsoleObject.h"
class TitleObj :
    public ConsoleObject
{
public:
    TitleObj(class Scene* Scene);
public:
    virtual void Update(float DeltaTime);
    virtual void Render(float DeltaTime);
private:
    short m_Right;
    short m_Top;
};

