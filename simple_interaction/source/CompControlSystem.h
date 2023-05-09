#pragma once
#include <UnigineComponentSystem.h>
using namespace Unigine;

class CompControlSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompControlSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Int, vehicleId, 0);
	PROP_PARAM(Int, vehicleType, 0);
	//PROP_PARAM(Float, armor, 0.0);
	//PROP_PARAM(Float, power, 0.0);
	//PROP_PARAM(Float, speed, 0.0);

protected:
	void init();
	void update();
	void shutdown();
};

