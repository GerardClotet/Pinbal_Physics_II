#ifndef  MODULE_SCENE
#define MODULE_SCENE

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

class SDL_Texture;
class PhysBody;
class b2RevoluteJoint;
class b2DistanceJoint;
class b2Contact;


class ModuleScene :public Module

{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();


	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* Background = nullptr;


};

#endif