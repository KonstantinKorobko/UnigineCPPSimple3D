#include "CompNavigationSystem.h"
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
}

void CompNavigationSystem::update()
{
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
