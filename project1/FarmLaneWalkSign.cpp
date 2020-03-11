/**
 * \file FarmLaneWalkSign.cpp
 *
 * \author Team Sprixie
 */


#include "pch.h"
#include "FarmLaneWalkSign.h"
#include <memory>

/// Farm Lane walk image
const wstring WalkSign = L"images/walksign.png";
/// Farm Lane stop image
const wstring StopSign = L"images/stopsign.png";

/** Constructor
 * \param game The game this is a member of
*/
CFarmLaneWalkSign::CFarmLaneWalkSign(CGame* game) :
	CLevel(game, StopSign)
{
}

/**
* Overloaded constructor
* \param game that the sign is in
* \param filename image to load from
*/
CFarmLaneWalkSign::CFarmLaneWalkSign(CGame* game, wstring& filename) : CLevel(game, filename)
{
}

void CFarmLaneWalkSign::Update(double elapse)
{
	mElapsed += elapse;
	if (mElapsed > 5)
	{
		switch (mSign)
		{
			case stop:
				mSign = walk;
				break;
			case walk:
				mSign = stop;
				break;
		}
		mElapsed = 0;
	}
}

/** Override to draw the object
* \param graphics The GDI+ graphics context to draw on
*/
void CFarmLaneWalkSign::Draw(Gdiplus::Graphics* graphics)
{
	if (mSign == walk)
	{
		std::unique_ptr<Gdiplus::Bitmap> walkImage = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(WalkSign.c_str()));
		double wid = GetImage()->GetWidth();
		double hit = GetImage()->GetHeight();


		graphics->DrawImage(walkImage.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
	}
	else
	{
		std::unique_ptr<Gdiplus::Bitmap> stopImage = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(StopSign.c_str()));
		double wid = GetImage()->GetWidth();
		double hit = GetImage()->GetHeight();

		graphics->DrawImage(stopImage.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
	}
}

/**
 * functionality of the sign when it collides with a player
 * \param player the player of the game that is colliding with the object
 * \returns void
 */
void CFarmLaneWalkSign::Collision(CPlayer* player)
{
	if (mSign == walk)
	{
		player->SetDistanceX(player->GetDistanceX() + 150);
	}
	else
	{
		player->SetDistanceX(player->GetDistanceX() - 150);
	}
	SetLocation(-100, -100);
}
