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

    int GetWorth() { return mWorth; }
    void SetWorth(int worth) { mWorth = worth; }

private:
    int mWorth = 0;
};

