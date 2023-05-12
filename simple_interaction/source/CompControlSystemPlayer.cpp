/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemPlayer.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemPlayer);

void CompControlSystemPlayer::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
}

void CompControlSystemPlayer::update()
{
	t15 = t15 - Game::getIFps();
	if (t15 <= 0.0)
	{
		t15 = 4.0;

		ptrCompNavigationSystem->setPatrolPoint(10);
	}
}

void CompControlSystemPlayer::shutdown()
{
}
