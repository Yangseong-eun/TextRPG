#include "pch.h"
#include "PlayerProfile.h"

PlayerProfile::PlayerProfile()
{
	m_CursorPos = { 90, 0 };
	m_TextColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetImage(m_vecText,"Profile");
}

void PlayerProfile::Update(float DeltaTime)
{
	ConsoleObject::Update(DeltaTime);
}

void PlayerProfile::Render(float DeltaTime)
{
	ConsoleObject::Render(DeltaTime);
}
