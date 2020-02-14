#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Wall.h"
#include "Platform.h"
#include "EndDoor.h"
#include "Character.h"
#include "Player.h"
using namespace std;


CGame::CGame()
{

}

CGame::~CGame()
{
}

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

/** Draw the game
* \param graphics The GDI+ graphics context to draw on
*/
void CGame::OnDraw(Gdiplus::Graphics* graphics)
{
    graphics->DrawImage(mBackground.get(), 0, 0,
        mBackground->GetWidth(), mBackground->GetHeight());
    
    for (auto entity : mEntities)
    {
        entity->Draw(graphics);
    }
}

void CGame::Load(const std::wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        std::shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"items")
            {
                XmlLevel(node);
            }
        }

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}

/**
 * Clear the game data.
 *
 * Deletes all known entities in the game.
 */
void CGame::Clear()
{
    mEntities.clear();
}

