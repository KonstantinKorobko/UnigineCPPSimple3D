/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemAI.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemAI);

void CompControlSystemAI::init()
{
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);
	ptrCompWeaponSystem = ComponentSystem::get()->getComponent<CompWeaponSystem>(ptrTurret);
}

void CompControlSystemAI::update()
{
	t15 = t15 - Game::getIFps();
	if (t15 <= 0.0)
	{
		t15 = 4.0;

		ptrCompMoveSystem->setpoint = ptrCompNavigationSystem->getPatrolPoint(10);
		ptrCompMoveSystem->tolerance = 0.0;
	}
}

void CompControlSystemAI::shutdown()
{
}
