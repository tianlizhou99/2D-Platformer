/**
 * \file Timer.h
 *
 * \author Team Sprixie
 *
 * Class that represents the timer
 */

#pragma once
#include "Element.h"
#include <memory>

/**
* Timer class
*/
class CTimer :
	public CElement
{
public:
	double GetTime();

	void Draw(Gdiplus::Graphics* graphics) override;

	/// Default constructor (disabled)
	CTimer() = delete;

	/// Copy constructor (disabled)
	CTimer(const CTimer&) = delete;

	CTimer(CGame* game);

	void Update(double elpased) override;


private:
	double mTime = 0; ///< time elapsed
};

