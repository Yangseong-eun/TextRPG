#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
public:
    TitleScene();
    virtual ~TitleScene() override;
public:
    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
};

