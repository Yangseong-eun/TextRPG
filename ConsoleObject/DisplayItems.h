#pragma once
#include "ConsoleObject.h"
class DisplayItems :
    public ConsoleObject
{
public:
    DisplayItems(class Scene* Scene);
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    std::vector<std::shared_ptr<Item>> m_vecItem;
    bool                               m_bSelect;
    class ShopScene* m_Shop;
    std::vector<std::string> m_SelectString;
    std::vector<std::string> m_vecPrice;
    int m_SelectShop;
};

