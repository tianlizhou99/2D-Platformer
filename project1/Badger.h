/**
 * \file Badger.h
 *
 * \author team Sprixie
 *
 *  Class that implements a Badger character
 */
#pragma once
#include<memory>
#include "Character.h"
#include "Entity.h"
 /**
 *A Badger Character Class
 */
class CBadger :public CCharacter
{
public:
    /** Constructor for Badger
    * \param game is the game the playeris held in
    */
    CBadger(CGame* game);
    /** saves the items to xml
    * \param node the item to save
    * \return a shared pointer to an object to save
    */
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Default constructor (disabled)
    CBadger() = delete;

    /// Copy constructor (disabled)
    CBadger(const CBadger&) = delete;


};

