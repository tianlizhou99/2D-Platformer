/**
 * \file Money.h
 *
 * \author Team Sprixie
 *
 * Class that implements money
 */

#pragma once
#include "Item.h"
#include <string>
using namespace std;

/**
* Class for money items
*/
class CMoney :
	public CItem
{
public:
    /// Default constructor (disabled)
    CMoney() = delete;

    /// Copy constructor (disabled)
    CMoney(const CMoney&) = delete;

    CMoney(CGame* game, wstring& filename);

    /// used to carry out different actions dependent
    /// on what item the player collides with.
    void Collision();

    /// Getter for mWorth
    /// \returns int mWorth
    int GetWorth() { return mWorth; }

    /// Setter for mWorth
    /// \param worth of the money
    void SetWorth(int worth) { mWorth = worth; }

private:
    int mWorth = 0; ///< Worth of the money
};

