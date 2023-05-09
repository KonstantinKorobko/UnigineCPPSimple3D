#pragma once
#include <UnigineComponentSystem.h>
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
	PROP_PARAM(Int, leftTargetId, 0);
	PROP_PARAM(Int, rightTargetId, 0);

protected:
	void init();
	void update();
	void shutdown();
private:
	NodePtr ptrAggregate;
};

