#pragma once
#include<memory>
#include "Character.h"
#include "Entity.h"

/**
 * class that represents the player character
 */
class CPlayer :public CCharacter
{
public:
    /** Constructor for Player
    * \param game is the Game the Player is held in
    */
    CPlayer(CGame* game);
    /** saves the items to xml
    * \param node the item to save
    * \return a shared pointer to an object to save
    */
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Default constructor (disabled)
    CPlayer() = delete;

    /// Copy constructor (disabled)
    CPlayer(const CPlayer&) = delete;

    /** increases the y position of the player
    *
    */
    void Jump();

    /** sets ground contact to false on loss
      *
      */
    void Loss();

    /** updates the player over time
    */
    void Update(double elpased) override;

    /** Draws the player
      *
      */
    void Draw(Gdiplus::Graphics* graphics)override;

    /** Accept a visitor
    * \param visitor The visitor we accept
    * \return virtual function
    */
    virtual void Accept(CVisitor* visitor) { visitor->VisitPlayer(this); }

    /// Setter function setting the x velocity of the gnome
    /// \param vel the velocity that mVelX is being set to
    void SetVelX(double vel) { mVelX = vel; }

    /// Setter function setting the velocity of the gnome
    /// \param vel the velocity that mVel is being set to
    void SetVelY(double vel) { mVelY = vel; }

    /// Setter function setting the Timer of the gnome
    /// \param Time the Time that mTimer is being set to
    void SetTimer(double Time) { mTimer = Time; }

    /// Getter function getting the velocity of the gnome
    /// \return mVelX the current velocity of the gnome in the x direction
    double GetVelX() { return mVelX; }

    /// Getter function getting the velocity of the gnome
    /// \return mVelY the current velocity of the gnome in the y direction
    double GetVelY() { return mVelY; }


    /// Setter function setting the platform contact of the gnome
    /// \param collision set platform contact true if collision
    void SetGroundContact(double collision) { mGroundContact = collision; }

    /// Setter function setting the multiplier for the speed o f the gnome
    /// \param multiplier the new multiplier or the speed of the gnome
    void SetDistanceX(double distance) { mDistanceX = distance; }

    /// Getter function getting the velocity of the gnome
    /// \return the current distance that the gnome travels in the x direction
    double GetDistanceX() { return mDistanceX; }

private:
    double mJumping = false; ///< whether player is jumping
    double mTime = 0; ///< time elapsed since space bar
    double mTimer = 0; ///< time that left or right key has been held down for
    double mVelX = 0; ///< velocity of the player in the x direction
    double mVelY = 0; ///<velocity of the player in the y direction
    double mGroundContact = false; ///<whether player is in contact with ground
    double mDistanceX = 500; ///< the speed multiplier for the player in the x direction
};
