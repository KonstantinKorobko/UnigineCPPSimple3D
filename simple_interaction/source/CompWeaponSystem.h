/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
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
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Node, ptrTarget);
	PROP_PARAM(Float, power, 0.0);
	PROP_PARAM(Float, range, 0.0);
	PROP_PARAM(Float, tReload, 0.0);

	//PROP_PARAM(Int, numAmmo, 0);//?

protected:
	void init();
	void update();
	void shutdown();

private:
	CompRotateSystem* ptrCompRotateSystem;

/*
* [0]	rotation vector X
* [1]	rotation vector Y
* [2]	distance
*/
	float calcBuffer[3];
	void calcData();

	//simple missile factory
	void fire(int missile_type = 0);
};

