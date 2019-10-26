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

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	//Colliders
	PhysBody* backgroundphys;
	PhysBody* leftStartWall;
	PhysBody* leftBigWall;
	PhysBody* leftMediumWall;
	PhysBody* leftLittleWall;
	PhysBody* LeftExtraWall;
	PhysBody* rightBigWall;
	PhysBody* rightMediumWall;
	PhysBody* rightLittleWall;
	PhysBody* rightExtraSmallWall;
	PhysBody* plat1;
	PhysBody* plat2;
	PhysBody* plat3;
	PhysBody* plat4;
	PhysBody* ball;
	PhysBody* ball2;
	PhysBody* Balk;
	PhysBody* flipperBigRight;
	PhysBody* flipperBigLeft;
	PhysBody* flipperLittleLeft;
	PhysBody* flipperLittleRight;
	PhysBody* StartBumper;
	PhysBody* StartSensor;
	PhysBody* GameOverSensor;
	PhysBody* circlesBumper[7];
	PhysBody* yellowRight;
	PhysBody* yellowLeft;
	PhysBody* DropRectangleBall;

	iPoint ball_position;
	iPoint balk_poisiton;
	iPoint startBumperPosition = { 410,350 };


	SDL_Texture* Background = nullptr;
	SDL_Texture* ball_texture = nullptr;
	SDL_Texture* balk_texture = nullptr;
	SDL_Texture* bigleftflipper = nullptr;
	SDL_Texture* bigrightflipper = nullptr;
	SDL_Texture* littlerigthflipper = nullptr;
	SDL_Texture* littleleftflipper = nullptr;
	SDL_Texture* redBumper = nullptr;
	SDL_Texture* blueBumper = nullptr;
	SDL_Texture* yellowBumper = nullptr;

	SDL_Rect up_part;
	SDL_Rect down_part;
	SDL_Rect arraynum;


	b2MouseJoint* balk_joint;

	bool StartBumperActive = false;
	bool changeCircle1Colore = false;
	bool changeCircle2Colore = false;
	bool changeCircle3Colore = false;
	bool changeCircle4Colore = false;
	bool changeCircle5Colore = false;
	bool changeCircle6Colore = false;
	bool changeCircle7Colore = false;
	bool SecondBallActive = false;

};

#endif