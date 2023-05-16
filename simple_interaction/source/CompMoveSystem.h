/*
* @author  Konstantin Korobko
*/
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
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Float, speed, 0.0);
	PROP_PARAM(Float, tolerance, 0.0);
	PROP_PARAM(Vec3, setpoint, Math::vec3(0.0));

	float getDistance();

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
	void calcMoveData();
};

