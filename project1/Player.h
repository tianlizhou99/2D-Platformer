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
    /** updates the player over time
    */
    void Update(double elpased) override;
    /** updates the players movement over time
* \param elapsed is the time 
*/
    void UpdateMove(double elapsed);
    /** Draws the player
* 
*/
    void Draw(Gdiplus::Graphics* graphics)override;

    /** Accept a visitor
    * \param visitor The visitor we accept
    * \return virtual function
    */
    virtual void Accept(CVisitor* visitor) { visitor->VisitPlayer(this); }

    /// Setter function setting the velocity of the gnome
    /// \param vel the velocity that mVel is being set to
    void SetVel(double vel) { mVel = vel; }

    /// Setter function setting the Timer of the gnome
    /// \param Time the Time that mTimer is being set to
    void SetTimer(double Time) { mTimer = Time; }


private:
    double mJumping = false; ///< whether player is jumping
    double mTime = 0; ///< time elapsed since space bar
    double mTimer = 0; ///< time that left or right key has been held down for
    double mVel = 0; ///< velocity of the player in the x direction

};
