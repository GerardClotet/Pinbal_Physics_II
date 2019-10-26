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


	return ret;
}

update_status ModuleScene::Update()
{

	App->renderer->Blit(Background, 0, 0);



	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	return true;
}

