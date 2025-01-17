#pragma once
#include "ConsoleObject.h"
#include "Monster.h" // Monster ?�래???�함

class MonsterConsoleObject : public ConsoleObject {
public:
    MonsterConsoleObject(ConsoleRender* Render, Monster* monster);
    virtual ~MonsterConsoleObject();

    virtual void update(HANDLE hConsole);
    virtual void render(HANDLE hConsole);

private:
    Monster* m_Monster; // ?�결??몬스??객체
};
