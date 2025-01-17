#pragma once
#include "ConsoleObject.h"
class PlayerProfile :
    public ConsoleObject
{
public:
    PlayerProfile();
public:
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
};

