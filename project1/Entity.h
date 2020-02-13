/**
 * \file Entity.h
 *
 * \author Team Sprixie
 *
 * Base class for any object in the game
 */

#pragma once

#include<memory>
#include<string>


class CGame;
/**
 * base class for any object in the game
 */
class CEntity
{
public:
    /// Default constructor (disabled)
    CEntity() = delete;

    /// Copy constructor (disabled)
    CEntity(const CEntity&) = delete;

    virtual ~CEntity();

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    
private:
    double mPosX; ///< X location for the center of the item
    double mPosy; ///< Y location for the center of the item

    /// The image of this entity
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

    /// the aquarium this item is contained in
    CGame* mGame;
    
};

