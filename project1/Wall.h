/**
 * \file Wall.h
 *
 * \author Team Sprixie
 *
 * Class that implements a wall
 */

#pragma once
#include "Level.h"
#include "Player.h"

 /**
  * class that represents a wall to crash into
  */
class CWall :
	public CLevel
{
public:
    CWall(CGame* game);

    /// Default constructor (disabled)
    CWall() = delete;

    /// Copy constructor (disabled)
    CWall(const CWall&) = delete;
    /// Cwall constructor
    CWall(CGame* game, wstring& filename);
    /**
  * Handle collision behavior with wall
  * \param player to check collision with
  * \return void
  */
    void Collision(CPlayer* player) override;

};

