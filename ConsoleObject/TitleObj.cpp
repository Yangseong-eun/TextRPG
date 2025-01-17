#include "pch.h"
#include "TitleObj.h"

#include "KeyMgr.h"
#include "ConsoleRender.h"
#include "MainScene.h"
TitleObj::TitleObj(Scene* Scene) : 
	ConsoleObject(Scene)
{
	SetImage(m_vecText, "Title");
	
	m_Right = (150 / 2) - (getWidth() / 2);
	m_Top = (short)(getHeight() * (3.f / 5.f));
	m_CursorPos = { m_Right , m_Top };
	m_CursorPos = { 20 , 10 };
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	m_Reverse = false;
}

void TitleObj::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);

	m_Time += DeltaTime;
	if (m_Time >= 1.f)
	{
		if (m_Top + 3 < m_CursorPos.Y)
			m_Reverse = true;
		else if (3 >= m_CursorPos.Y)
			m_Reverse = false;

		if (!m_Reverse)
		{
			m_CursorPos.Y += (short)m_Time;
			m_Time = 0.f;
		}

		if (m_Reverse)
		{
			m_CursorPos.Y -= (short)m_Time;
			m_Time = 0.f;
		}
	}

	
	if (IS_TAB(KEY::SPACE))
	{
		ConsoleRender::GetInst()->CreateScene(std::make_unique<MainScene>());
	}
}

void TitleObj::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
}
