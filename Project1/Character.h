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

    /** updates the character
    * \param elapsed is time gone by
    */
    void Update(double elapsed);
    /** sets the characters sstarting y coordinate
    * \param start is speed of characters
    */
    void SetStart(double start);
    /** sets the characters speed in the y direction
    * \param y is speed of characters
    */
    void SetSpeedY(double y);

    /** Constructor for character
    * \param game is the game the character is held in
    * \param filename File location of the image
    */
    CCharacter(CGame* game, const std::wstring& filename);

    /**
      * Handle collision behavior with character
      * \param player to check collision with
      * \return void
      */
    virtual void Collision(CPlayer* player);

private:
    ///  speed in the X direction
    double mSpeedX;

    ///  speed in the Y direction
    double mSpeedY;
    ///  Starting y coordinate
    double mStartY;
    /// timer
    double mTime;
};


