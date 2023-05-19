/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
using namespace Unigine;

class CompDamageSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompDamageSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Float, armor, 0.0);
	PROP_PARAM(Float, t0_2, 0);
	PROP_PARAM(Float, damageAdd, 0);

protected:
	void init();
	void update();
	void shutdown();

private:
};

