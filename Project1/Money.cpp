#include "pch.h"
#include "Money.h"
#include "DoubleBufferDC.h"
using namespace Gdiplus;

/**
* CMoney constructor
* \param game to add money to
* \param filename of the image to load
*/
CMoney::CMoney(CGame* game, wstring& filename) :
	CItem(game, filename)
{
}

void CMoney::Collision()
{
	/*
	 * Display money's worth
	 *
	Graphics graphics;

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 32);

	SolidBrush green(Color(0, 64, 0));

	string message = ("$" + to_string(mWorth));

	wstring wide_string = wstring(message.begin(), message.end());
	const wchar_t* result = wide_string.c_str();


	graphics.DrawString(result, -1, &font, PointF(500, 500), &green);
	*/

	// make money fly
	auto game = GetGame();
	int score = game->GetScore();
	score += mWorth;
	game->SetScore(score);

	while (GetY() > 0)
	{
		SetLocation(GetX() , (GetY() - 50));
		// make it wait somehow
	}
}
