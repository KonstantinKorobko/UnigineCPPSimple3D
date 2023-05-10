#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>
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

	//In this method node register in 2-sided list sorted with Y-axis for easy interection on space.
	void addYField(int player_node_id);

protected:
	void init();
	void update();
	void shutdown();
private:
	NodePtr ptrAggregate;
};

