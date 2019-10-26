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
	backgroundphys = App->physics->CreateChain(0, 0, Board, 56, true);
	//leftBigWall = App->physics->CreateChain(0, 0, LeftBigWall, 14, true);
	/*leftMediumWall = App->physics->CreateChain(0, 0, LeftMediumWall, 16, true);
	leftLittleWall = App->physics->CreateChain(0, 0, LeftLittleWall, 22, true);

	rightBigWall = App->physics->CreateChain(0, 0, RightBigWall, 2, true);
	rightMediumWall = App->physics->CreateChain(0, 0, RightMediumWall, 14, true);
	rightLittleWall = App->physics->CreateChain(0, 0, RightSmallWall, 14, true);*/

	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };

	//Ball def
	ball = App->physics->CreateCircle(425, 16, 8);//Position only ajusted to x axis because impluse bige is not implemented yet
	ball->body->SetBullet(true);
	ball->listener = this;

	//Balk that impluses the ball
	Balk = App->physics->CreateRectangle(425, 635, 8, 46);

	b2MouseJointDef def;
	def.bodyA = App->physics->ground;
	def.bodyB = Balk->body;

	//backgroundphys = App->physics->CreateChain(0, 0, Board, 56, true);

	//flippers

	flipper1 = App->physics->CreateFlippers(100, 50);
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

