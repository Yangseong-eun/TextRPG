#include "pch.h"
#include "BattleMenuObject.h"
#include "ConsoleRender.h"
#include "KeyMgr.h"
#include "BattleScene.h"

BattleMenuObject::BattleMenuObject(class Scene* Scene) :
	ConsoleObject(Scene)
{
	m_Render = ConsoleRender::GetInst();
	m_SelectMenu = 1;

	m_vecText.push_back("** 1. 싸운다.");
	m_vecText.push_back("** 2. 아이템사용.");
	m_vecText.push_back("** 3. 도망간다.");

	m_CursorPos = { 98, 30 };
	m_maxTime = 1.f;
}
void BattleMenuObject::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);

	if (IS_TAB(KEY::W))
	{
		m_SelectMenu = m_SelectMenu > 1 ? m_SelectMenu -1 : m_SelectMenu;
	}
	else if (IS_TAB(KEY::S))
	{
		size_t size = (int)m_vecText.size();
		m_SelectMenu = m_SelectMenu < size ? m_SelectMenu +1 : size;
	}
	if (IS_TAB(KEY::SPACE))
	{
		BattleScene* Scene = dynamic_cast<BattleScene*>(m_Owner);

		switch ((EBattleMenu)m_SelectMenu)
		{
		case EBattleMenu::None:
			break;
		case EBattleMenu::Fight:
			Scene->Fight();
			break;
		case EBattleMenu::UseItem:
			Scene->useItem();
			break;
		case EBattleMenu::Run:
			Scene->runAway();
			break;
		default:
			break;
		}
	}
}

void BattleMenuObject::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
	m_Render->SetTextColorAndBackGroundColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, m_BackGroundColor);
	SetConsoleCursorPosition(m_hConsole, CursorPos(m_CursorPos.X-1,m_CursorPos.Y + m_SelectMenu -1));
	WriteFile(m_hConsole, ">", (DWORD)1, nullptr, NULL);
	m_Render->SetTextColorAndBackGroundColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
