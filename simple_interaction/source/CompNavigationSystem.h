/*
* @author  Konstantin Korobko
*/
#pragma once
#include <UnigineComponentSystem.h>
#include "CompMoveSystem.h"
#include <random>

using namespace Unigine;

class CompNavigationSystem :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompNavigationSystem, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Node, ptrLeftYAxis);
	PROP_PARAM(Node, ptrRightYAxis);
	PROP_PARAM(Node, ptrTarget);
	PROP_PARAM(Float, t1, 0);
	PROP_PARAM(Float, radarRadius, 0);
	PROP_PARAM(Float, shootRange, 0);
	PROP_PARAM(Vec3, spawnPoint, Math::vec3(0.0));

	//In this method node register in 2-sided list with Y-axis for easy interection on space.
	void addYField(NodePtr ptr_player);
	void setPatrolPoint(int radius);
	void setClotherTarget();

protected:
	void init();
	void update();
	void shutdown();

private:
	CompMoveSystem* ptrCompMoveSystem;

	unsigned int seed;
	std::mt19937 random;

	float targetDistance;
};

