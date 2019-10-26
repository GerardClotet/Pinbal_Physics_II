#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)
enum Type {
	COLLIDER,
	PLATFORM,
	BALL,
	FLIPPER,
	REDBUMBPER1,
	REDBUMBPER2,
	REDBUMBPER3,
	REDBUMBPER4,
	REDBUMBPER5,
	REDBUMBPER6,
	REDBUMBPER7,
	YELLOWBUMPER,
	BALK,
	START,
	GAMEOVER,
	SPINNER
};
class b2Body;
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	Type type;

};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, bool static_body = false);
	PhysBody* CreateRectangle(int x, int y, int width, int height, bool static_body = false);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, Module* listener, bool static_body = false);
	PhysBody* CreateChain(int x, int y, int* points, int size, bool static_body = false);


	PhysBody* CreateFlippers(int x, int y, bool flipXaxis);
	PhysBody* CreateLittleFlippers(int x, int y, bool flipXaxis);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;
	b2Body* ground;

	// Mouse joint
	b2MouseJoint* mouse_joint;
	b2Body* body_clicked;
private:

	bool debug;
	
};