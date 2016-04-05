#include "SmartBombControl.h"

#include "SystemManager.h"
#include "AssetManager.h"
#include "Entity.h"

SmartBombControl()
{
	systemManager = nullptr;
	assetManager = nullptr;
}

SmartBombControl(SystemManager *s, AssetManager *a)
{
	systemManager = s;
	assetManager = a;
}

~SmartBombControl()
{
}

control(Entity *e)
{
	Property *p = e->getComponent("OuterBoundingBox");
	//check for explosion collision with outer bounding box.
	//If 0, don't do anything.
	//If -1, it means its to the left. Move right.
	//If 1, its to the right. Move left.
	//Move in the opposite direction.
}