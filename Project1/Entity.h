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
#include "XmlNode.h"
#include "Visitor.h"
using namespace xmlnode;




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
    /** Sets location of the entity on the screen
    * \param x position*/
    void SetX(double x) { mX = x; }
    /** Sets location of the entity on the screen
     * \param x position
     * \param y position */

    void SetLocation(double x, double y);
    /** The X location of the item
     * \returns X location in pixels */
    double GetX() const { return mX; }

    /** The Y location of the item
     * \returns Y location in pixels */
    double GetY() const { return mY; }

    virtual ~CEntity();

    /// \return void
    virtual void Draw(Gdiplus::Graphics* graphics);

    /// \return void
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Saves game state
     * \param node to save to
     * \returns node */
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    /// \return void
    virtual void Update(double elapsed) {}

    /** The the location of the game the entity is apart of
     * \returns game the entity is associated with */
    CGame * GetGame() const { return mGame; }

    CEntity(CGame* game, const std::wstring& filename);

    /// getter function getting the width of the image
    /// \returns double representing image width
    virtual int GetWidth() const { return mEntityImage->GetWidth(); }

    /// getter function getting the height of the image
    /// \returns double representing Image Height
    virtual int GetHeight() const { return mEntityImage->GetHeight(); }

    /// virtual function used to carry out different actions dependent
    /// on what item the player collides with.
    /// \param player to check collision with
    /// \return void
    virtual void Collision(CPlayer* player) {};

    /** getter function getting the image of the object
     * \returns the image that is used to draw the item */
    virtual Gdiplus::Bitmap* GetImage() { return mEntityImage.get(); }

private:
    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item

    bool mYMirror = false; ///< True flips entity across y-axis

    /// The image of this entity
    std::unique_ptr<Gdiplus::Bitmap> mEntityImage;

    /// the game this entity is part of
    CGame* mGame;
    
};

