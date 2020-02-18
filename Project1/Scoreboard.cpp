#include "pch.h"
#include "Scoreboard.h"
#include <memory>
#include <string>
#include "Visitor.h"

using namespace Gdiplus;
using namespace std;

/**
 * Getter getting the score of the game from mGame 
 * \returns score the current score of the game
 */
int CScoreboard::GetScore()
{
	auto game = GetGame();
	int score = game->GetScore();
	return score;
}


/**
 * Draws the scoreboard with the amount of points the user has.
 * \param graphics the graphics tool used to draw the scoreboard.
 */
void CScoreboard::Draw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 32);

	SolidBrush green(Color(0, 64, 0));

	string score ="$" + to_string(GetScore());

	wstring wide_string = wstring(score.begin(), score.end());
	const wchar_t* result = wide_string.c_str();


	graphics->DrawString(result, -1, &font, PointF(1000, 10), &green);
}

const wstring ScoreboardImageName = L"images/grass.png";

/**
 * Constructor for the scoreboard 
 * \param game the game the scoreboard is being added to
 */
CScoreboard::CScoreboard(CGame* game) :
	CElement(game, ScoreboardImageName)
{
}

/**
 * update function for the scoreboard
 * \param elapsed amount of time elapsed since the last update
 * given in milliseconds
 */
void CScoreboard::Update(double elapsed)
{	
	auto game = GetGame();
	CPlayer player(game);

	auto itemDists = game->ItemDistances(&player);

	double score = GetScore();
	for (auto itemDist : itemDists)
	{
		score += itemDist;
	}
	game->SetScore(score);
}
