#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainVertex.h"


ModuleScene::ModuleScene(Application* app, bool start_enable) : Module(app, start_enable)
{

}

ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Start()
{
	bool ret = true;
	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };
	bigRightFlipper = { 283,249,46,31 };

	Background = App->textures->Load("pinball/board.png");
	ball_texture = App->textures->Load("pinball/ball.png");
	balk_texture = App->textures->Load("pinball/balk.png");
	map_Sprites = App->textures->Load("pinball/Start Barrier.png");

	//Colliders


	backgroundphys = App->physics->CreateChain(0, 0, Board, 68, true);
	leftStartWall = App->physics->CreateChain(0, 0, LeftStartWall, 14, true);	//leftBigWall = App->physics->CreateChain(0, 0, LeftBigWall, 14, true);
	/*leftBigWall = App->physics->CreateChain(0, 0, LeftBigWall, 14, true);
	leftMediumWall = App->physics->CreateChain(0, 0, LeftMediumWall, 16, true);
	leftLittleWall = App->physics->CreateChain(0, 0, LeftLittleWall, 22, true);

	rightBigWall = App->physics->CreateChain(0, 0, RightBigWall, 10, true);
	rightMediumWall = App->physics->CreateChain(0, 0, RightMediumWall, 14, true);
	rightLittleWall = App->physics->CreateChain(0, 0, RightSmallWall, 14, true);
*/
	rightExtraSmallWall = App->physics->CreateChain(0, 0, RightExtraSmallWall, 22, true);
	plat1 = App->physics->CreateChain(0, 0, Plat1, 18, true);
	plat2 = App->physics->CreateChain(0, 0, Plat2, 18, true);
	plat3 = App->physics->CreateChain(0, 0, Plat3, 18, true);
	plat4 = App->physics->CreateChain(0, 0, Plat4, 42, true);

	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };

	//Ball def
	ball = App->physics->CreateCircle(424, 620, 8);
	ball->body->SetBullet(true);
	ball->listener = this;

	//Balk that impluses the ball
	Balk = App->physics->CreateRectangle(425, 635, 8, 46);

	b2MouseJointDef def;
	def.bodyA = App->physics->ground;
	def.bodyB = Balk->body;

	def.target = { PIXEL_TO_METERS(425), PIXEL_TO_METERS(640) };
	def.dampingRatio = 2.0f;
	def.maxForce = 1000.0f * Balk->body->GetMass();
	balk_joint = (b2MouseJoint*)App->physics->world->CreateJoint(&def);

	//flippers

	flipper1 = App->physics->CreateFlippers(200, 160);
	return ret;
}

update_status ModuleScene::Update()
{
	ball->GetPosition(ball_position.x, ball_position.y);
	Balk->GetPosition(balk_poisiton.x, balk_poisiton.y);

	App->renderer->Blit(Background, 0, 0, &up_part);
	App->renderer->Blit(Background, 0, 689, &down_part);
	App->renderer->Blit(ball_texture, ball_position.x, ball_position.y);
	App->renderer->Blit(balk_texture, balk_poisiton.x, balk_poisiton.y);

	int x, y;
	flipper1->GetPosition(x, y);
	App->renderer->Blit(map_Sprites, x, y, &bigRightFlipper, 1.0f, flipper1->GetRotation());
	//Player Controls

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		balk_joint->SetTarget({ PIXEL_TO_METERS(425), PIXEL_TO_METERS(735) });
		balk_joint->SetFrequency(1.0f);

	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) {
		balk_joint->SetTarget({ PIXEL_TO_METERS(425), PIXEL_TO_METERS(635) });
		balk_joint->SetFrequency(20.0f);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper1->body->ApplyTorque(500, true);
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	return true;
}

