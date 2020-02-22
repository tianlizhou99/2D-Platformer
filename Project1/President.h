/**
 * \file President.h
 *
 * \author Team Sprixie
 *
 * Class that implements a president
 */

#pragma once
#include "Item.h"
#include <string>
using namespace std;

class CPresident :
	public CItem
{
public:
    /// Default constructor (disabled)
    CPresident() = delete;

    /// Copy constructor (disabled)
    CPresident(const CPresident&) = delete;

    CPresident(CGame* game, wstring& filename);

    /** Tells whether or not this entitiy is a president (remove this variable when collision is implemented; bad practice)
    * \returns true if president */
    bool IsPresident() { return true; }
};

