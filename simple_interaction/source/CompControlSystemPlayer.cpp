/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemPlayer.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemPlayer);

void CompControlSystemPlayer::init()
{
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);
	ptrCompWeaponSystem = ComponentSystem::get()->getComponent<CompWeaponSystem>(ptrTurret);
}

void CompControlSystemPlayer::update()
{
	t0_5 = t0_5 - Game::getIFps();
	if (t0_5 <= 0.0)
	{
		t0_5 = 0.5;

		t1 = t1 - t0_5;

		if (t1 <= 0.0)
		{
			t1 = 1.0;
			ptrCompNavigationSystem->getClotherTarget();
		}

		if (ptrCompNavigationSystem->ptrTarget.get() != nullptr)
		{
			ptrCompMoveSystem->setpoint = ptrCompNavigationSystem->ptrTarget->getWorldPosition();
			ptrCompMoveSystem->tolerance = ptrCompWeaponSystem->range - 1.0;
			ptrCompWeaponSystem->ptrTarget = ptrCompNavigationSystem->ptrTarget;
		}
	}
}

void CompControlSystemPlayer::shutdown()
{
}
