#ifndef  _MODULE_SCORE_
#define _MODULE_SCORE_
#include "Module.h"
#include "Application.h"

#define MAXDIGITS 6

class ModuleScore : public Module
{
public:
	ModuleScore(Application* app, bool start_enabled = true);
	~ModuleScore();

	SDL_Texture* Score_text;
	SDL_Texture* font;
	SDL_Texture* lives_tex;
	SDL_Rect numbers[10];
	SDL_Rect live_text;
	SDL_Rect textScr;
	int score = 0;
	int lives = 5;
	int prevScore;
	int digits[MAXDIGITS] = { -1,-1,-1,-1,-1,0 };
	int prevdigit[MAXDIGITS] = { -1,-1,-1,-1,-1,0 };

	int live_digit[1] = { 5 };


	bool Start();
	update_status Update();
	bool CleanUp();

	void IncreaseS(int points);
	void IncreaseLive(int points);
	void ResetLives();
	int GetLife();
	void Finish();
};


#endif // ! _MODULE_SCORE_