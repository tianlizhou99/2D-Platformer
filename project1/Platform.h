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
    CPlatform(CGame* game);

    /// Default constructor (disabled)
    CPlatform() = delete;

    /// Copy constructor (disabled)
    CPlatform(const CPlatform&) = delete;
};

