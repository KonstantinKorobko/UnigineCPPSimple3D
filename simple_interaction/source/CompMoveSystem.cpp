#include "CompMoveSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompMoveSystem);

void CompMoveSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);

	ptrCompRotateSystem = ComponentSystem::get()->getComponent<CompRotateSystem>(ptrAggregate);
}

void CompMoveSystem::update()
{
	Math::vec3 rotVec = getRotationVec();

	if (rotVec.z >= 0.01)
	{
		ptrCompRotateSystem->rotateVec = rotVec;
	}
	//Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
	//Math::vec3 posSet = setpoint;

	//ptrAggregate->translate(Math::vec3(0.0, 0.001 * speed, 0.0));

	//Visualizer::renderLine3D(posCurrent, posSet, Math::vec4(0.0, 0.5, 0.5, 1.0));
}

void CompMoveSystem::shutdown()
{
}

Math::vec3 CompMoveSystem::getRotationVec()
{
	Math::vec3 posCurrent = ptrAggregate->getWorldPosition();

	float calcBuffer[3]{ 0.0 };
	calcBuffer[0] = setpoint.get().x - posCurrent.x;
	calcBuffer[1] = setpoint.get().y - posCurrent.y;
	calcBuffer[2] = sqrtf(calcBuffer[0] * calcBuffer[0] + calcBuffer[1] * calcBuffer[1]);
	calcBuffer[0] /= calcBuffer[2];
	calcBuffer[1] /= calcBuffer[2];

	return Math::vec3(calcBuffer[0], calcBuffer[1], calcBuffer[2]);
}
