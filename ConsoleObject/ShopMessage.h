#pragma once
#include "ConsoleObject.h"
class ShopMessage :
    public ConsoleObject
{
    friend class Shop;
public:
    ShopMessage();
public:
    virtual void Update(float DeltaTime);
    virtual void Render(float DeltaTime);
private:
    float m_maxTime = 1.f;
    std::list<std::string> m_listText;

};

