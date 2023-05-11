/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
using namespace Unigine;

class CompRotateSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompRotateSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Int, aggregateId, 0);
	PROP_PARAM(Float, torque, 0.0);
	PROP_PARAM(Vec3, rotateVec, Math::vec3(0.0));

protected:
	void init();
	void update();
	void shutdown();

private:
	NodePtr ptrAggregate;

	float calcTorque();
};

