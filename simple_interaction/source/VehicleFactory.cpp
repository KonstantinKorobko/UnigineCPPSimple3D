/*
* @author  Konstantin Korobko
*/
#include "VehicleFactory.h"
#include "CompControlSystemAI.h"
#include "CompControlSystemPlayer.h"
#include "CompDamageSystem.h"
#include "CompMoveSystem.h"
#include "CompNavigationSystem.h"
#include "CompRotateSystem.h"
#include "CompWeaponSystem.h"
#include <UnigineMeshDynamic.h>
#include <UnigineObjects.h>
#include <UniginePrimitives.h>

void VehicleFactory::constructVehicle(int vehicle_type, GlobalRadar& ref_global_radar)
{
	NodeDummyPtr ptrVehicle = NodeDummy::create();
	ptrVehicle->setSaveToWorldEnabled(true);
	ptrVehicle->setShowInEditorEnabled(true);	

	//Parametrise vehicle. 
	float armor = 0.0;
	float power = 0.0;
	float speed = 0.0;
	float torqueVehicle = 0.0;
	float torqueTurret = 0.0;
	float radarRadius = 0.0;
	float shootRange = 0.0;
	Math::vec3 sizeHull;
	Math::vec3 sizeTurret;
	Math::vec4 hullColor;
	Math::vec4 turretColor;

	switch (vehicle_type)
	{
	case T_VEHICLE_PLAYER:
	{
		ref_global_radar.setPlayer(ptrVehicle);

		armor = 100.0;
		power = 5.0;
		speed = 0.01;
		torqueVehicle = 1.0;
		torqueTurret = 2.0;
		radarRadius = 20.0;
		shootRange = 7.0;

		sizeHull = Math::vec3(0.4, 0.6, 0.2);
		sizeTurret = Math::vec3(0.1, 0.7, 0.05);

		turretColor = hullColor = Math::vec4(60.0 / 255.0, 195.0 / 255.0, 255.0 / 255.0, 1.0f);

		break;
	}
	case T_VEHICLE_LIGHT:
	{
		armor = 10.0;
		power = 1.0;
		speed = 0.01;
		torqueVehicle = 1.0;
		torqueTurret = 2.0;
		radarRadius = 6.0;
		shootRange = 4.5;

		sizeHull = Math::vec3(0.2, 0.3, 0.1);
		sizeTurret = Math::vec3(0.07, 0.2, 0.04);

		turretColor = hullColor = Math::vec4(255.0 / 255.0, 180.0 / 255.0, 174.0 / 255.0, 1.0f);

		break;
	}
	case T_VEHICLE_MIDDLE:
	{
		armor = 20.0;
		power = 2.0;
		speed = 0.0075;
		torqueVehicle = 0.75;
		torqueTurret = 1.5;
		radarRadius = 6.5;
		shootRange = 5.0;

		sizeHull = Math::vec3(0.3, 0.4, 0.15);
		sizeTurret = Math::vec3(0.1, 0.35, 0.06);

		turretColor = hullColor = Math::vec4(255.0 / 255.0, 180.0 / 255.0, 174.0 / 255.0, 1.0f);

		break;
	}
	case T_VEHICLE_HARD:
	{
		armor = 30.0;
		power = 3.0;
		speed = 0.005;
		torqueVehicle = 0.5;
		torqueTurret = 1.0;
		radarRadius = 7.0;
		shootRange = 5.5;

		sizeHull = Math::vec3(0.4, 0.5, 0.2);
		sizeTurret = Math::vec3(0.17, 0.4, 0.08);

		turretColor = hullColor = Math::vec4(255.0 / 255.0, 180.0 / 255.0, 174.0 / 255.0, 1.0f);

		break;
	}
	default:
		break;
	}
	//create aggregates
	NodePtr ptrHull = createHull(sizeHull, hullColor);
	ptrVehicle->addChild(ptrHull);
	NodePtr ptrTurret = createTurret(sizeTurret, turretColor);
	ptrVehicle->addChild(ptrTurret);

	Math::vec3 turretPos = Math::vec3(0.0, 0.0, sizeHull.z * 0.5 + sizeTurret.z * 0.5 + 0.005);
	ptrTurret->setPosition(turretPos);

	Math::vec3 vehiclePos = Math::vec3(ref_global_radar.getSpawnPosX(), ref_global_radar.getSpawnPosY(), sizeHull.z * 0.5 + 0.05);
	ptrVehicle->setWorldPosition(vehiclePos);

	//create and connect aggregates control components
	CompRotateSystem* ptrCompRotateSystemVehicle = ComponentSystem::get()->addComponent<CompRotateSystem>(ptrVehicle);
	ptrCompRotateSystemVehicle->ptrAggregate = ptrVehicle;
	ptrCompRotateSystemVehicle->torque = torqueVehicle;

	CompMoveSystem* ptrCompMoveSystem = ComponentSystem::get()->addComponent<CompMoveSystem>(ptrVehicle);
	ptrCompMoveSystem->ptrAggregate = ptrVehicle;
	ptrCompMoveSystem->speed = speed;

	CompNavigationSystem* ptrCompNavigationSystem = ComponentSystem::get()->addComponent<CompNavigationSystem>(ptrVehicle);
	ptrCompNavigationSystem->ptrAggregate = ptrVehicle;
	ptrCompNavigationSystem->radarRadius = radarRadius;
	ptrCompNavigationSystem->spawnPoint = vehiclePos;
	if (vehicle_type != T_VEHICLE_PLAYER)
	{
		ptrCompNavigationSystem->addYField(ref_global_radar.getPlayer());
		ptrCompNavigationSystem->ptrTarget = ref_global_radar.getPlayer();
	}

	CompDamageSystem* ptrCompDamageSystem = ComponentSystem::get()->addComponent<CompDamageSystem>(ptrVehicle);
	ptrCompDamageSystem->ptrAggregate = ptrVehicle;
	ptrCompDamageSystem->armor = armor;

	CompRotateSystem* ptrCompRotateSystemTurret = ComponentSystem::get()->addComponent<CompRotateSystem>(ptrTurret);
	ptrCompRotateSystemTurret->ptrAggregate = ptrTurret;
	ptrCompRotateSystemTurret->torque = torqueTurret;

	CompWeaponSystem* ptrCompWeaponSystem = ComponentSystem::get()->addComponent<CompWeaponSystem>(ptrTurret);
	ptrCompWeaponSystem->ptrVehicle = ptrVehicle;
	ptrCompWeaponSystem->ptrAggregate = ptrTurret;
	ptrCompWeaponSystem->power = power;
	ptrCompWeaponSystem->range = shootRange;

	if (vehicle_type != T_VEHICLE_PLAYER)
	{
		CompControlSystemAI* ptrCompControlSystemAI = ComponentSystem::get()->addComponent<CompControlSystemAI>(ptrVehicle);
		ptrCompControlSystemAI->ptrAggregate = ptrVehicle;
		ptrCompControlSystemAI->vehicleType = vehicle_type;
		ptrCompControlSystemAI->ptrHull = ptrHull;
		ptrCompControlSystemAI->ptrTurret = ptrTurret;
	}
	else
	{
		CompControlSystemPlayer* ptrCompControlSystemPlayer = ComponentSystem::get()->addComponent<CompControlSystemPlayer>(ptrVehicle);
		ptrCompControlSystemPlayer->ptrAggregate = ptrVehicle;
		ptrCompControlSystemPlayer->vehicleType = vehicle_type;
		ptrCompControlSystemPlayer->ptrHull = ptrHull;
		ptrCompControlSystemPlayer->ptrTurret = ptrTurret;
	}
}

NodePtr VehicleFactory::createHull(Math::vec3 hull_size, Math::vec4 hull_color)
{
	ObjectMeshDynamicPtr ptrHull = Primitives::createBox(hull_size);

	MaterialPtr ptrBaseMaterial = Materials::loadMaterial("material/vehicle_base.mat");
	ptrHull->setMaterial(ptrBaseMaterial, 0);
	ptrHull->setMaterialParameterFloat4("albedo_color", hull_color, 0);

	Primitives::addBoxSurface(ptrHull, hull_size, Math::mat4_identity);

	ptrHull->setSaveToWorldEnabled(true);
	ptrHull->setShowInEditorEnabled(true);

	return ptrHull;
}
NodePtr VehicleFactory::createTurret(Math::vec3 turret_size, Math::vec4 turret_color)
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

	MaterialPtr ptrBaseMaterial = Materials::loadMaterial("material/vehicle_base.mat");
	ptrTurret->setMaterial(ptrBaseMaterial, 0);
	ptrTurret->setMaterialParameterFloat4("albedo_color", turret_color, 0);

	return ptrTurret;
}

GlobalRadar::GlobalRadar()
{
	ptrPlayer = nullptr;
	spawnPosX = 0.0;
	spawnPosY = 0.0;
}

GlobalRadar::~GlobalRadar()
{
}

NodePtr GlobalRadar::getPlayer()
{
	return ptrPlayer;
}

void GlobalRadar::setPlayer(NodePtr ptr_player)
{
	ptrPlayer = ptr_player;
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
