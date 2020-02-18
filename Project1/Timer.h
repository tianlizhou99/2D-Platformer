#pragma once
#include "Element.h"
#include <memory>
class CTimer :
	public CElement
{
public:
	double GetTime();
	void SetTime(double time);

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

