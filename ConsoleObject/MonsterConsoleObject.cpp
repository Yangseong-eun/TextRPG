#include "pch.h"
#include "MonsterConsoleObject.h"

MonsterConsoleObject::MonsterConsoleObject(ConsoleRender* Render, Monster* monster)
    : ConsoleObject(Render), m_Monster(monster) {
}

MonsterConsoleObject::~MonsterConsoleObject() {
}

void MonsterConsoleObject::update(HANDLE hConsole) 
{
    if (m_Monster->getHealth() > 0) {
        m_Monster->takeDamage(10);
    }
}

void MonsterConsoleObject::render(HANDLE hConsole) {
    static int renderIndex = 0; 
    SetConsoleTextAttribute(hConsole, m_TextColor | m_BackGroundColor);

    COORD pos = { 10, 5 * renderIndex++ }; 
    SetConsoleCursorPosition(hConsole, pos);

    std::cout << m_Monster->getName() << " ?�장!" << std::endl;
    std::cout << "체력: " << m_Monster->getHealth() << std::endl;
    std::cout << "공격?? " << m_Monster->getAttackPower() << std::endl;
}
