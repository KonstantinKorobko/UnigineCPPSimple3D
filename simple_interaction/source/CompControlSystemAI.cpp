/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemAI.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemAI);

void CompControlSystemAI::init()
{
	ptrCompDamageSystem = ComponentSystem::get()->getComponent<CompDamageSystem>(ptrAggregate);
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);
	ptrCompWeaponSystem = ComponentSystem::get()->getComponent<CompWeaponSystem>(ptrTurret);
}

void CompControlSystemAI::update()
{
	t0_5 = t0_5 - Game::getIFps();

	if (t0_5 <= 0.0)
	{
		t0_5 = 0.5;

		t5 = t5 - t0_5;

		if (ptrCompWeaponSystem->ptrTarget.get() == nullptr)
		{
			Math::vec3 distance = ptrCompNavigationSystem->ptrTarget->getWorldPosition();
			distance.x = distance.x - ptrAggregate->getWorldPosition().x;
			distance.y = distance.y - ptrAggregate->getWorldPosition().y;
			distance.z = distance.x * distance.x + distance.y * distance.y;

			if (distance.z <= (ptrCompNavigationSystem->radarRadius * ptrCompNavigationSystem->radarRadius))
			{
				ptrCompMoveSystem->setpoint = ptrCompNavigationSystem->ptrTarget->getWorldPosition();
				ptrCompMoveSystem->tolerance = ptrCompWeaponSystem->range - 1.0;
				ptrCompWeaponSystem->ptrTarget = ptrCompNavigationSystem->ptrTarget;
			}
		}

		if ((t5 <= 0.0) && (ptrCompWeaponSystem->ptrTarget.get() == nullptr))
		{
			t5 = 5.0;

			ptrCompMoveSystem->setpoint = ptrCompNavigationSystem->getPatrolPoint(10);
			ptrCompMoveSystem->tolerance = 0.0;
		}

		if (ptrCompDamageSystem->armor < 0.0)
		{
			ptrCompNavigationSystem->removeYField();

			ptrAggregate->deleteLater();
		}
	}
}

void CompControlSystemAI::shutdown()
{
}
