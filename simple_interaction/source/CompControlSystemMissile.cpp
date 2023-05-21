/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemMissile.h"
#include "CompDamageSystem.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemMissile);

void CompControlSystemMissile::init()
{
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);
	ptrCompMoveSystem->speed = 0.08;
	ptrCompMoveSystem->tolerance = 0.0;	
}

void CompControlSystemMissile::update()
{
	lifeTime = lifeTime - Game::getIFps();
	if (lifeTime <= 0)
	{
		ptrAggregate->deleteLater();
	}

	if (ptrCompMoveSystem->distance - ptrCompMoveSystem->speed <= 0.0)
	{
		if (ptrTarget.get() != nullptr)
		{
			Math::vec3 collision = ptrTarget->getWorldPosition();
			collision.x = collision.x - ptrAggregate->getWorldPosition().x;
			collision.y = collision.y - ptrAggregate->getWorldPosition().y;
			collision.z = collision.x * collision.x + collision.y * collision.y;

			if (collision.z <= 0.04)
			{
				CompDamageSystem* ptrCompDamageSystem = ComponentSystem::get()->getComponent<CompDamageSystem>(ptrTarget);
				ptrCompDamageSystem->damageAdd = ptrCompDamageSystem->damageAdd + damage;				
			}
		}
		ptrAggregate->deleteLater();
	}
}

void CompControlSystemMissile::shutdown()
{
}
