#include "pch.h"
#include "PrintMap.h"
#include "ConsoleObject.h"
#include "KeyMgr.h"
#include "ConsoleRender.h"
#include "MainScene.h"
#include "FieldScene.h"
#include "Player.h"
PrintMap::PrintMap(Scene* Owner) :
	ConsoleObject(Owner)
{
	SetImage(m_vecMap, "Map");
	size_t size = m_vecMap.size();

	for (size_t i = 0; i < size; ++i)
	{
		std::wstring w;
		for (size_t j = 0; j < m_vecMap[i].size(); ++j)
		{
			if (m_vecMap[i][j] != TEXT('⠀'))
				w += m_vecMap[i][j];
			else
				w += TEXT('0');
		}
		m_vecWallMap.push_back(w);
	}
	m_Width = getWidth();
	m_Height = getHeight();
	m_PlayerPos = { 43,58};
	//m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X] = L'&';
}

void PrintMap::Update(float DeltaTime)
{
	
	ConsoleObject::Update(DeltaTime);
	m_Time += DeltaTime;

	if (m_Time >= m_eventTime)
	{
		if(Player::GetInst()->getLevel() >= 10)
			dynamic_cast<FieldScene*>(m_Owner)->RandomCreateBossMonster();
		else
			dynamic_cast<FieldScene*>(m_Owner)->RandomCreateMonster();
	}
	if (IS_PRESSED(KEY::W))
	{
		bool move = false;
		move = m_vecWallMap[m_PlayerPos.Y - 1][m_PlayerPos.X] == L'0' ? true : false;

		if (move)
		{
			//std::swap(m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X], m_vecWallMap[m_PlayerPos.Y - 1][m_PlayerPos.X]);
			m_PlayerPos.Y--;
		}
	}
	if (IS_PRESSED(KEY::S))
	{
		bool move = false;
		move = m_vecWallMap[m_PlayerPos.Y + 1][m_PlayerPos.X] == L'0' ? true : false;

		if (move)
		{
			//std::swap(m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X], m_vecWallMap[m_PlayerPos.Y+1][m_PlayerPos.X]);
			m_PlayerPos.Y++;
		}
	}
	if (IS_PRESSED(KEY::A))
	{
		bool move = false;
		move = m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X-1] == L'0' ? true : false;

		if (move)
		{
			//std::swap(m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X], m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X-1]);
			m_PlayerPos.X--;
		}
	}
	if (IS_PRESSED(KEY::D))
	{
		bool move = false;
		move = m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X+1] == L'0' ? true : false;

		if (move)
		{
			//std::swap(m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X], m_vecWallMap[m_PlayerPos.Y][m_PlayerPos.X+1]);
			m_PlayerPos.X++;
		}
	}
	if (IS_TAB(KEY::ESC))
	{
		ConsoleRender::GetInst()->CreateScene<MainScene>();
	}
	Player::GetInst()->SetFieldPos(m_PlayerPos);
}

void PrintMap::Render(float DeltaTime)
{
	int count = 0;
	DWORD dw = NULL;
	SetConsoleTextAttribute(m_hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	for (short col=0; col < m_vecWallMap.size();++col)
	{
		short row = 0;
		for (wchar_t *p = &m_vecWallMap[col][0]; *p != L'\0'; ++p)
		{
			COORD pos = { m_CursorPos.X + row, m_CursorPos.Y + col };
			SetConsoleCursorPosition(m_hConsole, pos);
			if(*p == L'0')
				WriteConsoleW(m_hConsole, L" ", 1, &dw, nullptr);
			else if (*p == L'&')
			{
				SetConsoleTextAttribute(m_hConsole, FOREGROUND_GREEN| FOREGROUND_INTENSITY);
				WriteConsoleW(m_hConsole, p, 1, &dw, nullptr);
				SetConsoleTextAttribute(m_hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
			else
				WriteConsoleW(m_hConsole, p, 1, &dw, nullptr);
			++row;
		}
	}
	SetConsoleCursorPosition(m_hConsole, m_PlayerPos);
	SetConsoleTextAttribute(m_hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	WriteConsoleW(m_hConsole, L"&", 1, &dw, nullptr);
	SetConsoleTextAttribute(m_hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
