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
