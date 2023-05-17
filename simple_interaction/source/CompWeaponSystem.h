/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
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

	PROP_PARAM(Int, numAmmo, 0);

protected:
	void init();
	void update();
	void shutdown();

private:
};

