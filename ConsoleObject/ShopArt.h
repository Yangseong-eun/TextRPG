#pragma once
#include "ConsoleObject.h"
class ShopArt :
    public ConsoleObject
{
public:
    ShopArt(class Scene* Scene);
    virtual ~ShopArt() override;
public:
    virtual void init() override;
public:
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    std::vector<std::string> m_vecArtText;
};

