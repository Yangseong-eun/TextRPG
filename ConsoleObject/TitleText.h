#pragma once
#include "ConsoleObject.h"
class TitleText :
    public ConsoleObject
{
public:
    TitleText(class Scene* Scene);
public:
    virtual void Update(float DeltaTime);
    virtual void Render(float DeltaTime);
private:
    int m_LineCount;
    int m_TextWidth;
    std::string m_LineText;
};

