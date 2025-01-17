#include "pch.h"
#include "BattleMessage.h"

BattleMessage::BattleMessage(Scene* Scene) :
	ConsoleObject(Scene)
{
	m_Timer = false;
	m_maxTime = 1.f;
	m_CursorPos = { 90, 15};
}

void BattleMessage::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
	if(m_Timer)
		m_currTime += DeltaTime;
	if (m_maxTime <= m_currTime)
	{
		m_vecText.clear();
		m_currTime = 0.f;
		m_Timer = false;
	}
}

void BattleMessage::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
}
