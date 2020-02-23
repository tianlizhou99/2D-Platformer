#pragma once
#include "Level.h"

/**
* Class for Farm Lane Walk Sign item
*/
class CFarmLaneWalkSign :
	public CLevel
{
public:
	CFarmLaneWalkSign(CGame* game);

	/// Default constructor (disabled)
	CFarmLaneWalkSign() = delete;

	/// Copy constructor (disabled)
	CFarmLaneWalkSign(const CFarmLaneWalkSign&) = delete;

	CFarmLaneWalkSign(CGame* game, wstring& filename);

	///possible sign states
	enum Sign {stop = 0, walk = 1};

	/** Sets the sign according to the time that has elapsed
	 * \param elapse Time elapsed since last call
	 * \returns void */
	void SetSign(double elapse);

	/** Gets the sign state
	 * \returns Sign state */
	Sign GetSign() { return mSign; }
private:
	Sign mSign = stop; ///<Sign state
};

