/*
* @author  Konstantin Korobko
*/
#include "CompNavigationSystem.h"
#include <UnigineGame.h>
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompNavigationSystem);

void CompNavigationSystem::addYField(int player_node_id)
{
	NodePtr ptrPlayer = World::getNodeByID(player_node_id);
	CompNavigationSystem* ptrPlayerNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayer);

	NodePtr ptrRight = World::getNodeByID(ptrPlayerNavSys->rightYAxis);
	if (ptrRight.get() != NULL)
	{
		CompNavigationSystem* ptrRightNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrRight);
		ptrRightNavSys->leftYAxis = aggregateId;
		rightYAxis = ptrPlayerNavSys->rightYAxis;
		leftYAxis = player_node_id;
		ptrPlayerNavSys->rightYAxis = aggregateId;
	}
	else
	{
		leftYAxis = player_node_id;
		ptrPlayerNavSys->rightYAxis = aggregateId;
	}
}

void CompNavigationSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
	ptrCompMoveSystem = ComponentSystem::get()->getComponent<CompMoveSystem>(ptrAggregate);

	Math::Random rand;
	seed = rand.getSeed();
	random.seed(seed);
}

void CompNavigationSystem::setPatrolPoint(int radius)
{
	std::uniform_real_distribution<> checkRange(-1.0, 1.0);
	Math::vec3 checkPoint;
	checkPoint.x = checkRange(random) * radius;
	seed++;
	checkPoint.y = checkRange(random) * radius;
	seed++;
	checkPoint.z = 0.0;

	ptrCompMoveSystem->setpoint = checkPoint + spawnPoint;
}

void CompNavigationSystem::setClotherTarget()
{
	NodePtr ptrTarget = World::getNodeByID(rightYAxis);
	CompNavigationSystem* ptrRightNavSys;
	Math::vec3 selfPos = ptrAggregate->getWorldPosition();
	Math::vec3 targetPos;
	float distance = 0.0;
	float distanceLast = 10000.0;
	targetId = rightYAxis;

	while (ptrTarget.get() != NULL)
	{
		ptrRightNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrTarget);
		targetPos = ptrTarget->getWorldPosition();
		distance = (selfPos.x - targetPos.x) * (selfPos.x - targetPos.x) + (selfPos.y - targetPos.y) * (selfPos.y - targetPos.y);
		if (distance < distanceLast)
		{
			distance = distanceLast;
			targetId = ptrRightNavSys->aggregateId;
		}
		
		ptrTarget = World::getNodeByID(ptrRightNavSys->rightYAxis);
	}	
}

void CompNavigationSystem::update()
{
	t1 = t1 - Game::getIFps();
	if (t1 <= 0.0)
	{
		t1 = 1.0;

		NodePtr ptrTarget = World::getNodeByID(targetId);

		if (ptrTarget.get() != NULL)
		{
			ptrCompMoveSystem->setpoint = ptrTarget->getWorldPosition();

			targetDistance = ptrCompMoveSystem->getDistance();

			if ((targetDistance - shootRange * shootRange) < 0.0)
			{
				//**********************************
			}
		}
	}
	//visualize list of vihicles 
	NodePtr ptrNextVehicle = World::getNodeByID(leftYAxis);
	if (ptrNextVehicle.get() != NULL)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrNextVehicle->getWorldPosition(), Math::vec4(0.0, 1.0, 0.0, 1.0));
	}
}

void CompNavigationSystem::shutdown()
{
}
