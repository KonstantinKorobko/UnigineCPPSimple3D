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
	t15 = t15 - Game::getIFps();
	if (t15 <= 0.0)
	{
		t15 = 4.0;

		ptrCompNavigationSystem->getClotherTarget();
	}
	if (ptrCompNavigationSystem->ptrTarget.get() != nullptr)
	{
		ptrCompMoveSystem->setpoint = ptrCompNavigationSystem->ptrTarget->getWorldPosition();
		ptrCompMoveSystem->tolerance = ptrCompWeaponSystem->range - 1.0;
	}
}

void CompControlSystemPlayer::shutdown()
{
}
