#include "pch.h"
#include "MonsterHPBar.h"
#include "BattleScene.h"
#include "Monster.h"
MonsterHPBar::MonsterHPBar(Scene* _Scene) :
	ConsoleObject(_Scene)
{
	SetImage(m_vecText, "HPBar");
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	// 남은 #개수
	m_BarCount = 50;
}

void MonsterHPBar::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
	//퍼센테이지 곱
	m_Frac = ((float)m_Monster->getHealth() / (float)m_Monster->getMaxHealth());
	// TODO : 몬스터 체력 가지고 와서 계산하기.	2번라인과 4번라인에 ## 박혀있음 이거 바꾸면된다.
	m_progress = (uint32)(m_Frac * 60);
	size_t size = m_vecText[2].size();

	for (size_t i = size-1; i > 0 && m_progress  < m_BarCount; --i)
	{
		if (m_vecText[2][i] == '#')
		{
			m_vecText[2][i] = ':';
			m_vecText[4][i] = ':';
			--m_BarCount;
		}
	}
}

void MonsterHPBar::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
}

void MonsterHPBar::SetCursorPosY(const int& y)
{
	m_CursorPos.Y = (SHORT)y;
}
