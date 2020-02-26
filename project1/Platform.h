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
   
    /* constructor for platform
    * \param game the game containing the wall
    * \param filename the name of the image file
    */
    CPlatform(CGame* game, const std::wstring& filename);

    CPlatform(CGame* game, const std::wstring& filename, int type);

    /// on collision set player's y velocity to 0
    /// \return void
    virtual void Collision(CPlayer* player) override;

private:
    int mType = 0;
};

