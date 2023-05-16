/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
#include "CompNavigationSystem.h"
using namespace Unigine;

class CompControlSystemPlayer :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompControlSystemPlayer, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Int, aggregateId, 0);
	PROP_PARAM(Int, vehicleType, 0);
	PROP_PARAM(Float, t15, 0);

protected:
	NodePtr ptrAggregate;

	void init();
	void update();
	void shutdown();

	CompNavigationSystem* ptrCompNavigationSystem;
};
