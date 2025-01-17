#pragma once
#include "ConsoleObject.h"
class PrintMap :
    public ConsoleObject
{
public:
    PrintMap(class Scene* Owner);
    virtual void Update(float DeltaTime) override;
    virtual void Render(float DeltaTime) override;
private:
    CursorPos m_PlayerPos;
    std::vector<std::wstring> m_vecMap;
    std::vector<std::wstring> m_vecWallMap;
    float m_eventTime = 5.f;
public:
    void SetPlayerPos(const CursorPos& pos) { m_PlayerPos = pos; }
};

