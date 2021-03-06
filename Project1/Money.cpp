/**
 * \file Money.cpp
 *
 * \author Team Sprixie
 */

#include "pch.h"
#include "Money.h"

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

void CMoney::SetTextLocation(double x, double y)
{
	mTextX = x;
	mTextY = y;
}

/**
* Update override
* \param elapsed time since last call
*/
void CMoney::Update(double elapsed)
{
	auto game = GetGame();


	if (mFlyAway)
	{
		SetSpeedY(-1000);
		SetLocation(GetX(), GetY() + GetSpeedY() * elapsed);
		if (GetY() < -250)
		{
			mFlyAway = false;
			mWorth = 0;
		}
	}
	else if ((game->GetTuitionIncrease() > mCurrentIncrease) && (mWorth != 0)) // Check if worth needs update 
	{
		mWorth = mWorth + (mWorth / 10);
		mCurrentIncrease += 1;
	}
	else if (game->GetState() == 0)
	{
		mWorth = mInitialWorth;
	}
}


void CMoney::Collision(CPlayer* player)
{
	if ((!mFlyAway) && (mWorth != 0))
	{
		// Initialize game
		auto game = GetGame();

		// Update score
		int score = game->GetScore();
		score += mWorth;
		game->SetScore(score);

		// Make money fly away
		mFlyAway = true;
	}
}

/**
 * Draws the money, along with the value of the mooney when collected
 * \param graphics the graphics tool used to draw the scoreboard.
 */
void CMoney::Draw(Gdiplus::Graphics* graphics)
{
	auto entityImage = GetImage();
	double wid = entityImage->GetWidth();
	double hit = entityImage->GetHeight();

	graphics->DrawImage(entityImage,
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)entityImage->GetWidth(), (float)entityImage->GetHeight());

	if ((mFlyAway) && (mWorth != 0))
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 24);

		SolidBrush green(Color(0, 64, 0));

		wstring score = L"$" + to_wstring(mWorth);

		wstring wide_string = wstring(score.begin(), score.end());
		const wchar_t* result = wide_string.c_str();


		graphics->DrawString(result, -1, &font, PointF(mTextX, mTextY), &green);
	}
}