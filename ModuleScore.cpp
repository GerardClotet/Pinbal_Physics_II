#include "Application.h"
#include "Globals.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleScene.h"
#include "ModuleScore.h"
#include"ModulePhysics.h"
ModuleScore::ModuleScore(Application* app, bool start_enabled) : Module(app, start_enabled)
{}


ModuleScore::~ModuleScore()
{}


bool ModuleScore::Start()
{
	numbers[0] = { 1,1,20,21 };
	numbers[1] = { 25,1,13,21 };
	numbers[2] = { 44,1,19,21 };
	numbers[3] = { 66,1,17,21 };
	numbers[4] = { 85,1,21,21 };
	numbers[5] = { 108,1,17,21 };
	numbers[6] = { 129,1,19,21 };
	numbers[7] = { 151,1,18,21 };
	numbers[8] = { 172,1,18,21 };
	numbers[9] = { 193,1,20,21 };

	textScr = { 2,1,110,35 };
	font = App->textures->Load("pinball/font.png");
	Score_text = App->textures->Load("pinball/Score.png");
	return true;
}

update_status ModuleScore::Update()
{
	if (App->physics->type != GAMEOVER)
	{
		int x = 140;
		int y = 750;

		for (int i = 5; i > 0; i--)
		{
			if (digits[i] != -1)
			{
				App->renderer->Blit(font, x, y, &numbers[digits[i]]);
				x -= 15;
			}
		}
	}

	App->renderer->Blit(Score_text, 50, 700, &textScr);
	return UPDATE_CONTINUE;
}


void ModuleScore::Increase(int points)
{
	score += points;

	int index = 5;
	int auxScore = score;

	while (auxScore > 0)

	{
		int num = auxScore % 10;
		auxScore /= 10;

		digits[index] = num;
		index--;
	}
}

void ModuleScore::Finish()
{
	prevScore = score;

	int index = 5;
	int auxScore = prevScore;
	while (auxScore > 0)
	{
		int num = auxScore % 10;
		auxScore /= 10;
		prevdigit[index] = num;
		index--;
	}

	score = 0;

	digits[0] = -1;
	digits[1] = -1;
	digits[2] = -1;
	digits[3] = -1;
	digits[4] = -1;
	digits[5] = -0;
}


bool ModuleScore::CleanUp()
{
	return true;
}