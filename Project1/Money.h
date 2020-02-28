/**
 * \file Money.h
 *
 * \author Team Sprixie
 *
 * Class that implements money
 */

#pragma once
#include "Item.h"
#include "DoubleBufferDC.h"
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

    void Update(double elapsed);

    /// used to carry out different actions dependent
    /// on what item the player collides with.
    void Collision(CPlayer* player) override;

    void Draw(Gdiplus::Graphics* graphics);

    /// Getter for mInitialWorth
    /// \returns int mInitialWorth
    int GetInitialWorth() { return mInitialWorth; }

    /// Getter for mWorth
    /// \returns int mWorth
    int GetWorth() { return mWorth; }

    /** Sets location of the text on the screen
     * \param x position
     * \param y position */
    void SetTextLocation(double x, double y);

    /// Setter for mWorth
    /// \param worth of the money
    void SetInitialWorth(int initialWorth) { mInitialWorth = initialWorth; }

    /// Setter for mWorth
    /// \param worth of the money
    void SetWorth(int worth) { mWorth = worth; }



private:
    int mWorth = 0; ///< Value of the money
    int mInitialWorth = 0;

    int mCurrentIncrease = 0; ///< Number of times tuition increased on this dollar
};

