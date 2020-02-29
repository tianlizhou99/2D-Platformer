/**
 * \file Item.h
 *
 * \author Team Sprixie
 *
 * Base class for any item in the game
 */

#pragma once
#include "Entity.h"

/**
* base class for any item in the game
*/
class CItem :
	public CEntity
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    /** gets the speed of the item in the x direction
    * \returns the speed of the object in the x direction*/
    double CItem::GetSpeedX() { return mSpeedX; }

    /** gets the speed of the item in the y direction
    * \returns the speed of the object in the y direction*/
    double CItem::GetSpeedY() { return mSpeedY; }

    /** sets the speed of the item in the x direction
    * \param x the speed that the speed in the x direction will be set to*/
    void CItem::SetSpeedX(double x) { mSpeedX = x; }

    /** sets the speed of the item in the y direction
    * \param y the speed that the speed in the y direction will be set to*/
    void CItem::SetSpeedY(double y) { mSpeedY = y; }

private:
    ///<  speed in the X direction
    double mSpeedX;

    ///<  speed in the Y direction
    double mSpeedY;


protected:
    CItem(CGame* game, const std::wstring& filename);

    ///< Make the item fly off screen when collided with
    bool mFlyAway = false;

    ///< x location of the text displayed on the screen
    double mTextX = 0;

    ///< y location of the text displayed on the screen
    double mTextY = 0;

};

