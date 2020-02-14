#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Wall.h"
#include "Platform.h"
#include "EndDoor.h"
using namespace std;


/**
* Add an item to the game
* \param entity New item to add
*/
void CGame::Add(std::shared_ptr<CEntity> entity)
{
	mEntities.push_back(entity);
}

/**
* Handle a level node.
* \param node Pointer to XML node we are handling
*/
void CGame::XmlLevel(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // A pointer for the item we are loading
    shared_ptr<CLevel> item;

    // We have an item. What type?
    wstring type = node->GetAttributeValue(L"type", L"");
    if (type == L"wall")
    {
        item = make_shared<CWall>(this);
    }
    else if (type == L"platform")
    {
        item = make_shared<CPlatform>(this);
    }
    else if (type == L"enddoor")
    {
        item = make_shared<CEndDoor>(this);
    }
    if (item != nullptr)
    {
        item->XmlLoad(node);
        Add(item);
    }
}