/**
 * \file Character.h
 *
 * \author team Sprixie
 *
 *  Class that implements a character
 */
#pragma once
#include "Entity.h"
#include "Game.h"
 /**
 *A Character Class
 */
class CCharacter :public CEntity
{
public:
    /** loads the items from xml
    * \param node the item to load
    */
    void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
    /** saves the items to xml
    * \param node the item to save
    * \return a shared pointer to an object to save
    */
    std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Default constructor (disabled)
    CCharacter() = delete;

    /// Copy constructor (disabled)
    CCharacter(const CCharacter&) = delete;
    /** sets the characters speed in the x direction
    * \param x is speed of character
    */
    void SetSpeedX(double x);
    /** sets the characters speed in the y direction
    * \param y is speed of characters
    */
    virtual void Update(double elapsed);
    void SetStart(double start);
    void SetSpeedY(double y);

    /** Constructor for character
    * \param game is the game the character is held in
    * \param filename File location of the image
    */
    CCharacter(CGame* game, const std::wstring& filename);

private:
    ///  speed in the X direction
    double mSpeedX;

    ///  speed in the Y direction
    double mSpeedY;
    double mStartY;
    double mTime;
};


