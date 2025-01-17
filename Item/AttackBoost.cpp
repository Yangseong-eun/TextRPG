#include "pch.h"
#include "AttackBoost.h"
#include "Player.h"
void AttackBoost::use(Player* player)
{
	player->addAtk(m_attackIncrease);
}
