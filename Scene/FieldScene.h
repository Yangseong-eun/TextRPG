#pragma once
#include "Scene.h"
class FieldScene :
    public Scene
{
    virtual void Start() override;
public:
    void SetFiledPos(const CursorPos& pos);
    void RandomCreateMonster();
    void RandomCreateBossMonster();
};

