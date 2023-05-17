#include "CompWeaponSystem.h"
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
