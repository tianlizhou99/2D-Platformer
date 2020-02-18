#include "pch.h"
#include "Wall.h"

/// Wall 1 filename
const wstring ImageNameWall1 = L"images/wall1.png";

/// Wall 2 filename
const wstring ImageNameWall2 = L"images/wall2.png";

/** Constructor
 * \param game The game this is a member of
*/
CWall::CWall(CGame* game) :
    CLevel(game, ImageNameWall1)
{
}

/**
 * Load the attributes for a wall node.
 *
 * \param node The Xml node we are loading the entity from
 */
void CWall::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CEntity::XmlLoad(node);

    mHeight = node->GetAttributeDoubleValue(L"height", 0);
    mWidth = node->GetAttributeDoubleValue(L"width", 0);
}