/*
* @author  Konstantin Korobko
*/
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
		//at this time i don't go to calculate with quaternions
		ptrAggregate->rotate(0.0, 0.0, calcTorque());

		Math::vec3 posCurrent = ptrAggregate->getWorldPosition();
		Math::vec3 posRotate = posCurrent + rotateVec;
		posRotate.z = posCurrent.z;
		Visualizer::renderLine3D(posCurrent, posRotate, Math::vec4(0.5, 0.5, 0.0, 1.0));
	}
}

void CompRotateSystem::shutdown()
{
}

float CompRotateSystem::calcTorque()
{
	Math::mat3 sRotationMat = ptrAggregate->getRotation().getMat3();

	if ((sRotationMat[4] * rotateVec.get().y) - (sRotationMat[5] * rotateVec.get().x) < 0)
	{
		return -0.2 * torque;
	}
	else
	{
		return 0.2 * torque;
	}

	return 0.0f;
}
