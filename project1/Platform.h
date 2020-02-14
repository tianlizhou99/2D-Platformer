/**
 * \file Platform.h
 *
 * \author Team Sprixie
 *
 * Class that implements a platform
 */

#pragma once
#include "Level.h"


class CPlatform :
	public CLevel
{
    CPlatform::CPlatform(CGame* game);

    /// Default constructor (disabled)
    CPlatform() = delete;

    /// Copy constructor (disabled)
    CPlatform(const CPlatform&) = delete;
};

