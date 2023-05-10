#include "CompMoveSystem.h"
REGISTER_COMPONENT(CompMoveSystem);

void CompMoveSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
}

void CompMoveSystem::update()
{
	//Math::vec3 pos = ptrAggregate->getWorldPosition();
	//ptrAggregate->translate(Math::vec3(0.0, 0.001 * speed, 0.0));
}

void CompMoveSystem::shutdown()
{
}
