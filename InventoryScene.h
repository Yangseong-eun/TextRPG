
#pragma once
#include "Scene.h"
#include "../Player/Player.h"

class InventoryScene : public Scene {
public:
    InventoryScene();
    virtual ~InventoryScene();

    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;

private:
    Player* m_Player;
};
