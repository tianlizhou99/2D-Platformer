/**
 * \file President.h
 *
 * \author Team Sprixie
 *
 * Class that implements a president
 */

#pragma once
#include "Item.h"
#include "DoubleBufferDC.h"
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

    /** Sets location of the text on the screen
    * \param x position
    * \param y position */
    void SetTextLocation(double x, double y);

    void Update(double elapsed);

    /// used to carry out different actions dependent
    /// on what item the player collides with.
    void Collision(CPlayer * player)override;

    void Draw(Gdiplus::Graphics* graphics);

private:
    int mTextSize = 48;
};

