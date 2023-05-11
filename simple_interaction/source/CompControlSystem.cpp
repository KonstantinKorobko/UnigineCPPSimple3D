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
	t8 = t8 - Game::getIFps();
	if (t8 <= 0.0)
	{
		t8 = 8.0;

		ptrCompNavigationSystem->setPatrolPoint(10);
	}
}

void CompControlSystem::shutdown()
{
}
