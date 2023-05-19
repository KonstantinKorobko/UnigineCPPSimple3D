/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
#include "CompMoveSystem.h"
#include "CompRotateSystem.h"
using namespace Unigine;

class CompWeaponSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompWeaponSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Node, ptrVehicle);
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Node, ptrTarget);
	PROP_PARAM(Float, power, 0.0);
	PROP_PARAM(Float, range, 0.0);
	PROP_PARAM(Float, t_Reload, 0.0);

	//PROP_PARAM(Int, numAmmo, 0);//?

protected:
	void init();
	void update();
	void shutdown();

private:
	CompRotateSystem* ptrCompRotateSystem;
	CompMoveSystem* ptrCompMoveSystem;

/*
* [0]	rotation vector X
* [1]	rotation vector Y
* [2]	distance
*/
	float calcBuffer[3];
	void calcData();

	//simple missile factory
	void shoot(int missile_type = 0);
};

