#include "CompMoveSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompMoveSystem);

void CompMoveSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
}

void CompMoveSystem::update()
{
	Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
	Math::vec3 posSet = setpoint;

	//ptrAggregate->translate(Math::vec3(0.0, 0.001 * speed, 0.0));

	Visualizer::renderLine3D(posCurrent, posSet, Math::vec4(0.0, 0.5, 0.5, 1.0));
}

void CompMoveSystem::shutdown()
{
}
