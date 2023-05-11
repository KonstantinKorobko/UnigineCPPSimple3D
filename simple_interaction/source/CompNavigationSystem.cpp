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

	float ySelf = World::getNodeByID(aggregateId)->getWorldPosition().y;
	float yNext = ptrPlayer->getWorldPosition().y;

	CompNavigationSystem* ptrNextNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayer);
	NodePtr ptrNext = nullptr;
	NodePtr ptrCheck = ptrPlayer;

	while ((ySelf < yNext) && (ptrCheck.get() != NULL))
	{
		ptrNext = ptrCheck;
		yNext = ptrNext->getWorldPosition().y;
		ptrNextNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrNext);
		ptrCheck = World::getNodeByID(ptrNextNavSys->leftYAxis);
	}

	ptrCheck = ptrPlayer;
	while ((ySelf > yNext) && (ptrCheck.get() != NULL))
	{
		ptrNext = ptrCheck;
		yNext = ptrNext->getWorldPosition().y;
		ptrNextNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrNext);
		ptrCheck = World::getNodeByID(ptrNextNavSys->rightYAxis);
	}

	if (ySelf <= yNext)
	{
		NodePtr ptrLeftVehicle = World::getNodeByID(ptrNextNavSys->leftYAxis);
		if (ptrLeftVehicle.get() != NULL)
		{
			CompNavigationSystem* ptrLeftVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrLeftVehicle);
			ptrLeftVehicleNavSys->rightYAxis = aggregateId;
			leftYAxis = ptrLeftVehicleNavSys->aggregateId;
		}
		ptrNextNavSys->leftYAxis = aggregateId;
		rightYAxis = ptrNextNavSys->aggregateId;
	}
	else
	{
		NodePtr ptrRightVehicle = World::getNodeByID(ptrNextNavSys->rightYAxis);
		if (ptrRightVehicle.get() != NULL)
		{
			CompNavigationSystem* ptrRightVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrRightVehicle);
			ptrRightVehicleNavSys->rightYAxis = aggregateId;
			rightYAxis = ptrRightVehicleNavSys->aggregateId;
		}
		ptrNextNavSys->rightYAxis = aggregateId;
		leftYAxis = ptrNextNavSys->aggregateId;
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

	ptrCompMoveSystem->setpoint = checkPoint + spawnPoint.get();
}

void CompNavigationSystem::update()
{
	t500 = t500 - Game::getIFps();
	if (t500 <= 0.0)
	{
		t500 = 500.0;
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
