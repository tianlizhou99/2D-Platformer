#pragma once
#include "Element.h"
#include <memory>


class CScoreboard :
	public CElement
{
public:
	int GetScore();

	void Draw(Gdiplus::Graphics* graphics) override;

	/// Default constructor (disabled)
	CScoreboard() = delete;

	/// Copy constructor (disabled)
	CScoreboard(const CScoreboard&) = delete;

	CScoreboard(CGame* game);

	void Update(double elpased) override;
};

