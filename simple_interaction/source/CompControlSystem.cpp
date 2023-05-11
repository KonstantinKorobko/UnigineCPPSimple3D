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
	t5 = t5 - Game::getIFps();
	if (t5 <= 0.0)
	{
		t5 = 5.0;

		ptrCompNavigationSystem->setPatrolPoint(10);
	}
}

void CompControlSystem::shutdown()
{
}
