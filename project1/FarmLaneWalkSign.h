#pragma once
#include "Level.h"
class FarmLaneWalkSign :
	public CLevel
{
public:
	enum Sign {stop = 0, walk = 1};
	void SetSign(double timer);
	Sign GetSign() { return mSign; }
private:
	Sign mSign = stop;
};

