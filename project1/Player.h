#pragma once
#include<memory>
#include "Character.h"
#include "Entity.h"
class CPlayer :public CCharacter
{
public:
    /** Constructor for beta fish
    * \param aquarium is the aquarium beta fish is held in
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

};

