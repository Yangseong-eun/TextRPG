#pragma once
#include "Scene.h"
#include "Shop.h"
class ShopScene :
    public Scene
{
public:
    ShopScene();
    virtual ~ShopScene() override;
public:
    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    std::unique_ptr<class Shop> m_Shop;
public:
    void buyItem(const std::string& ItemName);
    void sellItem(const std::string& ItemName);
    std::vector<std::shared_ptr<Item>> GetItems() const;
    const short getShopWidth(int ObjectIndex);
    const short getShopHeight(int ObjectIndex);
};

