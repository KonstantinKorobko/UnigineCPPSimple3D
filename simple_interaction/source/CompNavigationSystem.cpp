#include "CompNavigationSystem.h"
REGISTER_COMPONENT(CompNavigationSystem);

void CompNavigationSystem::addYField(int player_node_id)
{
	NodePtr ptrSelf = World::getNodeByID(aggregateId);
	NodePtr ptrPlayer = World::getNodeByID(player_node_id);

	float yAxisSelf = ptrSelf->getWorldPosition().y;
	float yAxisVehicle = ptrPlayer->getWorldPosition().y;

	CompNavigationSystem* ptrYAxisVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayer);
	NodePtr ptrYAxisVehicle;
	if (yAxisSelf <= yAxisVehicle)
	{
		ptrYAxisVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->leftYAxis);
		yAxisVehicle = ptrYAxisVehicle->getWorldPosition().y;
	}
	else
	{
		ptrYAxisVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->rightYAxis);
		yAxisVehicle = ptrYAxisVehicle->getWorldPosition().y;
	}
}

void CompNavigationSystem::init()
{
	ptrAggregate = World::getNodeByID(aggregateId);
}

void CompNavigationSystem::update()
{
}

void CompNavigationSystem::shutdown()
{
}
