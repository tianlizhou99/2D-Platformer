/**
 * \file Wolverine.h
 *
 * \author team Sprixie
 *
 *  Class that implements a wolverine character
 */
#pragma once
#include<memory>
#include "Character.h"
#include "Entity.h"
 /**
 *A Wolverine Class
 */
class CWolverine :public CCharacter
{
public:
    /** Constructor for Wolverine
    * \param game is the game the playeris held in
    */
    CWolverine(CGame* game);
    /** saves the items to xml
    * \param node the item to save
    * \return a shared pointer to an object to save
    */
    virtual std::shared_ptr<xmlnode::CXmlNode>
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /// Default constructor (disabled)
    CWolverine() = delete;

    /// Copy constructor (disabled)
    CWolverine(const CWolverine&) = delete;


};

