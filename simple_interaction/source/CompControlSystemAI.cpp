/*
* @author  Konstantin Korobko
*/
#include "CompControlSystemAI.h"
#include <UnigineGame.h>
REGISTER_COMPONENT(CompControlSystemAI);

void CompControlSystemAI::init()
{
	ptrCompNavigationSystem = ComponentSystem::get()->getComponent<CompNavigationSystem>(ptrAggregate);
}

void CompControlSystemAI::update()
{
	t15 = t15 - Game::getIFps();
	if (t15 <= 0.0)
	{
		t15 = 4.0;

		ptrCompNavigationSystem->setPatrolPoint(10);
	}
}

void CompControlSystemAI::shutdown()
{
}
