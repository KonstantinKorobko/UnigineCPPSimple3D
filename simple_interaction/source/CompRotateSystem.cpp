/*
* @author  Konstantin Korobko
*/
#include "CompRotateSystem.h"
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompRotateSystem);

void CompRotateSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);

	stateLast = stateCurrent = 0;
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

	difference = sRotationMat[4] * rotateVec.get().y - sRotationMat[5] * rotateVec.get().x;

	//crutch for rotate trembling. sry, no commercial algorytms here
	if ((difference > -0.03) && (difference < 0.03))
	{
		rotateVec = Math::vec3(0.0);
		return 0.0f;
	}
	
	if (difference > 0)
	{
		return torque;
	}
	else if (difference < 0)
	{
		return -torque;
	}

	return 0.0f;
}
