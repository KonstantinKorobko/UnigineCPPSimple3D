/*
* @author  Konstantin Korobko
*/
#include "CompDamageSystem.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompDamageSystem);

void CompDamageSystem::init()
{
}

void CompDamageSystem::update()
{
	t0_2 = t0_2 - Game::getIFps();
	if (t0_2 <= 0.0)
	{
		t0_2 = 0.2;

		armor = armor - damageAdd;
		damageAdd = 0.0;
	}	
}

void CompDamageSystem::shutdown()
{
}
