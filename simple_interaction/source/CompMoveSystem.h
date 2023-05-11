#pragma once
#include <UnigineComponentSystem.h>
#include "CompRotateSystem.h"
using namespace Unigine;

class CompMoveSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompMoveSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Int, aggregateId, 0);
	PROP_PARAM(Float, speed, 0.0);
	PROP_PARAM(Vec3, setpoint, Math::vec3(0.0));

protected:
	void init();
	void update();
	void shutdown();
private:
	NodePtr ptrAggregate;

	Math::vec3 getRotationVec();

	CompRotateSystem* ptrCompRotateSystem;
};

