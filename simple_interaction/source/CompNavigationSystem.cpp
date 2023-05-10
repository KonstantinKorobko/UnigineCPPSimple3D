#include "CompNavigationSystem.h"
REGISTER_COMPONENT(CompNavigationSystem);

void CompNavigationSystem::addYField(int player_node_id)
{
	NodePtr ptrSelf = World::getNodeByID(aggregateId);
	NodePtr ptrPlayer = World::getNodeByID(player_node_id);

	float yAxisSelf = ptrSelf->getWorldPosition().y;
	float yAxisVehicle = ptrPlayer->getWorldPosition().y;

	CompNavigationSystem* ptrYAxisVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrPlayer);
	NodePtr ptrYAxisVehicle = nullptr;
	NodePtr ptrYAxisNextVehicle = ptrPlayer;

	while ((yAxisSelf < yAxisVehicle) && (ptrYAxisNextVehicle.get() != NULL))
	{
		ptrYAxisVehicle = ptrYAxisNextVehicle;
		yAxisVehicle = ptrYAxisVehicle->getWorldPosition().y;
		ptrYAxisVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrYAxisVehicle);
		ptrYAxisNextVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->leftYAxis);
	}

	if (ptrYAxisVehicle == ptrPlayer)
	{
		ptrYAxisNextVehicle = ptrPlayer;
		while ((yAxisSelf > yAxisVehicle) && (ptrYAxisNextVehicle.get() != NULL))
		{
			ptrYAxisVehicle = ptrYAxisNextVehicle;
			yAxisVehicle = ptrYAxisVehicle->getWorldPosition().y;
			ptrYAxisVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrYAxisVehicle);
			ptrYAxisNextVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->rightYAxis);
		}
	}

	if (yAxisSelf <= yAxisVehicle)
	{
		NodePtr ptrLeftVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->leftYAxis);
		if (ptrLeftVehicle.get() != NULL)
		{
			CompNavigationSystem* ptrLeftVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrLeftVehicle);
			ptrLeftVehicleNavSys->rightYAxis = aggregateId;
			rightYAxis = ptrLeftVehicleNavSys->aggregateId;
		}
		ptrYAxisVehicleNavSys->leftYAxis = aggregateId;
	}
	else
	{
		NodePtr ptrRightVehicle = World::getNodeByID(ptrYAxisVehicleNavSys->rightYAxis);
		if (ptrRightVehicle.get() != NULL)
		{
			CompNavigationSystem* ptrRightVehicleNavSys = ComponentSystem::get()->getComponentInChildren<CompNavigationSystem>(ptrRightVehicle);
			ptrRightVehicleNavSys->rightYAxis = aggregateId;
			leftYAxis = ptrRightVehicleNavSys->aggregateId;
		}
		ptrYAxisVehicleNavSys->rightYAxis = aggregateId;
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
