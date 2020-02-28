

#include "pch.h"
#include "FarmLaneWalkSign.h"
#include <memory>

/// Farm Lane images
const wstring WalkSign = L"images/walksign.png";
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
* \param game that the door is in
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

void CFarmLaneWalkSign::Draw(Gdiplus::Graphics* graphics)
{
	if (mSign == walk) {

		std::unique_ptr<Gdiplus::Bitmap> walkImage = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(WalkSign.c_str()));
		double wid = GetImage()->GetWidth();
		double hit = GetImage()->GetHeight();


		graphics->DrawImage(walkImage.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
	}
	else{
		std::unique_ptr<Gdiplus::Bitmap> stopImage = unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(StopSign.c_str()));
		double wid = GetImage()->GetWidth();
		double hit = GetImage()->GetHeight();

		graphics->DrawImage(stopImage.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)GetImage()->GetWidth(), (float)GetImage()->GetHeight());
	}
}