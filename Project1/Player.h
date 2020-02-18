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
    * \param Game is the Game the Player is held in
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
    void Jump();
    void Update(double elpased) override;

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CVisitor* visitor) { visitor->VisitPlayer(this); }

private:
    double mJumping = false; ///< whether player is jumping
    double mTime = 0; ///< time elapsed since space bar

};
