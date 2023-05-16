/*
* @author  Konstantin Korobko
*/
#include "CompMoveSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompMoveSystem);

float CompMoveSystem::getDistance()
{
	return calcBuffer[2];
}

void CompMoveSystem::init()
{
	ptrCompRotateSystem = ComponentSystem::get()->getComponent<CompRotateSystem>(ptrAggregate);

	calcBuffer[0] = 0.0;
	calcBuffer[1] = 0.0;
	calcBuffer[2] = 0.0;
}

void CompMoveSystem::update()
{
	if ((setpoint.get().x != 0.0) || (setpoint.get().y != 0.0))
	{
		calcMoveData();

		ptrAggregate->translate(Math::vec3(0.0, speed, 0.0));		

		ptrCompRotateSystem->rotateVec = Math::vec3(calcBuffer[0], calcBuffer[1], calcBuffer[2]);

		if ((abs(calcBuffer[2]) - speed) < 0.0)
		{
			setpoint = Math::vec3(0.0);
		}
	}
}

void CompMoveSystem::shutdown()
{
}

void CompMoveSystem::calcMoveData()
{
	Math::vec3 posCurrent = ptrAggregate->getWorldPosition();

	calcBuffer[0] = setpoint.get().x - posCurrent.x;
	calcBuffer[1] = setpoint.get().y - posCurrent.y;
	calcBuffer[2] = sqrtf(calcBuffer[0] * calcBuffer[0] + calcBuffer[1] * calcBuffer[1]);
	calcBuffer[0] /= calcBuffer[2];
	calcBuffer[1] /= calcBuffer[2];
}
