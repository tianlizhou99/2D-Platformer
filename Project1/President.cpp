#include "pch.h"
#include "President.h"

using namespace Gdiplus;

/**
* Constructor for CPresident
* \param game to add money to
* \param filename of the image to load
*/
CPresident::CPresident(CGame* game, wstring& filename) :
	CItem(game, filename)
{
}

void CPresident::SetTextLocation(double x, double y)
{
	mTextX = x;
	mTextY = y;
}


/**
 * updates the function whenever all the objects in the game are updated
 * \param elapsed the amount of time passed since the last call of update
 */
void CPresident::Update(double elapsed)
{
	// Initialize game
	auto game = GetGame();

	if (mFlyAway)
	{
		SetSpeedY(1000);
		SetLocation(GetX(), GetY() + GetSpeedY() * elapsed);
		SetTextLocation(mTextX, mTextY - GetSpeedY() * elapsed);
		if ((GetY() > 1250) && (mTextY < -250))
		{
			mFlyAway = false;

			// Mark as used
			mUsed = true;
		}

		// Make text grow
		mTextSize += 5;
		mTextX -= 100;
	}
}


void CPresident::Collision(CPlayer* player)
{
	// Initialize game
	auto game = GetGame();


	if ((!mFlyAway) && (!mUsed))
	{
		// Increase Tuition
		game->SetTuitionIncrease(game->GetTuitionIncrease() + 1);

		// Make president fly away
		mFlyAway = true;

	}
}

/**
 * Draws the president, along with the Increase Tuition message
 * \param graphics the graphics tool used to draw the president.
 */
void CPresident::Draw(Gdiplus::Graphics* graphics)
{
	auto entityImage = GetImage();
	double wid = entityImage->GetWidth();
	double hit = entityImage->GetHeight();

	graphics->DrawImage(entityImage,
		float(GetX() - wid / 2), float(GetY() - hit / 2),
		(float)entityImage->GetWidth(), (float)entityImage->GetHeight());

	if ((mFlyAway) && (!mUsed))
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, mTextSize);

		SolidBrush green(Color(0, 64, 0));

		wstring score = L"Tuition Increase!";

		wstring wide_string = wstring(score.begin(), score.end());
		const wchar_t* result = wide_string.c_str();


		graphics->DrawString(result, -1, &font, PointF(mTextX, mTextY), &green);
	}
}