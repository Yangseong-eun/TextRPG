#include "pch.h"
#include "ShopArt.h"
#include "ConsoleRender.h"
ShopArt::ShopArt(Scene* Scene)
{
	m_CursorPos = { 0, };
	SetImage(m_vecText, "Store");
	init();
	m_vecArtText.push_back("============================");
	m_vecArtText.push_back("    ─███─█──█─████─████─     ");
	m_vecArtText.push_back("    ─█───█──█─█──█─█──█─     ");
	m_vecArtText.push_back("    ─█───█──█─█──█─█──█─     ");
	m_vecArtText.push_back("    ─███─████─█──█─████─     ");
	m_vecArtText.push_back("    ───█─█──█─█──█─█────     ");
	m_vecArtText.push_back("    ─███─█──█─████─█────     ");
	m_vecArtText.push_back("============================");
}

ShopArt::~ShopArt()
{
}

void ShopArt::init()
{
	m_TextColor = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
}

void ShopArt::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
}

void ShopArt::Render(float DeltaTime)
{
	DWORD dw;
	int count = 0;
	
	m_Render->SetTextColorAndBackGroundColor(m_TextColor, m_BackGroundColor);
	for (const auto& iter : m_vecText)
	{
		COORD pos = { m_CursorPos.X, m_CursorPos.Y + count +2};
		SetConsoleCursorPosition(m_hConsole, pos);
		std::wstring str = toUnicode(iter);
		WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &dw, NULL);
		++count;
	}
	count = 0;
	for (const auto& iter : m_vecArtText)
	{
		COORD pos = { m_CursorPos.X+10, m_CursorPos.Y + count +1};
		SetConsoleCursorPosition(m_hConsole, pos);
		std::wstring str = toUnicode(iter);
		WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &dw, NULL);
		++count;
	}
}
