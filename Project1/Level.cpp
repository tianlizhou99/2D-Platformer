/**
 * \file Level.cpp
 *
 * \author Team Sprixie
 */

#include "pch.h"
#include "Level.h"

/**
 * Constructor
 * \param game The game we are in
 * \param filename Filename for the image we use
 */
CLevel::CLevel(CGame* game, const std::wstring& filename) :
    CEntity(game, filename)
{
}


/**
 * Load the attributes for a level component node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the item from
 */
void CLevel::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CEntity::XmlLoad(node);
    mWidth = node->GetAttributeIntValue(L"width", 0);
    mHeight = node->GetAttributeIntValue(L"height", 0);
}