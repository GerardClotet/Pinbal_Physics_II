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
	SDL_Rect numbers[10];
	SDL_Rect textScr;
	int score = 0;
	int prevScore;
	int digits[MAXDIGITS] = { -1,-1,-1,-1,-1,0 };
	int prevdigit[MAXDIGITS] = { -1,-1,-1,-1,-1,0 };



	bool Start();
	update_status Update();
	bool CleanUp();

	void Increase(int points);
	void Finish();
};


#endif // ! _MODULE_SCORE_