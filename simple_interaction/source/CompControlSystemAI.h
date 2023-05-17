/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
#include "CompNavigationSystem.h"
#include "CompMoveSystem.h"
#include "CompWeaponSystem.h"
using namespace Unigine;

class CompControlSystemAI :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompControlSystemAI, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Node, ptrHull);
	PROP_PARAM(Node, ptrTurret);
	PROP_PARAM(Int, vehicleType, 0);
	PROP_PARAM(Float, t15, 0);

protected:
	void init();
	void update();
	void shutdown();

private:
	CompNavigationSystem* ptrCompNavigationSystem;
	CompMoveSystem* ptrCompMoveSystem;
	CompWeaponSystem* ptrCompWeaponSystem;
};

