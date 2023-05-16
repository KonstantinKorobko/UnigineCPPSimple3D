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

	NodePtr ptrRight = ptrPlayerNavSys->ptrRightYAxis;
	if (ptrRight.get() != NULL)
	{
		CompNavigationSystem* ptrRightNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayerNavSys->ptrRightYAxis);
		ptrRightNavSys->ptrLeftYAxis = ptrAggregate;
		ptrRightYAxis = ptrPlayerNavSys->ptrRightYAxis;
		ptrLeftYAxis = ptr_player;
		ptrPlayerNavSys->ptrRightYAxis = ptrAggregate;
	}
	else
	{
		ptrLeftYAxis = ptr_player;
		ptrPlayerNavSys->ptrRightYAxis = ptrAggregate;
	}
}

void CompNavigationSystem::init()
{
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
	NodePtr ptrCheck = nullptr;
	CompNavigationSystem* ptrRightNavSys = nullptr;
	Math::vec3 posSelf = ptrAggregate->getWorldPosition();
	Math::vec3 posTarget;
	float distance = 0.0;
	float distanceMin = 10000.0;

	ptrCheck = ptrRightYAxis;
	while (ptrCheck.get() != NULL)
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
	t1 = t1 - Game::getIFps();
	if (t1 <= 0.0)
	{
		t1 = 1.0;

		/*NodePtr ptrCheck = ptrTarget;
		if (ptrCheck.get() != NULL)
		{
			ptrCompMoveSystem->setpoint = ptrTarget->getWorldPosition();

			targetDistance = ptrCompMoveSystem->getDistance();

			if ((targetDistance - shootRange * shootRange) < 0.0)
			{
				//**********************************
			}
		}*/
	}
	//visualize list of vihicles 
	NodePtr ptrCheck = ptrLeftYAxis;
	if (ptrCheck.get() != NULL)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrLeftYAxis->getWorldPosition(), Math::vec4(0.0, 1.0, 0.0, 1.0));
	}
	//visualize target
	ptrCheck = ptrTarget;
	if (ptrCheck.get() != NULL)
	{
		Visualizer::renderLine3D(ptrAggregate->getWorldPosition(), ptrTarget->getWorldPosition(), Math::vec4(1.0, 0.0, 0.0, 1.0));
	}
}

void CompNavigationSystem::shutdown()
{
}
