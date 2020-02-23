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


    double CItem::GetSpeedX() { return mSpeedX; }

    double CItem::GetSpeedY() { return mSpeedY; }

    void CItem::SetSpeedX(double x) { mSpeedX = x; }

    void CItem::SetSpeedY(double y) { mSpeedY = y; }

private:
    ///  speed in the X direction
    double mSpeedX;

    ///  speed in the Y direction
    double mSpeedY;


protected:
    CItem(CGame* game, const std::wstring& filename);
};

