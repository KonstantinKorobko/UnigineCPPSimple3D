#include "CompRotateSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompRotateSystem);

void CompRotateSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
}

void CompRotateSystem::update()
{
	if (rotateVec.get().z != 0.0)
	{
		Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
		Math::vec3 posRotate = posCurrent + rotateVec;
		posRotate.z = posCurrent.z;
		Visualizer::renderLine3D(posCurrent, posRotate, Math::vec4(0.5, 0.5, 0.0, 1.0));
	}
}

void CompRotateSystem::shutdown()
{
}
