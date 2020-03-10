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
	Gdiplus::Font font(&fontFamily, 64);

	SolidBrush pink(Color(1, 206, 209));

	wstring score = L"$" + to_wstring(GetScore());

	wstring wide_string = wstring(score.begin(), score.end());
	const wchar_t* result = wide_string.c_str();

	auto Game = GetGame();
	auto Player = Game->GetPlayer();
	auto PlayerX = Player->GetX() + 450;

	graphics->DrawString(result, -1, &font, PointF(PlayerX, 10), &pink);
}

const wstring ScoreboardImageName = L"images/grass.png";

/**
 * Constructor for the scoreboard 
 * \param game the game the scoreboard is being added to
 */
CScoreboard::CScoreboard(CGame* game) :
	CElement(game, ScoreboardImageName)
{
	SetLocation(0, 0);
}

/**
 * update function for the scoreboard
 * \param elapsed amount of time elapsed since the last update
 * given in milliseconds
 */
void CScoreboard::Update(double elapsed)
{	
	auto game = GetGame();
	int score = GetScore();
	game->SetScore(score);
}
