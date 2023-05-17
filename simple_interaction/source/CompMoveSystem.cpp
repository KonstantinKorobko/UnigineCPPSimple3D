/*
* @author  Konstantin Korobko
*/
#include "CompMoveSystem.h"
#include <UnigineVisualizer.h>
#include <UnigineGame.h>
REGISTER_COMPONENT(CompMoveSystem);

void CompMoveSystem::init()
{
	ptrCompRotateSystem = ComponentSystem::get()->getComponent<CompRotateSystem>(ptrAggregate);

	calcBuffer[0] = 0.0;
	calcBuffer[1] = 0.0;
	calcBuffer[2] = 0.0;
}

void CompMoveSystem::update()
{
	calcMoveData();

	ptrCompRotateSystem->rotateVec = Math::vec3(calcBuffer[0], calcBuffer[1], calcBuffer[2]);

	if ((abs(calcBuffer[2]) - tolerance - speed) > 0.0)
	{
		ptrAggregate->translate(Math::vec3(0.0, speed, 0.0));
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
