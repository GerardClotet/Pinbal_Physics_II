#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ChainVertex.h"
#include "ModuleScore.h"

ModuleScene::ModuleScene(Application* app, bool start_enable) : Module(app, start_enable)
{

}

ModuleScene::~ModuleScene()
{
}


bool ModuleScene::Start()
{
	bool ret = true;
	App->renderer->camera.x = App->renderer->camera.y = 0;

	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };
	arraynum = { 0,1,185,21 };

	//Loading tex
	Background = App->textures->Load("pinball/board.png");
	ball_texture = App->textures->Load("pinball/ball.png");
	balk_texture = App->textures->Load("pinball/balk.png");
	bigleftflipper = App->textures->Load("pinball/bigflipperleft.png");
	bigrightflipper = App->textures->Load("pinball/flipper.png");
	littleleftflipper = App->textures->Load("pinball/littleflipperLeft.png");
	littlerigthflipper = App->textures->Load("pinball/littleflipperRight.png");
	yellowBumper = App->textures->Load("pinball/yellowBumper.png");
	redBumper = App->textures->Load("pinball/redBumper.png");
	blueBumper = App->textures->Load("pinball/blueBumper.png");
	reStart = App->textures->Load("pinball/restart.png");

	//Loading Audio
	flipper_fx = App->audio->LoadFx("pinball/audio/fx/flipper_audio.wav");
	balk_fx = App->audio->LoadFx("pinball/audio/fx/balkSound.wav");
	bumper_fx = App->audio->LoadFx("pinball/audio/fx/bumpersound.wav");
	spawn_ball_fx = App->audio->LoadFx("pinball/audio/fx/spawnballsound.wav");
	dead_ball_fx = App->audio->LoadFx("pinball/audio/fx/deadball.wav");

	App->audio->PlayMusic("pinball/audio/music/music.ogg",-1);

//Colliders
	backgroundphys = App->physics->CreateChain(0, 0, Board, 82, true);
	backgroundphys->type = COLLIDER;
	leftBigWall = App->physics->CreateChain(0, 0, LeftBigWall, 14, true);
	leftBigWall->type = COLLIDER;
	leftMediumWall = App->physics->CreateChain(0, 0, LeftMediumWall, 16, true);
	leftMediumWall->type = COLLIDER;
	leftLittleWall = App->physics->CreateChain(0, 0, LeftLittleWall, 22, true);
	leftLittleWall->type = COLLIDER;
	rightBigWall = App->physics->CreateChain(0, 0, RightBigWall, 10, true);
	rightBigWall->type = COLLIDER;
	rightMediumWall = App->physics->CreateChain(0, 0, RightMediumWall, 14, true);
	rightMediumWall->type = COLLIDER;
	rightLittleWall = App->physics->CreateChain(0, 0, RightSmallWall, 14, true);
	rightLittleWall->type = COLLIDER;
	rightExtraSmallWall = App->physics->CreateChain(0, 0, RightExtraSmallWall, 22, true);
	rightExtraSmallWall->type = COLLIDER;
	plat1 = App->physics->CreateChain(0, 0, Plat1, 18, true);
	plat1->type = PLATFORM;
	plat2 = App->physics->CreateChain(0, 0, Plat2, 18, true);
	plat2->type = PLATFORM;
	plat3 = App->physics->CreateChain(0, 0, Plat3, 18, true);
	plat3->type = PLATFORM;
	plat4 = App->physics->CreateChain(0, 0, Plat4, 42, true);
	plat4->type = PLATFORM;


	//Circle Bumpers

	circlesBumper[1] = App->physics->CreateCircle(130, 185, 15, true);
	circlesBumper[1]->type = REDBUMBPER1;
	circlesBumper[1]->body->ApplyAngularImpulse(10.0f, true);
	circlesBumper[2] = App->physics->CreateCircle(192, 185, 15, true);
	circlesBumper[2]->type = REDBUMBPER2;
	circlesBumper[3] = App->physics->CreateCircle(252, 185, 15, true);
	circlesBumper[3]->type = REDBUMBPER3;
	circlesBumper[4] = App->physics->CreateCircle(312, 185, 15, true);
	circlesBumper[4]->type = REDBUMBPER4;
	circlesBumper[5] = App->physics->CreateCircle(132, 254, 15, true);
	circlesBumper[5]->type = REDBUMBPER5;
	circlesBumper[6] = App->physics->CreateCircle(273, 268, 15, true);
	circlesBumper[6]->type = REDBUMBPER6;
	circlesBumper[7] = App->physics->CreateCircle(144, 315, 15, true);
	circlesBumper[7]->type = REDBUMBPER7;

	up_part = { 0,0,483,689 };
	down_part = { 0,757,483,115 };

	//Ball def
	ball = App->physics->CreateCircle(424, 620, 7);
	ball->type = BALL;
	ball->body->SetBullet(true);
	ball->listener = this;

	ball2 = App->physics->CreateCircle(340, 245, 7);
	ball2->type = BALL2;
	ball2->body->SetBullet(true);
	ball2->listener = this;
	ball2->body->SetActive(false);

	//Balk that impluses the ball
	Balk = App->physics->CreateRectangle(425, 664, 8, 46);
	Balk->type = BALK;
	Balk->body->SetFixedRotation(true);

	//Rectangle sensor

	GameOverSensor = App->physics->CreateRectangleSensor(242, 840, 483, 300, ball->listener, true);
	GameOverSensor->type = GAMEOVER;

	StartSensor = App->physics->CreateRectangleSensor(410, 350, 44, 10, ball->listener, true);
	StartSensor->type = START;

	DropRectangleBall = App->physics->CreateRectangleSensor(345, 260, 44, 10, ball->listener, true);
	DropRectangleBall->type = SBALL;

	//Bumpers
	StartBumper = App->physics->CreateChain(0, 0, StartYellowBumper, 10, true);
	yellowLeft = App->physics->CreateChain(0, 0, leftYellowBumper, 10, true);
	yellowRight = App->physics->CreateChain(0, 0, rightYellowBumper, 10, true);

	b2MouseJointDef def;
	def.bodyA = App->physics->ground;
	def.bodyB = Balk->body;

	def.target = { PIXEL_TO_METERS(425), PIXEL_TO_METERS(640) };
	def.dampingRatio = 0.06f;
	def.maxForce = 100000.0f * Balk->body->GetMass();
	balk_joint = (b2MouseJoint*)App->physics->world->CreateJoint(&def);


	
	//flippers

	flipperBigRight = App->physics->CreateFlippers(283, 612, true); //right
	flipperBigRight->type = FLIPPER;
	flipperBigLeft = App->physics->CreateFlippers(172, 615, false); //left y615

	flipperBigLeft->type = FLIPPER;
	flipperLittleRight = App->physics->CreateLittleFlippers(295, 558, true);//right
	flipperLittleRight->type = FLIPPER;
	flipperLittleLeft = App->physics->CreateLittleFlippers(160, 563, false);//left
	flipperLittleLeft->type = FLIPPER;


	//Wheel
	/*Wheel = App->physics->CreateChain(-25, 250, wheel, 86, true);
	Wheel->body->SetActive(false);
	WheelPivot = App->physics->CreateCircle(258, 333, 10, false);
	Wheel->type = SPINNER;
*/
	// tried to implement the rotative movment to the wheel but  couldnt due to lack of time
	/*b2RevoluteJointDef jointDef;
	jointDef.bodyA = Wheel->body;
	jointDef.bodyB = WheelPivot->body;
	jointDef.localAnchorA = { PIXEL_TO_METERS(258), PIXEL_TO_METERS(333) };
	jointDef.localAnchorB = { 258,333};
	jointDef.lowerAngle = 0.0f;
	jointDef.upperAngle = 0.0f;
	jointDef.enableLimit = true;
	jointDef.collideConnected = false;
	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 100.0f;
	jointDef.motorSpeed = 5.0f;*/

	return ret;
}

update_status ModuleScene::Update()
{
	if (decrease_live)
	{
		
			App->score->IncreaseLive(-1);
			decrease_live = false;

			if (App->score->GetLife() == 0)
			{
				LOG("%i", App->score->GetLife());
				DeadPlayer = true;
			}
		
	}

	ball->GetPosition(ball_position.x, ball_position.y);
	Balk->GetPosition(balk_poisiton.x, balk_poisiton.y);

	App->renderer->Blit(Background, 0, 689, &down_part);
	App->renderer->Blit(Background, 0, 0, &up_part);

	App->renderer->Blit(ball_texture, ball_position.x, ball_position.y);
	App->renderer->Blit(balk_texture, balk_poisiton.x, balk_poisiton.y);
	if (!DeadPlayer)
	{
		if (StartBumperActive == true) {
			StartBumper->body->SetActive(true);
			App->renderer->Blit(yellowBumper, startBumperPosition.x, startBumperPosition.y);

		}
		else StartBumper->body->SetActive(false);

		if (changeCircle1Colore == true)App->renderer->Blit(blueBumper, 118, 170);
		if (changeCircle1Colore == false)App->renderer->Blit(redBumper, 118, 170);

		if (changeCircle2Colore == true)App->renderer->Blit(blueBumper, 178, 170);
		if (changeCircle2Colore == false)App->renderer->Blit(redBumper, 178, 170);

		if (changeCircle3Colore == true)App->renderer->Blit(blueBumper, 238, 170);
		if (changeCircle3Colore == false)App->renderer->Blit(redBumper, 238, 170);

		if (changeCircle4Colore == true)App->renderer->Blit(blueBumper, 298, 170);
		if (changeCircle4Colore == false)App->renderer->Blit(redBumper, 298, 170);

		if (changeCircle5Colore == true)App->renderer->Blit(blueBumper, 118, 240);
		if (changeCircle5Colore == false)App->renderer->Blit(redBumper, 118, 240);

		if (changeCircle6Colore == true)App->renderer->Blit(blueBumper, 259, 253);
		if (changeCircle6Colore == false)App->renderer->Blit(redBumper, 259, 253);

		if (changeCircle7Colore == true)App->renderer->Blit(blueBumper, 130, 300);
		if (changeCircle7Colore == false)App->renderer->Blit(redBumper, 130, 300);



		int x, y;
		ball2->GetPosition(x, y);
		if (SecondBallActive == true)
		{
			ball2->body->SetActive(true);
			App->renderer->Blit(ball_texture, x, y);
			DropRectangleBall->body->SetActive(false);
		}
		else {
			ball2->body->SetActive(false);
			DropRectangleBall->body->SetActive(true);
		}

		//bliting flippers
		flipperBigRight->GetPosition(x, y);
		App->renderer->Blit(bigrightflipper, x, y, NULL, 1.0f, flipperBigRight->GetRotation(), false);

		flipperBigLeft->GetPosition(x, y);
		App->renderer->Blit(bigleftflipper, x, y, NULL, 1.0f, flipperBigLeft->GetRotation(), true); //take true out to avoid vibration

		flipperLittleRight->GetPosition(x, y);
		App->renderer->Blit(littlerigthflipper, x, y, NULL, 1.0f, flipperLittleRight->GetRotation(), false);

		flipperLittleLeft->GetPosition(x, y);
		App->renderer->Blit(littleleftflipper, x, y, NULL, 1.0f, flipperLittleLeft->GetRotation(), true);

		//Player Controls
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN))
		{
			App->audio->PlayFx(flipper_fx, 0);
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			balk_joint->SetTarget({ PIXEL_TO_METERS(425), PIXEL_TO_METERS(675) });
			balk_joint->SetFrequency(1.0f);

		}
		else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) {
			balk_joint->SetTarget({ PIXEL_TO_METERS(425), PIXEL_TO_METERS(635) });
			balk_joint->SetFrequency(10.0f);
			App->audio->PlayFx(balk_fx, 0);

		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			flipperBigRight->body->ApplyTorque(200, true);
			flipperLittleRight->body->ApplyTorque(190, true);
		}
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			flipperBigLeft->body->ApplyTorque(-200, true);
			flipperLittleLeft->body->ApplyTorque(-190, true);
		}

	}
	else {
		App->renderer->Blit(reStart, 0, 0);
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			App->score->ResetLives();
			App->score->Finish();
			DeadPlayer = false;
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	return true;
}

void ModuleScene::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;
	changeCircle1Colore = false;
	changeCircle2Colore = false;
	changeCircle3Colore = false;
	changeCircle4Colore = false;
	changeCircle5Colore = false;
	changeCircle6Colore = false;
	changeCircle7Colore = false;
	if (bodyB->type == BALL && bodyA->type == GAMEOVER)
	{
		ball->body->SetTransform({ PIXEL_TO_METERS(424),PIXEL_TO_METERS(620) }, ball->GetRotation());
		App->audio->PlayFx(dead_ball_fx, 0);
		StartBumperActive = false;
		StartSensor->body->SetActive(true);
		decrease_live = true;
	}
	if (bodyB->type == BALL2 && bodyA->type == GAMEOVER) {

		ball2->body->SetTransform({ PIXEL_TO_METERS(340), PIXEL_TO_METERS(245) }, ball->GetRotation());
		App->audio->PlayFx(dead_ball_fx, 0);

		SecondBallActive = false;
		decrease_live = true;

	}

	if (bodyA->type == START) {

		StartBumperActive = true;
		StartSensor->body->SetActive(false);

	}

	if (bodyB->type == REDBUMBPER1) {
		changeCircle1Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);


	}
	if (bodyB->type == REDBUMBPER2) {
		changeCircle2Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);


	}
	if (bodyB->type == REDBUMBPER3) {
		changeCircle3Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);


	}
	if (bodyB->type == REDBUMBPER4) {
		changeCircle4Colore = true;
		App->audio->PlayFx(bumper_fx, 0);

		App->score->IncreaseS(+100);

	}
	if (bodyB->type == REDBUMBPER5) {
		changeCircle5Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);


	}
	if (bodyB->type == REDBUMBPER6) {
		changeCircle6Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);


	}
	if (bodyB->type == REDBUMBPER7) {
		changeCircle7Colore = true;
		App->score->IncreaseS(+100);
		App->audio->PlayFx(bumper_fx, 0);

	}

	

}

