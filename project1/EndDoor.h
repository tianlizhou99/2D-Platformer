/**
 * \file EndDoor.h
 *
 * \author Team Sprixie
 *
 * Class that implements the end door
 */

#pragma once
#include "Level.h"

/**
* class that represents the door to end the level
*/
class CEndDoor :
	public CLevel
{
public:
    CEndDoor(CGame* game);

    /// Default constructor (disabled)
    CEndDoor() = delete;

    /// Copy constructor (disabled)
    CEndDoor(const CEndDoor&) = delete;
};

