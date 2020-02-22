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

/**
* Class for the Tuition Up item
*/
class CPresident :
	public CItem
{
public:
    /// Default constructor (disabled)
    CPresident() = delete;

    /// Copy constructor (disabled)
    CPresident(const CPresident&) = delete;

    CPresident(CGame* game, wstring& filename);
};

