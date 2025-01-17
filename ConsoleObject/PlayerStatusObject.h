#pragma once
#include "ConsoleObject.h"
class PlayerStatusObject :
    public ConsoleObject
{
public:
    PlayerStatusObject();
public:
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
};

