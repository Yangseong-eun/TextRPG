#pragma once
#include "Scene.h"
class MainScene :
    public Scene
{
public:
    virtual ~MainScene() override;
public:
    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    std::vector<std::string> m_vecText;
    uint32 m_SelectMenu;
};

