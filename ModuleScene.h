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
class SDL_Rect;

class ModuleScene :public Module

{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();


	bool Start();
	update_status Update();
	bool CleanUp();
public:
	PhysBody* ball;
	PhysBody* Balk;

	iPoint ball_position;

	SDL_Texture* Background = nullptr;
	SDL_Texture* ball_texture = nullptr;
	SDL_Texture* balk_texture = nullptr;

	SDL_Rect up_part;
	SDL_Rect down_part;
};

#endif