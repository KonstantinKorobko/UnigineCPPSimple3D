/*
* @author  Konstantin Korobko
*/
#include "CompMoveSystem.h"
using namespace Unigine;

class CompControlSystemMissile :
    public ComponentBase
{
public:
	COMPONENT_DEFINE(CompControlSystemMissile, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	//container node id
	PROP_PARAM(Node, ptrAggregate);
	PROP_PARAM(Node, ptrTarget);
	PROP_PARAM(Float, damage, 0.0);
	PROP_PARAM(Float, lifeTime, 0);

protected:
	void init();
	void update();
	void shutdown();

private:
	CompMoveSystem* ptrCompMoveSystem;
};

