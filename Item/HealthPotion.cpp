#include "pch.h"
#include "HealthPotion.h"
#include "Player.h"
void HealthPotion::use(Player* player)
{
	player->addHealth(m_healthRestore);
}
