#pragma once
#include "Level.h"
#include "Entity.h"

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

	/** Gets the sign state
	 * \returns Sign state */
	Sign GetSign() { return mSign; }

	/** Sets the sign according to the time that has elapsed
	 * \param elapse Time elapsed since last call
	 * \returns void */
	virtual void Update(double elapse);

	void Draw(Gdiplus::Graphics* graphics) override;

	virtual void Collision(CPlayer* player) override;

private:
	double mElapsed = 0; ///<Time elapsed since last call
	Sign mSign = stop; ///<Sign state
	double mMultiplier = 2; ///< Speed multiplier
};

