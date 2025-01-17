#include "pch.h"
#include "Slime.h"

Slime::Slime(int playerLevel)
    : Monster("Slime", playerLevel, MonsterType::Slime) // 이름 및 타입 수정
{
}
