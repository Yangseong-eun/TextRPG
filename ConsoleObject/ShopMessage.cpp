#include "pch.h"
#include "ShopMessage.h"
#include "ConsoleObject/ConsoleObject.h"
ShopMessage::ShopMessage()
{
	m_Time = 0.f;
	m_maxTime = 1.f;
	m_CursorPos = { 10, 35 };
}
void ShopMessage::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
	m_Time += DeltaTime;
	if (m_Time >= m_maxTime)
	{
		if(!m_listText.empty())
			m_listText.pop_front();
		m_Time = 0.f;
	}
}

void ShopMessage::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);

	int count = 0;
	for (const auto& iter : m_listText)
	{
		DWORD writeln;
		std::wstring wstr = toUnicode(iter);
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + count));
		WriteConsoleW(m_hConsole, wstr.c_str(), wstr.size(), &writeln, NULL);
		count++;
	}
}
