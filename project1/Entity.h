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
    void SetLocation(double x, double y);
    /** The X location of the item
     * \returns X location in pixels */
    double GetX() const { return mX; }

    /** The Y location of the item
     * \returns Y location in pixels */
    double GetY() const { return mY; }

    virtual ~CEntity();

    CEntity(const std::wstring& filename);

    void Draw(Gdiplus::Graphics* graphics);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

protected:
    CEntity(CGame* game, const std::wstring& filename);

private:
    double mX; ///< X location for the center of the item
    double mY; ///< Y location for the center of the item

    bool mYMirror; ///< True flips entity across y-axis

    /// The image of this entity
    std::unique_ptr<Gdiplus::Bitmap> mEntityImage;

    /// the game this entity is part of
    CGame* mGame;
    
};

