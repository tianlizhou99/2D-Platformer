#include "pch.h"
#include "FarmLaneWalkSign.h"

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

void CFarmLaneWalkSign::SetSign(double elapse)
{
	if (elapse > 5)
	{
		switch (mSign)
		{
			case 0:
				mSign = walk;
				break;
			case 1:
				mSign = stop;
				break;
		}
	}
}