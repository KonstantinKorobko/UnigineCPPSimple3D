/*
* @author  Konstantin Korobko
*/
#include "CompMoveSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompMoveSystem);

void CompMoveSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);

	ptrCompRotateSystem = ComponentSystem::get()->getComponent<CompRotateSystem>(ptrAggregate);

	calcBuffer[0] = 0.0;
	calcBuffer[1] = 0.0;
	calcBuffer[2] = 0.0;
}

void CompMoveSystem::update()
{
	//Math::vec3 rotVec = getRotationVec();
	if (true)
	{

	}
	calcMoveData();

	if (calcBuffer[2] > 1.0)
	{
		ptrAggregate->translate(Math::vec3(0.0, 0.001 * speed, 0.0));
	}

	if (calcBuffer[2] >= 0.001)
	{
		ptrCompRotateSystem->rotateVec = Math::vec3(calcBuffer[0], calcBuffer[1], calcBuffer[2]);
	}
	else
	{
		ptrCompRotateSystem->rotateVec = Math::vec3(0.0);
	}

	//Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
	//Math::vec3 posSet = setpoint;

	//ptrAggregate->translate(Math::vec3(0.0, 0.001 * speed, 0.0));

	//Visualizer::renderLine3D(posCurrent, posSet, Math::vec4(0.0, 0.5, 0.5, 1.0));
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
