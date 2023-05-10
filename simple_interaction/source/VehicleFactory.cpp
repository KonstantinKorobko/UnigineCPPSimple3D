#include "VehicleFactory.h"
#include "CompControlSystem.h"
#include "CompDamageSystem.h"
#include "CompMoveSystem.h"
#include "CompNavigationSystem.h"
#include "CompRotateSystem.h"
#include <UnigineMeshDynamic.h>
#include <UnigineObjects.h>
#include <UniginePrimitives.h>

void VehicleFactory::constructVehicle(int vehicle_type, GlobalRadar& ref_global_radar)
{
	NodeDummyPtr ptrVehicle = NodeDummy::create();
	ptrVehicle->setSaveToWorldEnabled(false);
	ptrVehicle->setShowInEditorEnabled(true);

	//Parametrise vehicle. 
	float armor = 0.0;
	float power = 0.0;
	float speed = 0.0;
	float torqueVehicle = 0.0;
	float torqueTurret = 0.0;
	Math::vec3 sizeHull;
	Math::vec3 sizeTurret;

	switch (vehicle_type)
	{
	case T_VEHICLE_PLAYER:
	{
		ref_global_radar.setPlayerId(ptrVehicle->getID());

		armor = 100.0;
		power = 5.0;
		speed = 2.0;
		torqueVehicle = 2.0;
		torqueTurret = 2.0;

		sizeHull = Math::vec3(0.4, 0.6, 0.2);
		sizeTurret = Math::vec3(0.1, 0.7, 0.05);

		break;
	}
	case T_VEHICLE_LIGHT:
	{
		armor = 10.0;
		power = 1.0;
		speed = 2.0;
		torqueVehicle = 2.0;
		torqueTurret = 2.0;

		sizeHull = Math::vec3(0.2, 0.3, 0.1);
		sizeTurret = Math::vec3(0.07, 0.2, 0.04);

		break;
	}
	case T_VEHICLE_MIDDLE:
	{
		armor = 20.0;
		power = 2.0;
		speed = 1.5;
		torqueVehicle = 1.5;
		torqueTurret = 1.5;

		sizeHull = Math::vec3(0.3, 0.4, 0.15);
		sizeTurret = Math::vec3(0.1, 0.35, 0.06);

		break;
	}
	case T_VEHICLE_HARD:
	{
		armor = 30.0;
		power = 3.0;
		speed = 1.0;
		torqueVehicle = 1.0;
		torqueTurret = 1.0;

		sizeHull = Math::vec3(0.4, 0.5, 0.2);
		sizeTurret = Math::vec3(0.17, 0.4, 0.08);

		break;
	}
	default:
		break;
	}
	//create aggregates
	NodePtr ptrHull = createHull(sizeHull);
	ptrVehicle->addChild(ptrHull);
	NodePtr ptrTurret = createTurret(sizeTurret);
	ptrVehicle->addChild(ptrTurret);

	Math::vec3 turretPos = Math::vec3(0.0, 0.0, sizeHull.z * 0.5 + sizeTurret.z * 0.5 + 0.005);
	ptrTurret->setPosition(turretPos);

	Math::vec3 vehiclePos = Math::vec3(ref_global_radar.getSpawnPosX(), ref_global_radar.getSpawnPosY(), sizeHull.z * 0.5 + 0.05);
	ptrVehicle->setWorldPosition(vehiclePos);

	//create and connect aggregates control components
	CompControlSystem* ptrCompControlSystem = ComponentSystem::get()->addComponent<CompControlSystem>(ptrVehicle);
	ptrCompControlSystem->vehicleId = ptrVehicle->getID();
	ptrCompControlSystem->vehicleType = vehicle_type;	
	
	CompMoveSystem* ptrCompMoveSystem = ComponentSystem::get()->addComponent<CompMoveSystem>(ptrVehicle);
	ptrCompMoveSystem->aggregateId = ptrVehicle->getID();
	ptrCompMoveSystem->speed = speed;

	CompRotateSystem* ptrCompRotateSystemVehicle = ComponentSystem::get()->addComponent<CompRotateSystem>(ptrVehicle);
	ptrCompRotateSystemVehicle->aggregateId = ptrVehicle->getID();
	ptrCompRotateSystemVehicle->torque = torqueVehicle;
	
	CompDamageSystem* ptrCompDamageSystem = ComponentSystem::get()->addComponent<CompDamageSystem>(ptrTurret);
	ptrCompDamageSystem->aggregateId = ptrTurret->getID();
	ptrCompDamageSystem->armor = armor;
	ptrCompDamageSystem->power = power;
	
	CompRotateSystem* ptrCompRotateSystemTurret = ComponentSystem::get()->addComponent<CompRotateSystem>(ptrTurret);
	ptrCompRotateSystemTurret->aggregateId = ptrTurret->getID();
	ptrCompRotateSystemTurret->torque = torqueTurret;
}

NodePtr VehicleFactory::createHull(Math::vec3 hull_size)
{
	ObjectMeshDynamicPtr ptrHull = Primitives::createBox(hull_size);
	Primitives::addBoxSurface(ptrHull, hull_size, Math::mat4_identity);

	ptrHull->setSaveToWorldEnabled(true);
	ptrHull->setShowInEditorEnabled(true);

	return ptrHull;
}
NodePtr VehicleFactory::createTurret(Math::vec3 turret_size)
{
	//We need turret with right size, but don't need to move turret coordinate center (pivot).
	//Pivot should be synchronized with all other vehicle components.
	//So we will modify just geometry with vertices.

	float length = turret_size.y;
	turret_size.y = turret_size.x;

	ObjectMeshDynamicPtr ptrTurret = Primitives::createBox(turret_size);
	Primitives::addBoxSurface(ptrTurret, turret_size, Math::mat4_identity);

	ptrTurret->setSaveToWorldEnabled(true);
	ptrTurret->setShowInEditorEnabled(true);

	MeshPtr ptrTurretMesh = Mesh::create();
	ptrTurret->getMesh(ptrTurretMesh);

	Math::vec3 vertex;
	for (int i = 6; i < 12; i++)
	{
		vertex = ptrTurretMesh->getVertex(i, 0);
		vertex.y += length;
		ptrTurretMesh->setVertex(i, vertex, 0);
	}
	for (int i = 18; i < 24; i++)
	{
		vertex = ptrTurretMesh->getVertex(i, 0);
		vertex.y += length;
		ptrTurretMesh->setVertex(i, vertex, 0);
	}
	for (int i = 30; i < 36; i++)
	{
		vertex = ptrTurretMesh->getVertex(i, 0);
		vertex.y += length;
		ptrTurretMesh->setVertex(i, vertex, 0);
	}
	for (int i = 42; i < 47; i++)
	{
		vertex = ptrTurretMesh->getVertex(i, 0);
		vertex.y += length;
		ptrTurretMesh->setVertex(i, vertex, 0);
	}

	ptrTurret->setMesh(ptrTurretMesh);

	return ptrTurret;
}

GlobalRadar::GlobalRadar()
{
	playerId = 0;
	spawnPosX = 0.0;
	spawnPosY = 0.0;
}

GlobalRadar::~GlobalRadar()
{
}

int GlobalRadar::getPlayerId()
{
	return playerId;
}

void GlobalRadar::setPlayerId(int node_id)
{
	playerId = node_id;
}

void GlobalRadar::setSpawnPos(float pos_x, float pos_y)
{
	spawnPosX = pos_x;
	spawnPosY = pos_y;
}

float GlobalRadar::getSpawnPosX()
{
	return spawnPosX;
}

float GlobalRadar::getSpawnPosY()
{
	return spawnPosY;
}
