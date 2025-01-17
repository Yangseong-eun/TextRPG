#include "pch.h"
#include "MonsterArtObject.h"
#include "ConsoleRender.h"
#include "Logger.h"
#include "BattleScene.h"
#include "Monster.h"
MonsterArtObject::MonsterArtObject(class Scene* Scene) :
	ConsoleObject(Scene)
{
	m_Render = ConsoleRender::GetInst();
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	
}

void MonsterArtObject::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
}

void MonsterArtObject::Render(float DeltaTime)
{
	m_Render->SetTextColorAndBackGroundColor(m_TextColor, m_BackGroundColor);
	size_t size = m_vecMonsterName.size();
	DWORD written;
	for (size_t i = 0; i < size; ++i)
	{
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + (SHORT)i));
		std::wstring str = toUnicode(m_vecMonsterName[i]).c_str();
		WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL);
	}
	for (size_t i = 0; i < m_vecText.size(); ++i)
	{
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + size + (SHORT)i));
		std::wstring str = toUnicode(m_vecText[i]).c_str();
		WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL);
	}
	m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//ConsoleObject::Render(DeltaTime);
}

void MonsterArtObject::SetMonster(Monster* _Monster)
{
	m_Monster = _Monster;

	SetImage(m_Monster->getType());
	SetImage(m_vecMonsterName, m_Monster->getName()+"Text");
}
