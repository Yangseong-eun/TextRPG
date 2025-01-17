#include "pch.h"
#include "TitleText.h"
#include "ConsoleRender.h"
#include "MainScene.h"
TitleText::TitleText(Scene* Scene) :
	ConsoleObject(Scene)
{
	m_vecText.push_back("미래의 어느 날, 코딩 세계는 \"시간 균열\"이라는 미스터리한 현상으로 붕괴되고 있습니다.");
	m_vecText.push_back("과거에서 탄생한 3가지 중요한 기술(C++, 언리얼, 블루프린트)이 사라지면서, 현실과 가상이 뒤섞이는 카오스 상태가 발생했습니다.");
	m_vecText.push_back("플레이어는 시간 여행 능력을 부여받고, 과거로 돌아가 각 기술의 탄생 순간에서 시간의 조각을 찾아야 합니다.");
	m_vecText.push_back("    ");
	m_vecText.push_back("시간의 균열로 C++코드가 파괴되어 객체지향이라는 개념이 망가졌습니다.");
	m_vecText.push_back("플레이어가 되어 버그를 제거하고 객체의 조각을 모아 객체지향을 복원해야합니다.");
	float ScreenWidth = (float)150 / 2.f;
	float Width = (float)getWidth() / 2.f;

	float CenterWidth = ScreenWidth - Width;
	m_CursorPos = { 5, 20 };

	m_LineCount = 0;
	m_TextWidth = 0;
}

void TitleText::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
	m_Time += DeltaTime;
}

void TitleText::Render(float DeltaTime)
{
	if (m_vecText.empty())
		return;
	m_hConsole = m_Render->getHandle();
	size_t size = m_vecText.size();
	m_Height = (uint32)size;

	m_Render->SetTextColorAndBackGroundColor(m_TextColor, m_BackGroundColor);
	DWORD written;

	// 0.1초마다 한줄씩 출력하려면
	// 0.1초마다 Text의 길이를 늘려야한다.
	for (size_t i = 0; i < m_LineCount; ++i)
	{
		SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + (SHORT)i));
		std::wstring str = toUnicode(m_vecText[i].c_str()).c_str();
		WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL);
	}
	SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X, m_CursorPos.Y + (SHORT)m_LineCount));
	if (m_Time >= 0.01f)
	{
		m_LineText = m_LineText + m_vecText[m_LineCount].at(m_TextWidth);
		m_TextWidth++;
		if (m_TextWidth == m_vecText[m_LineCount].size())
		{
			m_TextWidth = 0;
			m_LineCount++;
			m_LineText.clear();
		}
		m_Time = 0.f;
	}
	if (m_LineCount == m_vecText.size())
	{
		m_LineCount = 0;
		m_LineText.clear();
		ConsoleRender::GetInst()->CreateScene(std::make_unique<MainScene>());
	}
	std::wstring str = toUnicode(m_LineText.c_str()).c_str();
	WriteConsoleW(m_hConsole, str.c_str(), (DWORD)str.size(), &written, NULL);

	m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
