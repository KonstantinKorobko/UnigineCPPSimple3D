/*
* @author  Konstantin Korobko
*/
#include "CompNavigationSystem.h"
#include <UnigineGame.h>
#include <UnigineVisualizer.h>
REGISTER_COMPONENT(CompNavigationSystem);

void CompNavigationSystem::addYField(NodePtr ptr_player)
{
	CompNavigationSystem* ptrPlayerNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptr_player);

	if (ptrPlayerNavSys->ptrRightYAxis.get() != nullptr)
	{
		CompNavigationSystem* ptrRightNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayerNavSys->ptrRightYAxis);
		ptrRightNavSys->ptrLeftYAxis = ptrAggregate.get();
		ptrRightYAxis = ptrPlayerNavSys->ptrRightYAxis.get();
		ptrLeftYAxis = ptr_player;
		ptrPlayerNavSys->ptrRightYAxis = ptrAggregate.get();

		//check list init debug
		Log::message("left %f\n", ptrPlayerNavSys->ptrRightYAxis->getWorldPosition().y);
		Log::message("center %f\n", ptrAggregate->getWorldPosition().y);
		Log::message("right %f\n", ptrRightNavSys->ptrLeftYAxis->getWorldPosition().y);
	}
	else
	{
		ptrLeftYAxis = ptr_player;
		ptrPlayerNavSys->ptrRightYAxis = ptrAggregate.get();
	}
}

void CompNavigationSystem::removeYField()
{
	CompNavigationSystem* ptrLeftVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrLeftYAxis);
	CompNavigationSystem* ptrRightVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrRightYAxis);

	if ((ptrLeftYAxis.get() != nullptr) && (ptrRightYAxis.get() != nullptr))
	{
		ptrLeftVehicleNavSys->ptrRightYAxis = ptrRightYAxis.get();
		ptrRightVehicleNavSys->ptrLeftYAxis = ptrLeftYAxis.get();
	}
}

void CompNavigationSystem::init()
{
	Math::Random rand;
	seed = rand.getSeed();
	random.seed(seed);
}

Math::vec3 CompNavigationSystem::getPatrolPoint(int radius)
{
	std::uniform_real_distribution<> checkRange(-1.0, 1.0);
	Math::vec3 checkPoint;
	checkPoint.x = checkRange(random) * radius;
	seed++;
	checkPoint.y = checkRange(random) * radius;
	seed++;
	checkPoint.z = 0.0;

	return checkPoint + spawnPoint;
}

void CompNavigationSystem::getClotherTarget()
{
	NodePtr ptrCheck = nullptr;
	CompNavigationSystem* ptrRightNavSys = nullptr;
	Math::vec3 posSelf = ptrAggregate->getWorldPosition();
	Math::vec3 posTarget;
	float distance = 0.0;
	float distanceMin = 10000.0;

	ptrCheck = ptrRightYAxis;
	while (ptrCheck.get() != nullptr)
	{
		ptrRightNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrCheck);
		posTarget = ptrCheck->getWorldPosition();
		distance = (posSelf.x - posTarget.x) * (posSelf.x - posTarget.x) + (posSelf.y - posTarget.y) * (posSelf.y - posTarget.y);
		if (distanceMin > distance)
		{
			distanceMin = distance;
			ptrTarget = ptrCheck;
		}

		ptrCheck = ptrRightNavSys->ptrRightYAxis;
	}
}

void CompNavigationSystem::update()
{
	//visualize list of vihicles 
	if (ptrRightYAxis.get() != nullptr)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrRightYAxis->getWorldPosition(), Math::vec4(0.0, 0.4, 0.5, 0.5));
	}
	/*if (ptrLeftYAxis.get() != nullptr)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrLeftYAxis->getWorldPosition(), Math::vec4(0.0, 0.0, 1.0, 1.0));
	}*/
	//visualize target
	/*if (ptrTarget.get() != nullptr)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrTarget->getWorldPosition(), Math::vec4(1.0, 0.0, 0.0, 1.0));
	}*/
}

void CompNavigationSystem::shutdown()
{
}
