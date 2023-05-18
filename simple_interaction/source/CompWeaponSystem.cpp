#include "CompWeaponSystem.h"
#include "CompMoveSystem.h"
#include "CompControlSystemMissile.h"
#include <UniginePrimitives.h>
#include <UnigineGame.h>
REGISTER_COMPONENT(CompWeaponSystem);

void CompWeaponSystem::init()
{
	ptrCompRotateSystem = ComponentSystem::get()->getComponent<CompRotateSystem>(ptrAggregate);
}

void CompWeaponSystem::update()
{
	if (ptrTarget.get() != nullptr)
	{
		calcData();

		ptrCompRotateSystem->rotateVec = Math::vec3(calcBuffer[0], calcBuffer[1], calcBuffer[2]);

		if ((ptrCompRotateSystem->difference > -0.1) && (ptrCompRotateSystem->difference < 0.1) && (tReload <= 0.0))
		{
			fire();

			tReload = 1.5;
		}
	}
	if (tReload > 0.0)
	{
		tReload = tReload - Game::getIFps();
	}
}

void CompWeaponSystem::shutdown()
{
}

void CompWeaponSystem::calcData()
{
	Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
	Math::vec3 posTarget = ptrTarget->getWorldPosition();

	calcBuffer[0] = posTarget.x - posCurrent.x;
	calcBuffer[1] = posTarget.y - posCurrent.y;
	calcBuffer[2] = sqrtf(calcBuffer[0] * calcBuffer[0] + calcBuffer[1] * calcBuffer[1]);
	calcBuffer[0] /= calcBuffer[2];
	calcBuffer[1] /= calcBuffer[2];
}

void CompWeaponSystem::fire(int missile_type)
{
	ObjectMeshDynamicPtr ptrMissile = Primitives::createSphere(0.1);
	Primitives::addSphereSurface(ptrMissile, 0.1, Math::mat4_identity);

	ptrMissile->setSaveToWorldEnabled(true);
	ptrMissile->setShowInEditorEnabled(true);

	//in future init position with turret geometry
	ptrMissile->setWorldPosition(ptrAggregate->getWorldPosition());
	ptrMissile->setWorldRotation(ptrAggregate->getWorldRotation());

	CompMoveSystem* ptrCompMoveSystem = ComponentSystem::get()->addComponent<CompMoveSystem>(ptrMissile);
	ptrCompMoveSystem->ptrAggregate = ptrMissile;

	CompControlSystemMissile* ptrCompControlSystemMissile = ComponentSystem::get()->addComponent<CompControlSystemMissile>(ptrMissile);
	ptrCompControlSystemMissile->ptrAggregate = ptrMissile;
	ptrCompControlSystemMissile->lifeTime = 2.5;
	ptrCompControlSystemMissile->ptrTarget = ptrTarget;
	ptrCompControlSystemMissile->damage = power;
}
