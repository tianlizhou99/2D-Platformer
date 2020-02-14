/**
 * \file Wall.h
 *
 * \author Team Sprixie
 *
 * Class that implements a wall
 */

#pragma once
#include "Level.h"


class CWall :
	public CLevel
{
    CWall::CWall(CGame* game);

    /// Default constructor (disabled)
    CWall() = delete;

    /// Copy constructor (disabled)
    CWall(const CWall&) = delete;
};

