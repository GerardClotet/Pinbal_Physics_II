#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"


ModuleScene::ModuleScene(Application* app, bool start_enable) : Module(app, start_enable)
{

}

ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Start()
{
	bool ret = true;
	Background = App->textures->Load("pinball/board.png");
	ball_texture = App->textures->Load("pinball/ball.png");

	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };

	//Ball def
	ball = App->physics->CreateCircle(425, 16, 8);//Position only ajusted to x axis because impluse bige is not implemented yet
	ball->body->SetBullet(true);
	ball->listener = this;
	return ret;
}

update_status ModuleScene::Update()
{
	ball->GetPosition(ball_position.x, ball_position.y);

	App->renderer->Blit(Background, 0, 0, &up_part);
	App->renderer->Blit(Background, 0, 689, &down_part);
	App->renderer->Blit(ball_texture, ball_position.x, ball_position.y);



	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	return true;
}

