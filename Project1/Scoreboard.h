/**
 * \file Scoreboard.h
 *
 * \author Team Sprixie
 *
 * Class that represents the scoreboard
 */

#pragma once
#include "Element.h"
#include <memory>

/**
* Scoreboard class
*/
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

