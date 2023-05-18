/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemMissile.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemMissile);

void CompControlSystemMissile::init()
{
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);	
	ptrCompMoveSystem->speed = 0.1;
	ptrCompMoveSystem->setpoint = ptrTarget->getWorldPosition();
}

void CompControlSystemMissile::update()
{
	lifeTime = lifeTime - Game::getIFps();
	if (lifeTime <= 0)
	{
		ptrAggregate->deleteLater();
	}

	if (ptrCompMoveSystem->distance <= 0.4)
	{
		ptrAggregate->deleteLater();
	}
}

void CompControlSystemMissile::shutdown()
{
}
