/**
 * \file Platform.h
 *
 * \author Team Sprixie
 *
 * Class that implements a platform
 */

#pragma once
#include "Level.h"

 /**
  * class that represents a platform to jump on
  */
class CPlatform :
	public CLevel
{
public:
    /// Constructor for CPlatform
    CPlatform(CGame* game);

    /// Default constructor (disabled)
    CPlatform() = delete;

    /// Copy constructor (disabled)
    CPlatform(const CPlatform&) = delete;

    CPlatform(CGame* game, const std::wstring& filename);

    CPlatform(CGame* game, const std::wstring& filename, int type);

    /** Handle collision behavior
    * \param player The current player in the game
    * \return void */
    virtual void Collision(CPlayer* player) override;

private:
    int mType = 0; ///< The type of this platform
};

