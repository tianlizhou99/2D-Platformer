#include "pch.h"
#include "FarmLaneWalkSign.h"

void FarmLaneWalkSign::SetSign(double elapse)
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