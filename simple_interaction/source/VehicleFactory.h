#pragma once
#include <UnigineNodes.h>
#include <UnigineVisualizer.h>
#include <UnigineConsole.h>
#include <UnigineComponentSystem.h>
using namespace Unigine;

class GlobalRadar
{
public:
	GlobalRadar();
	~GlobalRadar();

	int getPlayerId();
	void setPlayerId(int node_id);
private:
	int playerId;
};

class VehicleFactory
{
public:
	enum VehicleType
	{
		T_VEHICLE_PLAYER,
		T_VEHICLE_LIGHT,
		T_VEHICLE_MIDDLE,
		T_VEHICLE_HARD
	};

	static void constructVehicle(int vehicle_type, GlobalRadar& ref_radar);
private:
	static NodePtr createHull(Math::vec3 hull_size);
	static NodePtr createTurret(Math::vec3 turret_size);
};
