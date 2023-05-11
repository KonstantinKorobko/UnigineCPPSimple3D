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
	PROP_PARAM(Int, aggregateId, 0);
	PROP_PARAM(Int, leftYAxis, 0);
	PROP_PARAM(Int, rightYAxis, 0);
	PROP_PARAM(Float, t500, 0);
	PROP_PARAM(Float, radarRadius, 0);
	PROP_PARAM(Vec3, spawnPoint, Math::vec3(0.0));

	//In this method node register in 2-sided list with Y-axis for easy interection on space.
	void addYField(int player_node_id);
	void setPatrolPoint(int radius);

protected:
	void init();
	void update();
	void shutdown();

private:
	NodePtr ptrAggregate;
	CompMoveSystem* ptrCompMoveSystem;

	unsigned int seed;
	std::mt19937 random;

};

