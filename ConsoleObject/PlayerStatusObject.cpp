#include "pch.h"
#include "PlayerStatusObject.h"
#include "ConsoleObject.h"
#include "../Player/Player.h"
#include "ConsoleRender.h"
PlayerStatusObject::PlayerStatusObject()
{
	m_CursorPos = {115, 1};
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
}

void PlayerStatusObject::Update(float DeltaTime)
{
	m_vecText.clear();
	m_vecText.push_back(" ");
	m_vecText.push_back(" ");
	m_vecText.push_back("이름   : " + Player::GetInst()->getName());
	m_vecText.push_back(" ");
	m_vecText.push_back("레벨   : " + std::to_string(Player::GetInst()->getLevel()));
	m_vecText.push_back(" ");
	m_vecText.push_back("체력   : " + std::to_string(Player::GetInst()->getCurrHealth()) + "/" + std::to_string(Player::GetInst()->getMaxHealth()));
	m_vecText.push_back(" ");
	m_vecText.push_back("소지금 : " + std::to_string(Player::GetInst()->getGold()));
	ConsoleObject::Update(DeltaTime);
}

void PlayerStatusObject::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
}
