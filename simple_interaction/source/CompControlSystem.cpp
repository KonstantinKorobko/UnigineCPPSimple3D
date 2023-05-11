/*
* @author  Konstantin Korobko
*/
#include "CompControlSystem.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystem);

void CompControlSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
}

void CompControlSystem::update()
{
	t15 = t15 - Game::getIFps();
	if (t15 <= 0.0)
	{
		t15 = 15.0;

		ptrCompNavigationSystem->setPatrolPoint(10);
	}
}

void CompControlSystem::shutdown()
{
}
